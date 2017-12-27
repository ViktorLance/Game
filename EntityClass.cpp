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
	x = X; y = Y; //���������� ��������� �������
	w = W; h = H; //������ �������
	name = Name; // ��� ���������
	moveTimer = 0; //
	dx = 0; dy = 0;
	speed = 0;
	CurrentFrame = 0;
	health = 100;
	life = true; //���������������� ���������� ���������� �����, ����� ���
	image.createMaskFromColor(Color(0, 0, 0)); //������� �������� black color, � ������, �.�. � ���� ������ ���� ������ ������ ����.
	texture.loadFromImage(image); //������� ���� ����������� � ��������
	sprite.setTexture(texture); //�������� ������ ���������
};