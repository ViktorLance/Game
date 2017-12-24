//*
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������

using namespace sf;
////////////////////////////����� ������////////////////////////
class Player { // ����� ������
private: 
	float x, y;
public:
	float  w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������, 
										 //��������� (�� � � �� �), ���� ��������
	int dir, money, maxObj; //����������� (direction) �������� ������, ������� ����, ���������� ��� �������� ���-�� �����
	bool life;//����� �����
	std::string File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 


				  //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� //��� �����, ���������� � � �, ������ � ������
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; speed = 0;  money = -4; dy = 0; dx = 0;
		life = true;
		maxObj = 0;
		File = F; //��� �����+����������
		w = W; h = H; //������ � ������
		image.loadFromFile("images/" + File);//��������� � image �����������, ������ File
											 //��������� ��, ��� �������� ��� �������� �������. � ����� ������ ��� "hero.png". ���������
											 //������, ���������� image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(0, 0, 0)); //������� �������� black color
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
		x = X; y = Y; //���������� ��������� �������
		sprite.setTextureRect(IntRect(0.0, 0.0, w, h));
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
		interactionWithMap();//�������� �������, ���������� �� �������������� � ������
		
	}


	void interactionWithMap()//�-��� �������������� � ������
	{
		//�������� ������ �� ��� ������ (����������� ������� 32*32), ������� ������������ � �������.
		//�������� ��� ��������� ��������� ��� ������������ ������! 
		for (int i = y / 37; i < (y + h) / 37; i++)
			for (int j = x / 37; j<(x + w) / 37; j++) {
				//�x� ����� �� 37, ��� ����� �������� ����� ���������, � ������� �������� �������������. 
				//�� ���� ������ ������� 37*37, ������� ����� ������������ ������ �� ���������� ������
				//����� ����, j<(x + w)/37 - ������� ����������� ��������� �� �x�, �.�. ���������� ������
				//������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� �����
				// ������� �� ����, ������� �� ������ �������� (���������������� � ������), �� �������
				// �������� (���������������� � ������)
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� �0�
										 //(�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0) {//���� �� ��� ����,
						y = i * 37 - h;//�� �������� (-h) ���������� �y� ���������. 
									   //������� �������� ���������� �i� ������ ���������� �� ����� � 
									   //����� �������� �� ������ ������� ���������.
					}
					if (dy<0) {
						y = i * 37 + 37;//���������� � ��������� �����.	
					}
					if (dx>0) {
						x = j * 37 - w;//���� ���� ������, �� ���������� �x� ����� 
									   //����� (������ 0) ����� ������ ���������
					}
					if (dx < 0) {
						x = j * 37 + 37; //���������� ���� �����
					}
				}
				
				if (TileMap[i][j] == 'h') { //���� ������ ����� 'h' (money)
					money += 1;// +1 money
					TileMap[i][j] = ' ';//������� money
				}

			}
	}
};

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

	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Clock gameTimeClock;//������ ������� �����
	int gameTime = 0; //������� �����

	Player p("pacman.png", 250, 250, 35.0, 35.0);//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

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
			randomMapGenerate();
			//��������� health
			createObjectForMapTimer = 1;//�������� health
		}
		


		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		/////////////////////////���������� ���������� � ���������//////////////////////////////////
		if (p.life)
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.
										 //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
				CurrentFrame += 0.005*time; //���-�� ���� ���, ��� ������ ���������, ��� ������ ������ ������������ 
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 35, 35, 35)); 				//����� ������ p
																									//������ player ������ ������, ����� �������� 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				p.dir = 0; p.speed = 0.1;//����������� ������
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 35, 35)); //����� ������ p 								//������ player ������ ������, ����� �������� 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				p.dir = 3; p.speed = 0.1;//����������� �����
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(70, 35 * int(CurrentFrame), 35, 35)); //����� ������ p 				//������ player ������ ������, ����� �������� (��������� �������� �����)

			}

			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				p.dir = 2; p.speed = 0.1;//����������� ����
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(105, 35 * int(CurrentFrame), 35, 35));
			}

			p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
							// ��������� ����� � �������� ��������� ������� update. 

			window.clear();
		}
		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 37, 37)); //����
																						//��������� ������ ������, �� ������ 1-� ���������
				if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(37, 0, 37, 37));//����
																						//��������� ������ h, �� ������ 2� ��������� - money 
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(74, 0, 37, 37));//���� 0 - stena
		


				s_map.setPosition(j * 37, i * 37);//������������ ���������� � �����.

				window.draw(s_map);//������ ���������� �� �����
			}
		std::ostringstream playerMoneyString, gameTimeString;//�������� ���������� �������� � �������
		playerMoneyString << p.money; gameTimeString << gameTime;//��������� ������
		text.setString("����� ����: " + gameTimeString.str()); 
		text.setPosition(500, 10);//������ ������� ������
		window.draw(text);//������ ���� �����

		text.setString("Money: " + playerMoneyString.str());
		text.setPosition(50, 10);//������ ������� ������
		window.draw(text);//������ ���� �����

		if (p.money > 10) {
			window.clear();
			text.setString("YOU WIN");
			text.setPosition(300, 200);//������ ������� ������
			window.draw(text);//������ ���� �����
		}


		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		window.display();
	}
	return 0;
}
//*/

