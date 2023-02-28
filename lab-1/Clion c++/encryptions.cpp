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
            for (int i = 0; i < charVectorRussian.size(); i++)
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
    dataIsReformat = true;
    reformatString(key);
    reformatString(plaintext);
}

void Encryption::reformatString(std::wstring& str)
{
    std::wstring tempString;
    for (wchar_t i : str)
    {
        if (alphabet.getAlphabet() == alphabets::possibleAlphabet::russian)
        {
            if (alphabet.getCharSet().contains(i))
                tempString += i;
        }
        else if (alphabet.getAlphabet() == alphabets::possibleAlphabet::english)
        {
            if (alphabet.getCharSet().contains(tolower(i)))
                tempString += i;
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
    {
        std::wcout << "Error: Key or/and plaintext is/are empty. Check your data." << "\n";
        exit(1);
    }

    uint32_t columns = key.size(), rows;
    rows = plaintext.size() % columns != 0 ? plaintext.size() / columns + 1 : plaintext.size() / columns;
    encryptionMatrix.resize(rows, std::vector <wchar_t> (columns, L'\0'));

    if (keySeq.empty()) initKeySeq();

    for (uint32_t i = 0, ptrStr = 0; i < rows; i++)
        for (uint32_t j = 0; i*columns + j <= plaintext.size() && j < columns; j++)
            encryptionMatrix[i][j] = plaintext[ptrStr++];
}

void ColumnMethod::initDecryptionMatrix(const std::wstring& cipherText)
{
    if (!dataIsReformat)
        reformatData();
    if (key.empty() || cipherText.empty())
    {
        std::wcout << "Error: Key or/and cipherText is/are empty. Check your data." << "\n";
        exit(1);
    }

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
            if (!emptyCellsInd.contains(i * columns + currColumn))
            {
                decryptionMatrix[i][currColumn] = cipherText[k++];
                wchar_t wc = cipherText[k-1];
                int a = 10;
            }
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

std::wstring ColumnMethod::decrypt(const std::wstring& cipherText)
{
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
    {
        std::wcout << "Error: Key or/and plaintext is/are empty. Check your data." << "\n";
        exit(1);
    }
    std::wstring newKey;
    if (key.size() >= plaintext.size())
        newKey = key.substr(0, plaintext.size());
    else
    {
        uint32_t keySize = key.size(), aSize = alphabet.getAlphabetSize();

        transform(newKey.begin(), newKey.end(), newKey.begin(), ::tolower);
        std::map<wchar_t, uint32_t> lettersNormal = alphabet.getCharMap();

        if (lettersReversed.empty()) initReversedMap();

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

std::wstring Vigenere::decrypt(const std::wstring& cipherText)
{
    if (!dataIsReformat)
        reformatData();

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