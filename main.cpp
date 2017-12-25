
#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой

using namespace sf;
////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
private:
	float x, y;
public:
	float  w, h, dx, dy, speed; //координаты игрока х и у, высота и ширина, 
										 //ускорение (по х и по у), сама скорость
	int dir, money, maxObj, photo = 2; //направление (direction) движения игрока, игровые очки, кол-во объектов на карте, кол-во кадров для анимации движения.
	bool life;//жизнь перса
	float CurrentFrame = 0; //хранитекущий кадр
	enum { left, right, up, down, stay } state;// перечисления состояния объекта
	std::string File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 


				  //Конструктор с параметрами для класса Player. При создании объекта класса мы будем задавать //имя файла, координату Х и У, ширину и высоту
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; speed = 0;  money = -4; dy = 0; dx = 0;
		life = true;
		maxObj = 0;
		File = F; //имя файла+расширение
		w = W; h = H; //высота и ширина
		image.loadFromFile("images/" + File);//загружаем в image изображение, вместо File
											 //передадим то, что пропишем при создании объекта. В нашем случае это "hero.png". Получится
											 //запись, идентичная image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(0, 0, 0)); //убираем ненужный black color
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
		x = X; y = Y; //координата появления спрайта
		sprite.setTextureRect(IntRect(0.0, 0.0, w, h));
		//Задаем спрайту один прямоугольник для
		//вывода одного льва. IntRect – для приведения типов
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


void update(float time) //функция "оживления/обновления" объекта класса. Принимает в себя 
							//время SFML, вследствие чего работает бесконечно, давая персонажу движение.
	{
		if (life) {
			control(); // управление персом
			switch (state)//реализуем поведение в зависимости от направления. Каждая цифра
						//соответствует направлению.
			{

			case right: {//состояние идти вправо
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > photo) CurrentFrame -= photo;
				sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 35, 35));
				break;
			}
			case left: {//состояние идти влево
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
			case stay: {//стоим
				dy = speed;
				dx = speed;
				break;
			}
			}
			x += dx*time; //движение по “X”
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			y += dy*time; //движение по “Y”
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
						  //state = stay; //состояние - стоим

			sprite.setPosition(x, y); //спрайт в позиции (x, y).
		}
	}
			
	//Метод проверки столкновений с элементами карты
void checkCollisionWithMap(float Dx, float Dy) 
	{
		for (int i = y / 37; i < (y + h) / 37; i++)//проходимся по элементам карты
			for (int j = x / 37; j<(x + w) / 37; j++)
			{
				if (TileMap[i][j] == '0')//если элемент тайлик земли
				{
					if (Dy > 0) { y = i * 37 - h;  dy = 0; }//по Y 
					if (Dy < 0) { y = i * 37 + 37; dy = 0; }//столкновение с верхними краями 
					if (Dx > 0) { x = j * 37 - w; dx = 0; }//с правым краем карты
					if (Dx < 0) { x = j * 37 + 37; dx = 0; }// с левым краем карты
				}
				if (TileMap[i][j] == 'h') { //если символ равен 'h' (money)
					money += 1;// +1 money
					TileMap[i][j] = ' ';//убираем money

				}
			}
	}

	FloatRect getRect() {//метод получения прямоугольника. его коорд, размеры (шир,высот).
		FloatRect FR(x, y, w, h);
		return FR;
		//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
		//в нашей игре это координаты текущего расположения тайла на карте
		//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
		//эта ф-ция нужна для проверки пересечений	
	}
};






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

	Player p("pacman.png", 250, 250, 35.0, 35.0);//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

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
			randomMapGenerate();
			//генерация health
			createObjectForMapTimer = 1;//обнуляем health
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
						// передавая время в качестве параметра функции update. 
		window.clear();
	
	/////////////////////////////Рисуем карту/////////////////////
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 37, 37)); //если
																					//встретили символ пробел, то рисуем 1-й квадратик
			if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(37, 0, 37, 37));//если
																					//встретили символ h, то рисуем 2й квадратик - money 
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(74, 0, 37, 37));//если 0 - stena



			s_map.setPosition(j * 37, i * 37);//раскладываем квадратики в карту.

			window.draw(s_map);//рисуем квадратики на экран
		}
	std::ostringstream playerMoneyString, gameTimeString;//объявили переменную здоровья и времени
	playerMoneyString << p.money; gameTimeString << gameTime;//формируем строку
	text.setString("Время игры: " + gameTimeString.str());
	text.setPosition(500, 10);//задаем позицию текста
	window.draw(text);//рисуем этот текст

	text.setString("Money: " + playerMoneyString.str());
	text.setPosition(50, 10);//задаем позицию текста
	window.draw(text);//рисуем этот текст

	if (p.money > 1000) {
		window.clear();
		text.setString("YOU WIN");
		text.setPosition(300, 200);//задаем позицию текста
		window.draw(text);//рисуем этот текст
	}


	window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
	window.display();
}
	return 0;
}
