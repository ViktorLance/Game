
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
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

	Font font;//шрифт 
	font.loadFromFile("mysor/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(Color::White);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый


	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/mappac.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом


	Clock clock;
	Clock gameTimeClock;//хранит игровое время
	int gameTime = 0; //игровое время


	Image EnemyImage[3];
	EnemyImage[2].loadFromFile("images/enemypac.png"); // загружаем изображение врага
	EnemyImage[1].loadFromFile("images/enemypac1.png"); // загружаем изображение врага
	EnemyImage[0].loadFromFile("images/enemypac2.png"); // загружаем изображение врага

	Image image_pac;
	image_pac.loadFromFile("images/pacman.png");// загрузка изображения игрока

	Player p(image_pac, 250, 250, 35, 35, "Pacman");

	std::list<Entity*>  enemies; //список врагов
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка

	const int ENEMY_COUNT = 3;	//максимальное количество врагов в игре
	int enemiesCount = 0;      //текущее количество врагов в игре

							   //Заполняем список объектами врагами
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		float xr = 150 + rand() % 500; //случайная координата врага на поле игры по оси “x”
		float yr = 150 + rand() % 350; //случайная координата врага на поле игры по оси “y”
									   //создаем врагов и помещаем в список
		enemies.push_back(new Enemy(EnemyImage[i], xr, yr, 35, 35, "Enemy1"));
		enemiesCount += 1; //увеличили счётчик врагов
	}

	int createObjectForMapTimer = 0;//Переменная под время для генерирования камней

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		//игровое время в секундах идёт вперед, пока жив игрок. 
		//Перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//наращиваем таймер


		if (createObjectForMapTimer > 60) { //60000 = 1 min
			randomMapGenerate();//генерация money
			createObjectForMapTimer = 1;//обнуляем timer of money object on map
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
						// передавая время в качестве параметра функции update. 

						//оживляем врагов
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}

		//Проверка пересечения игрока с врагами
		//Если пересечение произошло, то "health = 0", игрок обездвижевается и 
		//выводится сообщение "you are lose"
		if (p.life == true) {//если игрок жив
			for (it = enemies.begin(); it != enemies.end(); it++) {//бежим по списку врагов
				if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "Enemy1"))
				{
					p.health = 0;
					std::cout << "you are lose";
				}
			}
		}

		window.clear();// чистим экран 

	/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 37, 37)); //если встретили символ пробел, то рисуем 1-й квадратик - свободную клетку поля
				if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(37, 0, 37, 37));//если встретили символ "h", то рисуем 2й квадратик - money 
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(74, 0, 37, 37));//если "0" ... - stena

				s_map.setPosition(j * 37, i * 37);//раскладываем квадратики в карту.

				window.draw(s_map);//рисуем квадратики на экран
			}
		std::ostringstream playerMoneyString, gameTimeString, playerHealthString;//объявили переменную здоровья и времени
		playerMoneyString << p.money; gameTimeString << gameTime, playerHealthString << p.health;;//формируем строки

		text.setString("Время игры: " + gameTimeString.str());
		text.setPosition(500, 10);//задаем позицию текста
		window.draw(text);//рисуем этот текст

		text.setString("Money: " + playerMoneyString.str());
		text.setPosition(50, 10);//задаем позицию текста
		window.draw(text);//рисуем этот текст

		text.setString("Health: " + playerHealthString.str());
		text.setPosition(250, 10);//задаем позицию текста
		window.draw(text);//рисуем этот текст

		if (p.health <= 1) {// ну тип игру прошли, если 1000 рублей собрали...
			window.clear();
			text.setString("YOU LOSE");
			text.setPosition(300, 200);//задаем позицию текста
			window.draw(text);//рисуем этот текст
		}

		if (p.money > p.money1) {// ну тип игру прошли, если 1000 рублей собрали...
			window.clear();
			text.setString("YOU WIN");
			text.setPosition(300, 200);//задаем позицию текста
			window.draw(text);//рисуем этот текст
		}

		if ((p.money < p.money1) && (p.health > 0)) {
			window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
								  //рисуем врагов
		}
		if ((p.money < p.money1) && (p.health > 0)) {
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				window.draw((*it)->sprite); //рисуем enemies объекты
			}
		}

		window.display();
	}
	return 0;
}