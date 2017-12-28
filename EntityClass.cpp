#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include <iostream>
#include "global.h"
#include <sstream>

using namespace std;
using namespace sf;

Entity::Entity(Image &image, float X, float Y, int W, int H, std::string Name)
{
	x = X; y = Y; //координата появления спрайта
	w = W; h = H; //размер спрайта
	name = Name; // имя персонажа
	moveTimer = 0; //
	dx = 0; dy = 0;
	speed = 0;
	CurrentFrame = 0;
	health = 100;
	life = true; //инициализировали логическую переменную жизни, герой жив
	image.createMaskFromColor(Color(0, 0, 0)); //убираем ненужный black color, в предке, т.к. у всех техтур надо убрать черный цвет.
	texture.loadFromImage(image); //заносим наше изображение в текстуру
	sprite.setTexture(texture); //заливаем спрайт текстурой
};