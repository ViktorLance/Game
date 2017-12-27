
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������
#include <list>
#include "Global.h"


using namespace sf;

////////////////////////////����� ��������////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay } state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health; //������ �������,���������� �health�, �������� ����� ������
	bool life; //���������� �life� �����, ����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 
	float CurrentFrame;//������ ������� ����
	std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������
					 //������� ����� ���� ���� �������� � update() � ����������� �� �����

	Entity(Image &image, float X, float Y, int W, int H, std::string Name) {
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
	}

	FloatRect getRect() {//����� ��������� ��������������. ��� �����, ������� (���,�����).
		FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect
		return FR;
		//return FloatRect(x, y, w, h);
		//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
		//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
		//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
		//��� �-��� ����� ��� �������� ����������� 
	}
	virtual void update(float time) = 0;
};



////////////////////////////����� ������////////////////////////
class Player:public Entity { // ����� ������
public:

	int  money, photo, money1; // ������� ����, ���-�� ������ ��� �������� ��������,���������� � "������", ���-�� ����� �� ������

				  //����������� � ����������� ��� ������ Player
	Player(Image &image, float X, float Y, float W, float H, std::string Name ) :Entity(image, X, Y, W, H, Name) {
		money = -4;  photo = 2; money1 = 1000;
		  state = stay; // ������ ����� �� �����
		  if (name == "Pacman") {
			  sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� �����
		  }
	}

	void control() { // ���������� ������
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

	//����� �������� ������������ � ���������� �����
	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 37; i < (y + h) / 37; i++)//���������� �� ��������� �����
			for (int j = x / 37; j<(x + w) / 37; j++)
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

void update(float time) //������� "���������/����������" ������� ������. ��������� � ���� 
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
};


////////////////////////////����� �����////////////////////////
class Enemy :public Entity {
public:
	int direction;//����������� �������� �����
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name) {
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

	void checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
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

	void update(float time)
	{
		if (name == "Enemy1") {//��� ��������� � ����� ������ ������ ����� �����

			if (life) {//���������, ��� �� �����
				switch (direction)//�������� ��������� �������� � ����������� �� ���������
				{
				case 0: {//��������� ���� ������
					dx = speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					sprite.setTextureRect(IntRect(0 , 0, 35, 35));
					break;
				}
				case 1: {//��������� ���� �����
					dx = -speed;
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					sprite.setTextureRect(IntRect(33 , 0, 35, 35));
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
};//����� Enemy ������




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

	Image heroImage;
	heroImage.loadFromFile("images/pacman.png");// �������� ����������� ������
	Image EnemyImage[3];
	EnemyImage[2].loadFromFile("images/enemypac.png"); // ��������� ����������� �����
	EnemyImage[1].loadFromFile("images/enemypac1.png"); // ��������� ����������� �����
	EnemyImage[0].loadFromFile("images/enemypac2.png"); // ��������� ����������� �����


	Player p(heroImage, 250, 250, 35, 35, "Pacman");
	
	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������

	const int ENEMY_COUNT = 3;	//������������ ���������� ������ � ����
	int enemiesCount = 0;      //������� ���������� ������ � ����

							   //��������� ������ ��������� �������
	for (int i = 0; i < ENEMY_COUNT ; i++)
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

		if (p.health <= 1 ) {// �� ��� ���� ������, ���� 1000 ������ �������...
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
