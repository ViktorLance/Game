#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" 
#include "Global.h"
#include "Entity.h"
#include "Enemy.h"


using namespace std;
using namespace sf;

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
	if (name == "Enemy1") {
		//«адаем спрайту один пр€моугольник дл€
		//вывода одного игрока. IntRect Ц дл€ приведени€ типов
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (3); //Ќаправление движени€ врага задаЄм случайным образом
								  //через генератор случайных чисел
		speed = 0.1;//даем скорость.этот объект всегда двигаетс€
		dx = speed;
	}
}
void Enemy::checkCollisionWithMap(float Dx, float Dy)//ф-ци€ проверки столкновений с картой
{
	for (int i = y / 37; i < (y + h) / 37; i++)//проходимс€ по элементам карты
		for (int j = x / 37; j<(x + w) / 37; j++)
		{
			if (TileMap[i][j] == '0')//если элемент - тайлик земли
			{
				if (Dy > 0) {
					y = i * 37 - h;  dy = -0.1;
					direction = rand() % (4); //Ќаправление движени€ врага
				}//по Y 
				if (Dy < 0) {
					y = i * 37 + 37; dy = 0.1;
					direction = rand() % (4);//Ќаправление движени€ врага 
				}//столкновение с верхними кра€ми 
				if (Dx > 0) {
					x = j * 37 - w; dx = -0.1;
					direction = rand() % (4);//Ќаправление движени€ врага 
				}//с правым краем карты
				if (Dx < 0) {
					x = j * 37 + 37; dx = 0.1;
					direction = rand() % (4); //Ќаправление движени€ врага
				}// с левым краем карты
			}
		}
}
void Enemy::update(float time)
{
	if (name == "Enemy1") {//дл€ персонажа с таким именем логика будет такой

		if (life) {//провер€ем, жив ли герой
			switch (direction)//делаютс€ различные действи€ в зависимости от состо€ни€
			{
			case 0: {//состо€ние идти вправо
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(0, 0, 35, 35));
				break;
			}
			case 1: {//состо€ние идти влево
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(33, 0, 35, 35));
				break;
			}
			case 2: {//идти вверх
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(65, 0, 35, 35));
				break;
			}
			case 3: {//идти вниз
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(100, 0, 35, 35));
				break;
			}
			}

			x += dx*time; //движение по УXФ
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’

			y += dy*time; //движение по УYФ
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

			if (health <= 0) { life = false; }//если жизней меньше 0, либо равно 0, то умираем
		}
	}
}