///*
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//������ ����� �� ������
const int WIDTH_MAP = 20;//������ ����� �� ������ 

std::string TileMap[HEIGHT_MAP] = {
	"00000000000000000000",
	"0hhhhh00hhhhh0hhhhh0",
	"0hhhhhhhhh0hhhh0hhh0",
	"00hh0000000000000hh0",
	"0hhhhhhhhhh0hhhhh0h0",
	"0hhh00hhhh00h0h0hhh0",
	"0hhh0hhhhhh0h0hhhhh0",
	"0h000hhhhhhhh0000hh0",
	"0h0hhhh00hhhhhhhh0h0",
	"0hh0h0hh0hhhhhhhh0h0",
	"0hh0h0hh00hhh00hhhh0",
	"0hh0hhhhh000000hhhh0",
	"00h0hh0000hhhhhhhh00",
	"0hhhhhhhhhhh0000hhh0",
	"00000000000000000000",
};
void randomMapGenerate() {//�������� ����������� �����

	int randomElementX = 0;//���������� ��� �������� ���������� �������� �� �����������
	int randomElementY = 0;//���������� ��� �������� ���������� �������� �� ���������
	srand(time(0));//������������� ���������� ��������� �����	
	int countStone = 10;//���������� ������


	if (countStone > 0) {
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������������� �������� �� �x� �� 1 ��
													  //������ �����-1. ����������� ������� ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� �y�

		if (TileMap[randomElementY][randomElementX] == ' ') {//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 'h';  //�� ������ ���� money.
			countStone--;
			if (TileMap[randomElementY][randomElementX] != ' ');
		}
	}

};
//*/

/*
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//������ ����� ������
const int WIDTH_MAP = 20;//������ ����� ������ 

std::string TileMap[HEIGHT_MAP] = {
	"00000000000000000000",
	"0                  0",
	"0   s  s       f   0",
	"0                  0",
	"0     s            0",
	"0             h    0",
	"0  h               0",
	"0       f          0",
	"0 s                0",
	"0          h       0",
	"0      s           0",
	"0                  0",
	"0  h           f   0",
	"0                  0",
	"00000000000000000000",
};
*/
