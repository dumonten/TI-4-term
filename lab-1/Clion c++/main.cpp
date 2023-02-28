#include <iostream>
#include "encryptions.h"

int main() {
    setlocale(LC_ALL,"");
    encryption::Vigenere bk(L"", L"" , encryption::alphabets::possibleAlphabet::english);
    bk.decrypt(bk.encrypt());
    return 0;
}
