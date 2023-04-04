#include <iostream>
#include <string>

int main() {
	//                   1 234567890 1 2 34 5 6
   // std::string str = u8"ㄱ가가나라마바사 이건 UTF-8 문자열 입니다";

	const char* str = u8"ㄱ마가나라마바사";
	size_t count = 0;
	size_t len = 0;

	size_t Size = strlen(str);

	while (count < Size) {
		int char_size = 0;

		if ((str[count] & 0b11111000) == 0b11110000)
		{
			char_size = 4;
			std::cout << u8"4byte" << std::endl;
		}
		else if ((str[count] & 0b11110000) == 0b11100000)
		{
			char_size = 3;
			std::cout << u8"3byte 한글은 일단 여기" << std::endl;

			if ((str[count] & 0b11101010) == 0b11101010)
				if ((str[count + 1] & 0b10110000) == 0b10110000)
					if ((str[count + 2] & 0b10000000) == 0b10000000)
						std::cout << u8"이건 '가' 이다!" << std::endl << std::endl;

			if ((str[count] & 0b11110000) == 0b11100011)
				if ((str[count + 1] | 0b10000000) == 0b10100000)
					if ((str[count + 2] | 0b10000000) == 0b10000000)
						std::cout << u8"이건 'ㄱ' 이다!" << std::endl << std::endl;
		}
		else if ((str[count] & 0b11100000) == 0b11000000)
		{
			char_size = 2;
			std::cout << u8"2byte" << std::endl;
		}
		else if ((str[count] & 0b10000000) == 0b00000000)
		{
			char_size = 1;
			std::cout << u8"1byte" << std::endl;
		}
		else
		{
			std::cout << u8"이상한 문자 발견!" << std::endl;
			char_size = 1;
		}

		//std::cout << str.substr(i, char_size) << std::endl;

		//int i = char_size;
		int j = 0;
		while (j < char_size)
		{
			std::cout << str[count + j];
			j++;
		}
		std::cout << std::endl;


		count += char_size;
		len++;
	}
	std::cout << u8"문자열의 실제 길이 : " << len << std::endl;
	std::cout << u8"문자열의 메모리상 길이 : " << Size << std::endl;
}