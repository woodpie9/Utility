#include <iostream>
#include <string>

int main() {
	//                   1 234567890 1 2 34 5 6
   // std::string str = u8"���������󸶹ٻ� �̰� UTF-8 ���ڿ� �Դϴ�";

	const char* str = u8"���������󸶹ٻ�";
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
			std::cout << u8"3byte �ѱ��� �ϴ� ����" << std::endl;

			if ((str[count] & 0b11101010) == 0b11101010)
				if ((str[count + 1] & 0b10110000) == 0b10110000)
					if ((str[count + 2] & 0b10000000) == 0b10000000)
						std::cout << u8"�̰� '��' �̴�!" << std::endl << std::endl;

			if ((str[count] & 0b11110000) == 0b11100011)
				if ((str[count + 1] | 0b10000000) == 0b10100000)
					if ((str[count + 2] | 0b10000000) == 0b10000000)
						std::cout << u8"�̰� '��' �̴�!" << std::endl << std::endl;
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
			std::cout << u8"�̻��� ���� �߰�!" << std::endl;
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
	std::cout << u8"���ڿ��� ���� ���� : " << len << std::endl;
	std::cout << u8"���ڿ��� �޸𸮻� ���� : " << Size << std::endl;
}