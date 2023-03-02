#include <iostream>
#include "encryptions.h"

int main() {
    setlocale(LC_ALL,"");
    encryption::ColumnMethod objColumnMthod(L"", L"", encryption::alphabets::possibleAlphabet::russian);
    try
    {
        objColumnMthod.decrypt(L"ауау");
    }
    catch (Error& e)
    {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.error() << std::endl;
    }
    return 0;
}
