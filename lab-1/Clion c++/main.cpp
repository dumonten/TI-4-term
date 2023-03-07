#include <iostream>
#include "encryptions.h"

int main() {
    setlocale(LC_ALL,"");
    encryption::Vigenere objColumnMthod(L"Привет, мир! О, это шифратор! ", L"Желтое яркое солнце! ", encryption::alphabets::possibleAlphabet::russian);
    std::wstring cipher = objColumnMthod.encrypt();
    std::wcout << objColumnMthod.decrypt(cipher)<< "\n";
    std::wcout << std::string("redhatonmyheadisabreadonii").length() << "\n";
    return 0;
}
