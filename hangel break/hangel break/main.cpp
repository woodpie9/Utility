
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
	//strcpy_s(strUTF8, 256, "utf-8����..");
	//int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
	//MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);


	//_wsetlocale(LC_ALL, L"korean");

	char strUTF8[156] = u8"utd-8 text �׽�Ʈ�ϱ� �ȳ����";
	std::cout << strUTF8 << std::endl;


	wchar_t strUnicode[256] = { 0, };

	// �ڵ� ������ / ��ȯ ���� / ��ȯ�� ���ڿ� ������ / ���ڿ��� ũ�� / ��ȯ ���ڿ��� ������ ���� ������ / ������ ũ��. NULL�Ͻ� null���ڸ� ������ ���� ũ�⸦ ���ڷ� ��ȯ.
	int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);

	//wprintf(strUnicode);
	//std::cout << std::endl;


	std::wstring wstr(strUnicode);
	std::u16string u16_str2(wstr.begin(), wstr.end());


	std::cout << strUnicode << std::endl;



	//std::u16string u16_str = u"�ȳ��ϼ��� ��ο� �ڵ忡 ���� ���� ȯ���մϴ�";
	std::string jaum[] = { u8"��", u8"��", u8"��", u8"��", u8"��", u8"��", u8"��",
						  u8"��", u8"��",u8"��", u8"��", u8"��", u8"��", u8"��",
						  u8"��", u8"��",u8"��", u8"��", u8"��" };

	for (char16_t c : u16_str2) {
		// �����ڵ� �󿡼� �ѱ��� ����
		if (!(0xAC00 <= c && c <= 0xD7A3)) {
			continue;
		}
		// �ѱ��� AC00 ���� �����ؼ� �� �ʼ��� �� 0x24C �� �� �ִ�.
		int offset = c - 0xAC00;
		int jaum_offset = offset / 0x24C;
		std::cout << jaum[jaum_offset];

	}
}
