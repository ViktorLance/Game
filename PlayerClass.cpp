#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" 
#include "Global.h"
#include "Entity.h"
#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(Image &image, float X, float Y, float W, float H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	

		money = -4;  photo = 2; money1 = 1000;
		state = stay; // объект стоит на месте
		if (name == "Pacman") {
			sprite.setTextureRect(IntRect(0, 0, w, h)); //«адаем спрайту один пр€моугольник дл€ вывода одного игрока. IntRect Ц дл€ приведени€ типов
		}
}
	void Player::control() { // управление персом
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}

	void Player::checkCollisionWithMap(float Dx, float Dy)
	{

		for (int i = y / 37; i < (y + h) / 37; i++)//проходимс€ по элементам карты
			for (int j = x / 37; j < (x + w) / 37; j++)
			{
				if (TileMap[i][j] == '0')//если элемент - стена
				{
					if (Dy > 0) { y = i * 37 - h;  dy = 0; }//по Y 
					if (Dy < 0) { y = i * 37 + 37; dy = 0; }//столкновение с верхними кра€ми 
					if (Dx > 0) { x = j * 37 - w; dx = 0; }//с правым краем карты
					if (Dx < 0) { x = j * 37 + 37; dx = 0; }// с левым краем карты
				}
				if (TileMap[i][j] == 'h') { //если символ равен 'h' (money)
					money += 1;// +1 money
					TileMap[i][j] = ' ';//убираем money, ставим пустой/свободный элемент пол€
				}
			}
	}

	void Player::update(float time) //функци€ "оживлени€/обновлени€" объекта класса. ѕринимает в себ€ 
							//врем€ SFML, вследствие чего работает бесконечно, дава€ персонажу движение.
	{
		if (life) { // а герой жив?
			control(); // управление персом, оќ перс жив!!!
			switch (state)//реализуем поведение в зависимости от направлени€.  ажда€ цифра соответствует направлению. ну или не цифра, а кнопка))
			{

			case right: {//состо€ние идти вправо
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 35, 35));
				break;
			}
			case left: {//состо€ние идти влево
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 35, 35, 35));
				break;
			}
			case up: {//идти вверх
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(70, 35 * int(CurrentFrame), 35, 35));
				break;
			}
			case down: {//идти вниз
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(105, 35 * int(CurrentFrame), 35, 35));
				break;
			}
			case stay: {//стоим, отдыхаем
				dy = speed;
				dx = speed;
				break;
			}
			}
			x += dx*time; //движение по УXФ
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
			y += dy*time; //движение по УYФ
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			speed = 0;    //обнул€ем скорость, чтобы персонаж остановилс€.

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

			if (health <= 0) { life = false; }//тип игрок умер
		}
	}