/*
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������

using namespace sf;
////////////////////////////����� ������////////////////////////
class Player { // ����� ������
private: float x, y;
public:
	float w, h, dx, dy, speed; //���������� ������ � � �, ������ � ������, 
							   //��������� (�� � � �� �), ���� ��������
	int dir, playerScore, health;//����� ���������� �health�, �������� ����� ������ 
	bool life;//���������� �life� �����, ����������
	std::string File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 


				  //����������� � ����������� ��� ������ Player. ��� �������� ������� ������ �� ����� �������� //��� �����, ���������� � � �, ������ � ������
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; playerScore = 0;
		dx = 0; dy = 0; speed = 0;
		health = 100;
		//���������������� ���������� ����� � ������������
		life = true;//���������������� ���������� ���������� �����
		File = F; //��� �����+����������
		w = W; h = H; //������ � ������
		image.loadFromFile("images/" + File);//��������� � image �����������, ������ File
											 //��������� ��, ��� �������� ��� �������� �������. � ����� ������ ��� "hero.png". ���������
											 //������, ���������� image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59)); //������� �������� �����-����� ����
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
		interactionWithMap();//�������� �������, ���������� �� �������������� � ������
		if (health <= 0) { life = false; }//���� ������ ������ ���� ����� 0, �� ������� 
	}


	void interactionWithMap()//�-��� �������������� � ������
	{
		//�������� ������ �� ��� ������ (����������� ������� 32*32), ������� ������������ � �������.
		//�������� ��� ��������� ��������� ��� ������������ ������! 
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++) {
				//�x� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. 
				//�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ������
				//����� ����, j<(x + w)/32 - ������� ����������� ��������� �� �x�, �.�. ���������� ������
				//������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� �����
				// ������� �� ����, ������� �� ������ �������� (���������������� � ������), �� �������
				// �������� (���������������� � ������)
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� �0�
										 //(�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy>0) {//���� �� ��� ����,
						y = i * 32 - h;//�� �������� (-h) ���������� �y� ���������. 
									   //������� �������� ���������� �i� ������ ���������� �� ����� � 
									   //����� �������� �� ������ ������� ���������.
					}
					if (dy<0) {
						y = i * 32 + 32;//���������� � ��������� �����.	
					}
					if (dx>0) {
						x = j * 32 - w;//���� ���� ������, �� ���������� �x� ����� 
									   //����� (������ 0) ����� ������ ���������
					}
					if (dx < 0) {
						x = j * 32 + 32; //���������� ���� �����
					}
				}
				if (TileMap[i][j] == 's') {
					playerScore++; //���� ����� ������, ���������� playerScore=playerScore+1;
					TileMap[i][j] = ' ';
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//���� ����� �������� ������,�� ���������� health=health-40;
					TileMap[i][j] = ' ';//������ ������
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//���� ����� ��������,�� ���������� health=health+20;
					TileMap[i][j] = ' ';//������ ��������
				}

			}
	}

};

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 11");

	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ������ ������(� ��������);
							//��� ������ ����� (�� ������)
	text.setFillColor(Color::Red);//��������� ����� � �������.
	text.setStyle(Text::Bold);//������ �����.


	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map_new.png");//��������� ����� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.

	Player p("hero.png", 250, 250, 96.0, 96.0);//������� ������ p ������ player, 
											   //������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		//������� ����� � �������� ��� ������, ���� ��� �����. 
		//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����

		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/////////////////////////���������� ���������� � ���������//////////////////////////////////
		if (p.life) {
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.
										 //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //����� ������ p
																					  //������ player ������ ������, ����� �������� 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				p.dir = 0; p.speed = 0.1;//����������� ������
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //����� ������ p 				//������ player ������ ������, ����� �������� 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				p.dir = 3; p.speed = 0.1;//����������� ����
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); //����� ������ p 	//������ player ������ ������, ����� �������� (��������� �������� �����)
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				p.dir = 2; p.speed = 0.1;//����������� �����
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			}
		}
		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 

		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//������
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//������
				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}

		std::ostringstream playerHealthString, gameTimeString;//�������� ���������� �������� � �������
		playerHealthString << p.health; gameTimeString << gameTime;//��������� ������
		text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str());//������ ������ ������
		text.setPosition(50, 50);//������ ������� ������
		window.draw(text);//������ ���� �����


		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�
		window.display();
	}
	return 0;
}
*/


