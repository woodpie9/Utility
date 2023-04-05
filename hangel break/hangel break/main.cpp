
// 
//
#include "Windows.h"
#include "Stringapiset.h"
#include <cstring>
#include <iostream>

int main()
{
	//wchar_t strUnicode[256] = { 0, };
	//char    strUTF8[256] = { 0, };
	//strcpy_s(strUTF8, 256, "utf-8글자..");
	//int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
	//MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);


	//_wsetlocale(LC_ALL, L"korean");

	char strUTF8[156] = u8"utd-8 text 테스트하기 안녀어어엉";
	std::cout << strUTF8 << std::endl;


	wchar_t strUnicode[256] = { 0, };

	// 코드 페이지 / 변환 유형 / 변환할 문자열 포인터 / 문자열의 크기 / 반환 문자열을 저장할 버퍼 포인터 / 버퍼의 크기. NULL일시 null문자를 포함한 버퍼 크기를 문자로 반환.
	int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);

	//wprintf(strUnicode);
	//std::cout << std::endl;


	std::wstring wstr(strUnicode);
	std::u16string u16_str2(wstr.begin(), wstr.end());


	std::cout << strUnicode << std::endl;



	//std::u16string u16_str = u"안녕하세용 모두에 코드에 오신 것을 환영합니다";
	std::string jaum[] = { u8"ㄱ", u8"ㄲ", u8"ㄴ", u8"ㄷ", u8"ㄸ", u8"ㄹ", u8"ㅁ",
						  u8"ㅂ", u8"ㅃ",u8"ㅅ", u8"ㅆ", u8"ㅇ", u8"ㅈ", u8"ㅉ",
						  u8"ㅊ", u8"ㅋ",u8"ㅌ", u8"ㅍ", u8"ㅎ" };

	for (char16_t c : u16_str2) {
		// 유니코드 상에서 한글의 범위
		if (!(0xAC00 <= c && c <= 0xD7A3)) {
			continue;
		}
		// 한글은 AC00 부터 시작해서 한 초성당 총 0x24C 개 씩 있다.
		int offset = c - 0xAC00;
		int jaum_offset = offset / 0x24C;
		std::cout << jaum[jaum_offset];

	}
}
