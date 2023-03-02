#include "encryptions.h"
#include <vector>
#include <algorithm>

using namespace encryption;

//Alphabet -> methods  -------------------------------------------------------------------------------------------------

void alphabets::Alphabet::setChars()
{
    charSet.clear();
    charMap.clear();
    switch(alphabet)
    {
        case russian:
            for (uint64_t i = 0; i < charVectorRussian.size(); i++)
            {
                charSet.insert(charVectorRussian[i]);
                charMap[charVectorRussian[i]] = i % 33;
            }
            alphabetSize = 33;
            break;
        case english:
            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                charSet.insert(ch);
                charMap[ch] = ch % 'a';
            }
            alphabetSize = 26;
            break;
        default:
            break;
    }
}

char alphabets::Alphabet::compareWchar_ts(const wchar_t& w1, const wchar_t& w2)const
{
    if (charMap.at(w1) < charMap.at(w2))
        return -1;
    else if (charMap.at(w1) == charMap.at(w2))
        return 0;
    else
        return 1;
}

//Encryption -> methods ------------------------------------------------------------------------------------------------

Encryption::Encryption()
{
    key = L"";
    plaintext = L"";
    alphabet = alphabets::possibleAlphabet::none;
    dataIsReformat = false;
}

Encryption::Encryption(const std::wstring& k, const std::wstring& basicString,
                       alphabets::possibleAlphabet abc)
{
    key = k;
    alphabet = abc;
    plaintext = basicString;
    alphabet.setChars();
    dataIsReformat = false;
}

void Encryption::reformatData()
{
    reformatString(key);
    reformatString(plaintext);
    dataIsReformat = true;
}

void Encryption::reformatString(std::wstring& str)
{
    std::wstring tempString;
    std::set<wchar_t> charMap = alphabet.getCharSet();
    if (alphabet.getAlphabet() == alphabets::possibleAlphabet::russian)
    {
        for (wchar_t i : str)
        {
            if (charMap.find(i) != charMap.end())
                tempString += i;
        }
    }
    else if (alphabet.getAlphabet() == alphabets::possibleAlphabet::english)
    {
        for (wchar_t i : str)
        {
            if (charMap.find(towlower(i)) != charMap.end())
                tempString += towlower(i);
        }
    }
    str = tempString;
}

//ColumnMethod -> methods ----------------------------------------------------------------------------------------------

ColumnMethod::ColumnMethod() : Encryption()
{}

ColumnMethod::ColumnMethod(const std::wstring& k, const std::wstring& basicString,
                           alphabets::possibleAlphabet abc) : Encryption(k, basicString, abc)
{}

long long ColumnMethod::partition(std::vector<std::pair<wchar_t, uint32_t> >& v,
                                  const alphabets::Alphabet& alphabet, long long start, long long end)
{
    std::pair<wchar_t, uint32_t> pivot  = v[end];
    long long pIndex = start;
    for (long long i = start; i < end; i++)
    {
        char diff = alphabet.compareWchar_ts(v[i].first, pivot.first);
        if (diff < 0 || (diff == 0 && v[i].second < pivot.second))
        {
            std::swap(v[i], v[pIndex]);
            pIndex++;
        }
    }
    std::swap (v[pIndex], v[end]);
    return pIndex;
}

void ColumnMethod::quicksort(std::vector<std::pair<wchar_t, uint32_t> >& v,
                             const alphabets::Alphabet& alphabet, long long start, long long end)
{
    if (start >= end)
        return;
    long long pivot = partition(v, alphabet, start, end);
    quicksort(v, alphabet, start, pivot - 1);
    quicksort(v, alphabet, pivot + 1, end);
}

void ColumnMethod::initKeySeq()
{
    for (uint32_t i = 0, n = key.size(); i < n; i++)
        keySeq.emplace_back(key[i], i);
    quicksort(keySeq, alphabet, 0, (long long)keySeq.size() - 1);
}

void ColumnMethod::initEncryptionMatrix()
{
    if (!dataIsReformat)
        reformatData();
    if (key.empty() || plaintext.empty())
        throw Error("Ошибка: Ключ или/и исходный текст отсутствуют. Проверьте свои данные и выбранный язык.");

    uint32_t columns = key.size(), rows;
    rows = plaintext.size() % columns != 0 ? plaintext.size() / columns + 1 : plaintext.size() / columns;
    encryptionMatrix.resize(rows, std::vector <wchar_t> (columns, L'\0'));

    if (keySeq.empty()) initKeySeq();

    uint32_t plaintextSize = plaintext.size();
    for (uint32_t i = 0, ptrStr = 0; i < rows; i++)
        for (uint32_t j = 0; ptrStr < plaintextSize && j < columns; j++)
            encryptionMatrix[i][j] = plaintext[ptrStr++];
}

void ColumnMethod::initDecryptionMatrix(const std::wstring& cipherText)
{
    if (!dataIsReformat)
        reformatData();
    if (key.empty() || cipherText.empty())
        throw Error("Ошибка: Ключ или/и исходный текст отсутствуют. Проверьте свои данные и выбранный язык.");

    uint32_t columns = key.size(), rows;
    rows = cipherText.size() % columns != 0 ? cipherText.size() / columns + 1 : cipherText.size() / columns;
    decryptionMatrix.resize(rows, std::vector <wchar_t> (columns, L'\0'));

    std::set<uint32_t> emptyCellsInd;
    uint32_t lowBound = cipherText.size();
    for (uint32_t i = lowBound, highBound = columns * rows; i < highBound; i++)
        emptyCellsInd.insert(i);

    if (keySeq.empty()) initKeySeq();

    for (uint32_t j = 0, k = 0; j < columns; j++)
    {
        uint32_t currColumn = keySeq[j].second;
        for (uint32_t i = 0; i < rows; i++) {
            if (!(emptyCellsInd.find(i * columns + currColumn) != emptyCellsInd.end()))
                decryptionMatrix[i][currColumn] = cipherText[k++];
        }
    }
}

