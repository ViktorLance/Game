#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//размер карты по высоте
const int WIDTH_MAP = 20;//размер карты по ширине 

std::string TileMap[HEIGHT_MAP] = {
	"00000000000000000000",
	"0    h    h   h    0",
	"0      f     f  f  0",
	"00  0000000000000  0",
	"0     s    0     0 0",
	"0          0 0  0  0",
	"0   0      0 0     0",
	"0  000       0000  0",
	"0  0      f      0 0",
	"0  0    0        0 0",
	"0  0    00   00    0",
	"0  0     000000    0",
	"0  0  0000       0 0",
	"0  0        0000   0",
	"00000000000000000000",
};
void randomMapGenerate() {//рандомно расставл€ем камни

	int randomElementX = 0;//переменна€ дл€ хранени€ случайного элемента по горизонтали
	int randomElementY = 0;//переменна€ дл€ хранени€ случайного элемента по вертикали
	srand(time(0));//»нициализаци€ генератора случайных чисел	
	int countStone = 10;//количество камней


	if (countStone > 0) {
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//псевдослучайное значение по УxФ от 1 до
													  //ширина карты-1. ќграничение введено чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по УyФ

		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 'h';  //то ставим туда health.
			countStone--;
			if (TileMap[randomElementY][randomElementX] != ' ');
		}
	}

};