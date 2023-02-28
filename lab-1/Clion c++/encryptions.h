#ifndef ENCRYPTIONS_H
#define ENCRYPTIONS_H

#include <iostream>
#include <locale>
#include <set>
#include <vector>
#include <map>

namespace encryption
{
    namespace alphabets
    {
        enum possibleAlphabet {russian, english, none};
        const std::vector<wchar_t> charVectorRussian =
        {
                L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж', L'з', L'и', L'й', L'к', L'л', L'м', L'н', L'о', L'п',
                L'р', L'с', L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш', L'щ', L'ы', L'ь', L'ъ', L'э', L'ю', L'я',
                L'А', L'Б', L'В', L'Г', L'Д', L'Е', L'Ё', L'Ж', L'З', L'И', L'Й', L'К', L'Л', L'М', L'Н', L'О', L'П',
                L'Р', L'С', L'Т', L'У', L'Ф', L'Х', L'Ц', L'Ч', L'Ш', L'Щ', L'Ы', L'Ь', L'Ъ', L'Э', L'Ю', L'Я',
        };
        class Alphabet
        {
        private:
            uint32_t alphabetSize;
            possibleAlphabet  alphabet;
            std::set<wchar_t> charSet;
            std::map<wchar_t, uint32_t> charMap;
        public:
            Alphabet() { alphabet = none; }
            Alphabet(possibleAlphabet abc) : alphabet(abc)
            {}

            void setChars();
            [[nodiscard]] char compareWchar_ts(const wchar_t& w1, const wchar_t& w2)const;
            [[nodiscard]] std::set<wchar_t> getCharSet()const   { return charSet;  }
            [[nodiscard]] possibleAlphabet  getAlphabet()const  { return alphabet; }
            [[nodiscard]] std::map<wchar_t, uint32_t> getCharMap()const { return charMap; }
            [[nodiscard]] uint32_t getAlphabetSize()const { return alphabetSize; }
            ~Alphabet()=default;
        };
    }

    class Encryption
    {
    protected:
        bool dataIsReformat;
        alphabets::Alphabet alphabet;
        std::wstring key, plaintext;
    private:
        virtual void reformatString(std::wstring& str);
    public:
        Encryption();
        Encryption(const std::wstring& k, const std::wstring& basicString, alphabets::possibleAlphabet abc);

        virtual void setKey(const std::wstring& k) { key = k; }
        virtual void setPlaintext(const std::wstring& basicString) { plaintext = basicString; }
        virtual void setAlphabet(alphabets::possibleAlphabet abc)  { alphabet = abc; alphabet.setChars(); }

        virtual std::wstring encrypt()=0;
        virtual std::wstring decrypt(const std::wstring& cipherText)=0;

        virtual void reformatData();

        virtual ~Encryption()=default;
    };

    class ColumnMethod : public Encryption
    {
    private:
        std::vector<std::vector<wchar_t>> encryptionMatrix;
        std::vector<std::vector<wchar_t>> decryptionMatrix;
        std::vector<std::pair<wchar_t, uint32_t> > keySeq;
    private:
        static long long partition(std::vector<std::pair<wchar_t, uint32_t> >& v,
                            const alphabets::Alphabet& alphabet, long long start, long long end);
        void quicksort(std::vector<std::pair<wchar_t, uint32_t> >& v,
                       const alphabets::Alphabet& alphabet, long long start, long long end);
        void initEncryptionMatrix();
        void initDecryptionMatrix(const std::wstring& cipherText);
        void initKeySeq();
    public:
        ColumnMethod();
        ColumnMethod(const std::wstring& k, const std::wstring& basicString, alphabets::possibleAlphabet abc);

        void setKey(const std::wstring& k) override;
        void setPlaintext(const std::wstring& basicString) override;
        void setAlphabet(alphabets::possibleAlphabet abc)  override;

        std::wstring encrypt() override;
        std::wstring decrypt(const std::wstring& cipherText) override;

        void clearData();
        ~ColumnMethod() override;
    };

    class Vigenere : public Encryption
    {
    private:
        std::map<uint32_t, wchar_t> lettersReversed;
    private:
        std::wstring getKey();
        void initReversedMap();
    public:
        Vigenere();
        Vigenere(const std::wstring& k, const std::wstring& basicString, alphabets::possibleAlphabet abc);

        void setKey(const std::wstring& k) override;
        void setPlaintext(const std::wstring& basicString) override;
        void setAlphabet(alphabets::possibleAlphabet abc)  override;

        std::wstring encrypt() override;
        std::wstring decrypt(const std::wstring& cipherText) override;

        void clearData();
        ~Vigenere() override;
    };
}

#endif
