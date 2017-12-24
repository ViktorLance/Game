///*
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//размер карты по высоте
const int WIDTH_MAP = 20;//размер карты по ширине 

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
			TileMap[randomElementY][randomElementX] = 'h';  //то ставим туда money.
			countStone--;
			if (TileMap[randomElementY][randomElementX] != ' ');
		}
	}

};
//*/

/*
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//размер карты высота
const int WIDTH_MAP = 20;//размер карты ширина 

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
