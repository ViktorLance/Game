
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
	int dir, money, maxObj, photo = 2; //����������� (direction) �������� ������, ������� ����, ���-�� �������� �� �����, ���-�� ������ ��� �������� ��������.
	bool life;//����� �����
	float CurrentFrame = 0; //������������ ����
	enum { left, right, up, down, stay } state;// ������������ ��������� �������
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

	void control() {
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


void update(float time) //������� "���������/����������" ������� ������. ��������� � ���� 
							//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		if (life) {
			control(); // ���������� ������
			switch (state)//��������� ��������� � ����������� �� �����������. ������ �����
						//������������� �����������.
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
			case stay: {//�����
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
						  //state = stay; //��������� - �����

			sprite.setPosition(x, y); //������ � ������� (x, y).
		}
	}
			
	//����� �������� ������������ � ���������� �����
void checkCollisionWithMap(float Dx, float Dy) 
	{
		for (int i = y / 37; i < (y + h) / 37; i++)//���������� �� ��������� �����
			for (int j = x / 37; j<(x + w) / 37; j++)
			{
				if (TileMap[i][j] == '0')//���� ������� ������ �����
				{
					if (Dy > 0) { y = i * 37 - h;  dy = 0; }//�� Y 
					if (Dy < 0) { y = i * 37 + 37; dy = 0; }//������������ � �������� ������ 
					if (Dx > 0) { x = j * 37 - w; dx = 0; }//� ������ ����� �����
					if (Dx < 0) { x = j * 37 + 37; dx = 0; }// � ����� ����� �����
				}
				if (TileMap[i][j] == 'h') { //���� ������ ����� 'h' (money)
					money += 1;// +1 money
					TileMap[i][j] = ' ';//������� money

				}
			}
	}

	FloatRect getRect() {//����� ��������� ��������������. ��� �����, ������� (���,�����).
		FloatRect FR(x, y, w, h);
		return FR;
		//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
		//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
		//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
		//��� �-��� ����� ��� �������� �����������	
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

		p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml,
						// ��������� ����� � �������� ��������� ������� update. 
		window.clear();
	
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

	if (p.money > 1000) {
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
