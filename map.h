
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//������ ����� �� ������
const int WIDTH_MAP = 20;//������ ����� �� ������ 

std::string TileMap[HEIGHT_MAP] = {
	"00000000000000000000",
	"0hhhhh00hhhhh0hhhhh0",
	"0hhhhhhhhh0hhhh0hhh0",
	"00hh0000000000000hh0",
	"0hhhhhhhhhh0hhhhhhh0",
	"0hhhhhhhhh00h0h00hh0",
	"0hhh0hhhhhh0h0hhhhh0",
	"0hh00hhh0hhhh0000hh0",
	"0hh0hhh00hhhhhhh0hh0",
	"0hh0hhhh0hhhhhhh0hh0",
	"0hh0hhhh00hhh0hhhhh0",
	"0hh0hh0000000hhhhhh0",
	"0hhhhhhhhhhhhhhhhh00",
	"0hhhhhhhhhhhhhh0hhh0",
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
