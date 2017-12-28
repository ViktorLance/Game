
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������
#include <list>
#include "Global.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;

int main()
{

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(742, 555, desktop.bitsPerPixel), "PACMAN");

	Font font;//����� 
	font.loadFromFile("mysor/CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(Color::White);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������


	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/mappac.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������


	Clock clock;
	Clock gameTimeClock;//������ ������� �����
	int gameTime = 0; //������� �����


	Image EnemyImage[3];
	EnemyImage[2].loadFromFile("images/enemypac.png"); // ��������� ����������� �����
	EnemyImage[1].loadFromFile("images/enemypac1.png"); // ��������� ����������� �����
	EnemyImage[0].loadFromFile("images/enemypac2.png"); // ��������� ����������� �����

	Image image_pac;
	image_pac.loadFromFile("images/pacman.png");// �������� ����������� ������

	Player p(image_pac, 250, 250, 35, 35, "Pacman");

	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������

	const int ENEMY_COUNT = 3;	//������������ ���������� ������ � ����
	int enemiesCount = 0;      //������� ���������� ������ � ����

							   //��������� ������ ��������� �������
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		float xr = 150 + rand() % 500; //��������� ���������� ����� �� ���� ���� �� ��� �x�
		float yr = 150 + rand() % 350; //��������� ���������� ����� �� ���� ���� �� ��� �y�
									   //������� ������ � �������� � ������
		enemies.push_back(new Enemy(EnemyImage[i], xr, yr, 35, 35, "Enemy1"));
		enemiesCount += 1; //��������� ������� ������
	}

	int createObjectForMapTimer = 0;//���������� ��� ����� ��� ������������� ������

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		//������� ����� � �������� ��� ������, ���� ��� �����. 
		//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//���������� ������


		if (createObjectForMapTimer > 60) { //60000 = 1 min
			randomMapGenerate();//��������� money
			createObjectForMapTimer = 1;//�������� timer of money object on map
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 

						//�������� ������
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //��������� ����� update()
		}

		//�������� ����������� ������ � �������
		//���� ����������� ���������, �� "health = 0", ����� ��������������� � 
		//��������� ��������� "you are lose"
		if (p.life == true) {//���� ����� ���
			for (it = enemies.begin(); it != enemies.end(); it++) {//����� �� ������ ������
				if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "Enemy1"))
				{
					p.health = 0;
					std::cout << "you are lose";
				}
			}
		}

		window.clear();// ������ ����� 

	/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 37, 37)); //���� ��������� ������ ������, �� ������ 1-� ��������� - ��������� ������ ����
				if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(37, 0, 37, 37));//���� ��������� ������ "h", �� ������ 2� ��������� - money 
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(74, 0, 37, 37));//���� "0" ... - stena

				s_map.setPosition(j * 37, i * 37);//������������ ���������� � �����.

				window.draw(s_map);//������ ���������� �� �����
			}
		std::ostringstream playerMoneyString, gameTimeString, playerHealthString;//�������� ���������� �������� � �������
		playerMoneyString << p.money; gameTimeString << gameTime, playerHealthString << p.health;;//��������� ������

		text.setString("����� ����: " + gameTimeString.str());
		text.setPosition(500, 10);//������ ������� ������
		window.draw(text);//������ ���� �����

		text.setString("Money: " + playerMoneyString.str());
		text.setPosition(50, 10);//������ ������� ������
		window.draw(text);//������ ���� �����

		text.setString("Health: " + playerHealthString.str());
		text.setPosition(250, 10);//������ ������� ������
		window.draw(text);//������ ���� �����

		if (p.health <= 1) {// �� ��� ���� ������, ���� 1000 ������ �������...
			window.clear();
			text.setString("YOU LOSE");
			text.setPosition(300, 200);//������ ������� ������
			window.draw(text);//������ ���� �����
		}

		if (p.money > p.money1) {// �� ��� ���� ������, ���� 1000 ������ �������...
			window.clear();
			text.setString("YOU WIN");
			text.setPosition(300, 200);//������ ������� ������
			window.draw(text);//������ ���� �����
		}

		if ((p.money < p.money1) && (p.health > 0)) {
			window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
								  //������ ������
		}
		if ((p.money < p.money1) && (p.health > 0)) {
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				window.draw((*it)->sprite); //������ enemies �������
			}
		}

		window.display();
	}
	return 0;
}