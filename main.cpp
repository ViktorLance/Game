#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������

using namespace sf;
////////////////////////////����� ������////////////////////////
class Player { // ����� ������
public:
	float x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ � ������, 
										 //��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	std::string File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 


				  //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� //��� �����, ���������� � � �, ������ � ������
	Player(std::string F, float X, float Y, float W, float H) {
		File = F; //��� �����+����������
		w = W; h = H; //������ � ������
		image.loadFromFile("images/" + File);//��������� � image �����������, ������ File
											 //��������� ��, ��� �������� ��� �������� �������. � ����� ������ ��� "hero.png". ���������
											 //������, ���������� image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(0, 0, 0)); //������� �������� �����-����� ����
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
		x = X; y = Y; //���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));
		//������ ������� ���� ������������� ���
		//������ ������ ����. IntRect � ��� ���������� �����
	}

	void update(float time) //������� "���������/����������" ������� ������. ��������� � ���� 
							//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. ������ �����
					//������������� �����������.
		{
		case 0: dx = speed; dy = 0; break; //�� �X� ������ ������������� ��������, �� �Y� - 0. 
										   //�������� ���� ������ ������.
		case 1: dx = -speed; dy = 0; break;//�� �X� ������ ������������� ��������, �� � �Y� � 0.
										   //�������� ���� ������ �����.
		case 2: dx = 0; dy = speed; break;//�� �X� ������ ������� ��������, �� �Y�
										  //�������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed; break;//�� �X� ������ ������� ��������, �� �Y�
										   //�������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx*time; //�������� �� �X�
		y += dy*time; //�������� �� �Y�
		speed = 0;    //�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� (x, y). 
								  //���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	}
};

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(742, 555, desktop.bitsPerPixel), "Lesson 8");

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/mappac.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	float CurrentFrame = 0;//������ ������� ����
	Clock clock;

	Player p("pacman.png", 270, 250, 35.0, 35.0);//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/////////////////////////���������� ���������� � ���������//////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.
									 //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 35, 33, 33)); //����� ������ p
																				  //������ player ������ ������, ����� �������� 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;//����������� ������
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 33, 33)); //����� ������ p 								//������ player ������ ������, ����� �������� 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;//����������� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(70, 35 * int(CurrentFrame), 33, 33)); //����� ������ p 				//������ player ������ ������, ����� �������� (��������� �������� �����)

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			p.dir = 2; p.speed = 0.1;//����������� �����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(105, 35 * int(CurrentFrame), 33, 33));
		}

		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 

		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 37, 37)); //����
																						//��������� ������ ������, �� ������ 1-� ���������
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(37, 0, 37, 37));//����
																						//��������� ������ s, �� ������ 2� ���������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(74, 0, 37, 37));//����
																						 //��������� ������ 0, �� ������ 3� ���������


				s_map.setPosition(j * 37, i * 37);//������������ ���������� � �����.

				window.draw(s_map);//������ ���������� �� �����
			}

		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		window.display();
	}
	return 0;
}




