// https://wendys.tistory.com/84
#pragma once
#include <windows.h>

// 한글 출력을 위해     std::locale::global(std::locale("kor")); 사용
//
// convert_ansi_to_unicode_string.
//

DWORD convert_ansi_to_unicode_string(
    __out std::wstring& unicode,
    __in const char* ansi,
    __in const size_t ansi_size
) {

    DWORD error = 0;

    do {

        if ((nullptr == ansi) || (0 == ansi_size)) {
            error = ERROR_INVALID_PARAMETER;
            break;
        }

        unicode.clear();

        //
        // getting required cch.
        //

        int required_cch = ::MultiByteToWideChar(
            CP_ACP,
            0,
            ansi, static_cast<int>(ansi_size),
            nullptr, 0
        );

        if (0 == required_cch) {
            error = ::GetLastError();
            break;
        }

        unicode.resize(required_cch);

        //
        // convert.
        //

        if (0 == ::MultiByteToWideChar(
            CP_ACP,
            0,
            ansi, static_cast<int>(ansi_size),
            const_cast<wchar_t*>(unicode.c_str()), static_cast<int>(unicode.size())
        )) {
            error = ::GetLastError();
            break;
        }

    } while (false);

    return error;
}


//
// convert_unicode_to_ansi_string.
//

DWORD convert_unicode_to_ansi_string(
    __out std::string& ansi,
    __in const wchar_t* unicode,
    __in const size_t unicode_size
) {

    DWORD error = 0;

    do {

        if ((nullptr == unicode) || (0 == unicode_size)) {
            error = ERROR_INVALID_PARAMETER;
            break;
        }

        ansi.clear();

        //
        // getting required cch.
        //

        int required_cch = ::WideCharToMultiByte(
            CP_ACP,
            0,
            unicode, static_cast<int>(unicode_size),
            nullptr, 0,
            nullptr, nullptr
        );

        if (0 == required_cch) {
            error = ::GetLastError();
            break;
        }

        //
        // allocate.
        //

        ansi.resize(required_cch);

        //
        // convert.
        //

        if (0 == ::WideCharToMultiByte(
            CP_ACP,
            0,
            unicode, static_cast<int>(unicode_size),
            const_cast<char*>(ansi.c_str()), static_cast<int>(ansi.size()),
            nullptr, nullptr
        )) {
            error = ::GetLastError();
            break;
        }

    } while (false);

    return error;
}


//
// convert_unicode_to_utf8_string
//

DWORD convert_unicode_to_utf8_string(
    __out std::string& utf8,
    __in const wchar_t* unicode,
    __in const size_t unicode_size
) {

    DWORD error = 0;

    do {

        if ((nullptr == unicode) || (0 == unicode_size)) {
            error = ERROR_INVALID_PARAMETER;
            break;
        }

        utf8.clear();

        //
        // getting required cch.
        //

        int required_cch = ::WideCharToMultiByte(
            CP_UTF8,
            WC_ERR_INVALID_CHARS,
            unicode, static_cast<int>(unicode_size),
            nullptr, 0,
            nullptr, nullptr
        );

        if (0 == required_cch) {
            error = ::GetLastError();
            break;
        }

        //
        // allocate.
        //

        utf8.resize(required_cch);

        //
        // convert.
        //

        if (0 == ::WideCharToMultiByte(
            CP_UTF8,
            WC_ERR_INVALID_CHARS,
            unicode, static_cast<int>(unicode_size),
            const_cast<char*>(utf8.c_str()), static_cast<int>(utf8.size()),
            nullptr, nullptr
        )) {
            error = ::GetLastError();
            break;
        }

    } while (false);

    return error;
}


//
// convert_utf8_to_unicode_string
//

DWORD convert_utf8_to_unicode_string(
    __out std::wstring& unicode,
    __in const char* utf8,
    __in const size_t utf8_size
) {

    DWORD error = 0;

    do {

        if ((nullptr == utf8) || (0 == utf8_size)) {
            error = ERROR_INVALID_PARAMETER;
            break;
        }

        unicode.clear();

        //
        // getting required cch.
        //

        int required_cch = ::MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            utf8, static_cast<int>(utf8_size),
            nullptr, 0
        );
        if (0 == required_cch) {
            error = ::GetLastError();
            break;
        }

        //
        // allocate.
        //

        unicode.resize(required_cch);

        //
        // convert.
        //

        if (0 == ::MultiByteToWideChar(
            CP_UTF8,
            MB_ERR_INVALID_CHARS,
            utf8, static_cast<int>(utf8_size),
            const_cast<wchar_t*>(unicode.c_str()), static_cast<int>(unicode.size())
        )) {
            error = ::GetLastError();
            break;
        }

    } while (false);

    return error;
}

//
// convert_ansi_string_to_utf8
//
