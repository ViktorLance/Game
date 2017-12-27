
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 15;//размер карты по высоте
const int WIDTH_MAP = 20;//размер карты по ширине 

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
