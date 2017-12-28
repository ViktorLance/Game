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
		state = stay; // ������ ����� �� �����
		if (name == "Pacman") {
			sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� �����
		}
}
	void Player::control() { // ���������� ������
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

		for (int i = y / 37; i < (y + h) / 37; i++)//���������� �� ��������� �����
			for (int j = x / 37; j < (x + w) / 37; j++)
			{
				if (TileMap[i][j] == '0')//���� ������� - �����
				{
					if (Dy > 0) { y = i * 37 - h;  dy = 0; }//�� Y 
					if (Dy < 0) { y = i * 37 + 37; dy = 0; }//������������ � �������� ������ 
					if (Dx > 0) { x = j * 37 - w; dx = 0; }//� ������ ����� �����
					if (Dx < 0) { x = j * 37 + 37; dx = 0; }// � ����� ����� �����
				}
				if (TileMap[i][j] == 'h') { //���� ������ ����� 'h' (money)
					money += 1;// +1 money
					TileMap[i][j] = ' ';//������� money, ������ ������/��������� ������� ����
				}
			}
	}

	void Player::update(float time) //������� "���������/����������" ������� ������. ��������� � ���� 
							//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		if (life) { // � ����� ���?
			control(); // ���������� ������, �� ���� ���!!!
			switch (state)//��������� ��������� � ����������� �� �����������. ������ ����� ������������� �����������. �� ��� �� �����, � ������))
			{

			case right: {//��������� ���� ������
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 35, 35));
				break;
			}
			case left: {//��������� ���� �����
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 35, 35, 35));
				break;
			}
			case up: {//���� �����
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(70, 35 * int(CurrentFrame), 35, 35));
				break;
			}
			case down: {//���� ����
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(105, 35 * int(CurrentFrame), 35, 35));
				break;
			}
			case stay: {//�����, ��������
				dy = speed;
				dx = speed;
				break;
			}
			}
			x += dx*time; //�������� �� �X�
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			y += dy*time; //�������� �� �Y�
			checkCollisionWithMap(0, dy);//������������ ������������ �� Y

			speed = 0;    //�������� ��������, ����� �������� �����������.

			sprite.setPosition(x, y); //������ � ������� (x, y).

			if (health <= 0) { life = false; }//��� ����� ����
		}
	}