void ColumnMethod::setKey(const std::wstring& k)
{
    clearData();
    Encryption::setKey(k);
}

void ColumnMethod::setPlaintext(const std::wstring& basicString)
{
    clearData();
    Encryption::setPlaintext(basicString);
}

void ColumnMethod::setAlphabet(alphabets::possibleAlphabet abc)
{
    clearData();
    Encryption::setAlphabet(abc);
}

void ColumnMethod::clearData()
{
    uint32_t n;
    if ((n = encryptionMatrix.size()) != 0)
        for (uint32_t i = 0; i < n; i++)
            encryptionMatrix[i].clear();
    encryptionMatrix.clear();
    if ((n = decryptionMatrix.size()) != 0)
        for (uint32_t i = 0; i < n; i++)
            decryptionMatrix[i].clear();
    decryptionMatrix.clear();

    dataIsReformat = false;
    keySeq.clear();
}

std::wstring ColumnMethod::encrypt() {
    std::wstring ciphertext;
    if (encryptionMatrix.empty())
        initEncryptionMatrix();
    for (uint32_t j = 0, n = key.size(); j < n; j++)
    {
        uint32_t currColumn = keySeq[j].second;
        for (auto & i : encryptionMatrix)
        {
            if (i[currColumn] != '\0')
                ciphertext += i[currColumn];
        }
    }
    return ciphertext;
}

std::wstring ColumnMethod::decrypt(std::wstring cipherText)
{
    reformatString(cipherText);
    if (cipherText.empty())
        throw Error("Ошибка: зашифрованный текст на другом языке или отсутствует.");

    std::wstring ptext;
    if (decryptionMatrix.empty())
        initDecryptionMatrix(cipherText);

    for (auto & i : decryptionMatrix)
    {
        for (uint32_t j = 0, k = key.size(); j < k; j++)
        {
            if (i[j] != '\0')
                ptext += i[j];
        }
    }
    return ptext;
}

ColumnMethod::~ColumnMethod()
{
    clearData();
}

//Vigenere -> methods --------------------------------------------------------------------------------------------------
Vigenere::Vigenere() : Encryption()
{}

Vigenere::Vigenere(const std::wstring& k, const std::wstring& basicString,
                   alphabets::possibleAlphabet abc) : Encryption(k, basicString, abc)
{}

void Vigenere::setKey(const std::wstring& k)
{
    clearData();
    Encryption::setKey(k);
}

void Vigenere::setPlaintext(const std::wstring& basicString)
{
    clearData();
    Encryption::setPlaintext(basicString);
}

void Vigenere::setAlphabet(alphabets::possibleAlphabet abc)
{
    clearData();
    Encryption::setAlphabet(abc);
}

void Vigenere::initReversedMap()
{
    for (auto  i : alphabet.getCharMap())
        lettersReversed[i.second] = i.first;
}

std::wstring Vigenere::getKey() {
    if (key.empty() || plaintext.empty())
        throw Error("Ошибка: Ключ или/и исходный текст отсутствуют. Проверьте свои данные и выбранный язык.");

    std::wstring newKey;
    if (lettersReversed.empty()) initReversedMap();

    if (key.size() >= plaintext.size())
        newKey = key.substr(0, plaintext.size());
    else
    {
        uint32_t keySize = key.size(), aSize = alphabet.getAlphabetSize();
        std::map<wchar_t, uint32_t> lettersNormal = alphabet.getCharMap();
        for (uint32_t i = 0; i < keySize; i++)
            newKey += lettersReversed.at(lettersNormal[key[i]]);
        for (uint32_t i = keySize, n = plaintext.size(); i < n; i++)
            newKey += lettersReversed.at((lettersNormal.at(newKey[i - keySize]) + 1) % aSize);
    }
    return newKey;
}

std::wstring Vigenere::encrypt()
{
    if (!dataIsReformat)
        reformatData();

    std::wstring ciphertext, newKey = getKey();
    std::map<wchar_t, uint32_t> lettersNormal = alphabet.getCharMap();
    uint32_t aSize = alphabet.getAlphabetSize();

    for (uint32_t i = 0, n = plaintext.size(); i < n; i++)
        ciphertext += lettersReversed.at((lettersNormal.at(plaintext[i]) + lettersNormal.at(newKey[i])) % aSize);

    return ciphertext;
}

std::wstring Vigenere::decrypt(std::wstring cipherText)
{
    if (!dataIsReformat)
        reformatData();
    reformatString(cipherText);
    if (cipherText.empty())
        throw Error("Ошибка: зашифрованный текст на другом языке или отсутствует");

    std::wstring ptext, newKey = getKey();
    std::map<wchar_t, uint32_t> lettersNormal = alphabet.getCharMap();
    uint32_t aSize = alphabet.getAlphabetSize();

    for (uint32_t i = 0, n = cipherText.size(); i < n; i++)
        ptext += lettersReversed.at((lettersNormal.at(cipherText[i]) + aSize - lettersNormal.at(newKey[i])) % aSize);

    return ptext;
}

void Vigenere::clearData()
{
    lettersReversed.clear();
    dataIsReformat = false;
}

Vigenere::~Vigenere()
{
    clearData();
}
