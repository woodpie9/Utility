#include <iostream>
#include <string>
#include "convert_string.h"


int main()
{

    std::locale::global(std::locale("kor"));

    {
        //
        // convert_ansi_to_unicode_string
        //

        std::wstring unicode = L"";
        std::string ansi = "ansi string 한글한글";

        convert_ansi_to_unicode_string(unicode, ansi.c_str(), ansi.size());

        std::wcout << unicode.c_str() << std::endl;
    }

    {
        //
        // convert_unicode_to_ansi_string
        //

        std::wstring unicode = L"unicode string 두글두글";
        std::string ansi = "";

        convert_unicode_to_ansi_string(ansi, unicode.c_str(), unicode.size());

        std::cout << ansi.c_str() << std::endl;
    }

    {
        //
        // convert_unicode_to_utf8_string
        //

        std::wstring unicode = L"unicode string 세글세글";
        std::string utf8 = u8"";

        convert_unicode_to_utf8_string(utf8, unicode.c_str(), unicode.size());

        std::cout << utf8.c_str() << std::endl;

        //
        // convert_utf8_to_unicode_string
        //

        std::wstring unicode_2 = L"";

        convert_utf8_to_unicode_string(unicode_2, utf8.c_str(), utf8.size());

        std::wcout << unicode_2.c_str() << std::endl;
    }

    system("pause");
}


