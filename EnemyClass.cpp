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
		//������ ������� ���� ������������� ���
		//������ ������ ������. IntRect � ��� ���������� �����
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (3); //����������� �������� ����� ����� ��������� �������
								  //����� ��������� ��������� �����
		speed = 0.1;//���� ��������.���� ������ ������ ���������
		dx = speed;
	}
}
void Enemy::checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
{
	for (int i = y / 37; i < (y + h) / 37; i++)//���������� �� ��������� �����
		for (int j = x / 37; j<(x + w) / 37; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� - ������ �����
			{
				if (Dy > 0) {
					y = i * 37 - h;  dy = -0.1;
					direction = rand() % (4); //����������� �������� �����
				}//�� Y 
				if (Dy < 0) {
					y = i * 37 + 37; dy = 0.1;
					direction = rand() % (4);//����������� �������� ����� 
				}//������������ � �������� ������ 
				if (Dx > 0) {
					x = j * 37 - w; dx = -0.1;
					direction = rand() % (4);//����������� �������� ����� 
				}//� ������ ����� �����
				if (Dx < 0) {
					x = j * 37 + 37; dx = 0.1;
					direction = rand() % (4); //����������� �������� �����
				}// � ����� ����� �����
			}
		}
}
void Enemy::update(float time)
{
	if (name == "Enemy1") {//��� ��������� � ����� ������ ������ ����� �����

		if (life) {//���������, ��� �� �����
			switch (direction)//�������� ��������� �������� � ����������� �� ���������
			{
			case 0: {//��������� ���� ������
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(0, 0, 35, 35));
				break;
			}
			case 1: {//��������� ���� �����
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(33, 0, 35, 35));
				break;
			}
			case 2: {//���� �����
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(65, 0, 35, 35));
				break;
			}
			case 3: {//���� ����
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(100, 0, 35, 35));
				break;
			}
			}

			x += dx*time; //�������� �� �X�
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �

			y += dy*time; //�������� �� �Y�
			checkCollisionWithMap(0, dy);//������������ ������������ �� Y

			sprite.setPosition(x, y); //������ � ������� (x, y).

			if (health <= 0) { life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
		}
	}
}