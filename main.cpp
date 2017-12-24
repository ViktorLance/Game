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
	int dir,playerScore, health; //направление (direction) движения игрока, игровые очки, переменная для хранения кол-ва жизни
	bool life;//жизнь перса
	std::string File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 


				  //Конструктор с параметрами для класса Player. При создании объекта класса мы будем задавать //имя файла, координату Х и У, ширину и высоту
	Player(std::string F, float X, float Y, float W, float H) {
		dir = 0; speed = 0; playerScore = 0; health = 100; dy = 0; dx = 0;
		life = true;
		File = F; //имя файла+расширение
		w = W; h = H; //высота и ширина
		image.loadFromFile("images/" + File);//загружаем в image изображение, вместо File
											 //передадим то, что пропишем при создании объекта. В нашем случае это "hero.png". Получится
											 //запись, идентичная image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(0, 0, 0)); //убираем ненужный темно-синий цвет
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
		x = X; y = Y; //координата появления спрайта
		sprite.setTextureRect(IntRect(0.0, 0.0, w, h));
		//Задаем спрайту один прямоугольник для
		//вывода одного льва. IntRect – для приведения типов
	}

	void update(float time) //функция "оживления/обновления" объекта класса. Принимает в себя 
							//время SFML, вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. Каждая цифра
					//соответствует направлению.
		{
		case 0: dx = speed; dy = 0; break; //по “X” задаем положительную скорость, по “Y” - 0. 
										   //Персонаж идет только вправо.
		case 1: dx = -speed; dy = 0; break;//по “X” задаем отрицательную скорость, по и “Y” – 0.
										   //Персонаж идет только влево.
		case 2: dx = 0; dy = speed; break;//по “X” задаем нулевое значение, по “Y”
										  //положительное. Получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;//по “X” задаем нулевое значение, по “Y”
										   //отрицательное. Получается, что персонаж идет только вверх
		}

		x += dx*time; //движение по “X”
		y += dy*time; //движение по “Y”
		speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию (x, y). 
								  //бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
		if (health <= 0) { life = false;}
	}


	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		//Проходим только по тем тайлам (квадратикам размера 32*32), которые контактируют с игроком.
		//Частично или полностью находятся под изображением игрока! 
		for (int i = y / 37; i < (y + h) / 37; i++)
			for (int j = x / 37; j<(x + w) / 37; j++) {
				//”x” делим на 37, тем самым получаем левый квадратик, с которым персонаж соприкасается. 
				//Он ведь больше размера 37*37, поэтому может одновременно стоять на нескольких тайлах
				//Кроме того, j<(x + w)/37 - условие ограничения координат по “x”, т.е. координата самого
				//правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева
				// направо по иксу, проходя от левого квадрата (соприкасающегося с героем), до правого
				// квадрата (соприкасающегося с героем)
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу “0”
										 //(стена), то проверяем "направление скорости" персонажа:
				{
					if (dy>0) {//если мы шли вниз,
						y = i * 37 - h;//то стопорим (-h) координату “y” персонажа. 
									   //сначала получаем координату “i” нашего квадратика на карте и 
									   //затем вычитаем из высоты спрайта персонажа.
					}
					if (dy<0) {
						y = i * 37 + 37;//аналогично с движением вверх.	
					}
					if (dx>0) {
						x = j * 37 - w;//если идем вправо, то координата “x” равна 
									   //стена (символ 0) минус ширина персонажа
					}
					if (dx < 0) {
						x = j * 37 + 37; //аналогично идем влево
					}
				}
				if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
					playerScore++;//+ очко
					TileMap[i][j] = ' ';//убираем камень
				}
				if (TileMap[i][j] == 'f') { //если символ равен 's' (камень)
					health -= 50; // - 50 hp
					TileMap[i][j] = ' ';//убираем камень
				}
				if (TileMap[i][j] == 'h') { //если символ равен 's' (камень)
					health += 50;// +50 hp
					TileMap[i][j] = ' ';//убираем камень
				}

			}
	}
};

int main()
{

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(742, 555, desktop.bitsPerPixel), "Lesson 9");

	Font font;//шрифт 
	font.loadFromFile("mysor/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый


	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/mappac.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;
	Clock gameTimeClock;//хранит игровое время
	int gameTime = 0; //игровое время

	Player p("pacman.png", 250, 250, 35.0, 35.0);//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		//игровое время в секундах идёт вперед, пока жив игрок. 
		//Перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/////////////////////////Управление персонажем с анимацией//////////////////////////////////
		if (p.life)
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения.
										 //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
				CurrentFrame += 0.005*time; //что-то типо фпс, чем больше множитель, тем больше кадров вырисовывает 
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 35, 35, 35)); 				//через объект p
																									//класса player меняем спрайт, делая анимацию 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				p.dir = 0; p.speed = 0.1;//направление вправо
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 35, 35)); //через объект p 								//класса player меняем спрайт, делая анимацию 
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				p.dir = 3; p.speed = 0.1;//направление вверх
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(70, 35 * int(CurrentFrame), 35, 35)); //через объект p 				//класса player меняем спрайт, делая анимацию (используя оператор точку)

			}

			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				p.dir = 2; p.speed = 0.1;//направление вниз
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 2) CurrentFrame -= 2;
				p.sprite.setTextureRect(IntRect(105, 35 * int(CurrentFrame), 35, 35));
			}

			p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
							// передавая время в качестве параметра функции update. 

			window.clear();
		}
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 37, 37)); //если
																						//встретили символ пробел, то рисуем 1-й квадратик
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(37, 0, 37, 37));//если
																						//встретили символ s, то рисуем 2й квадратик
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(74, 0, 37, 37));//если
																						 //встретили символ 0, то рисуем 3й квадратик
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(111, 0, 37, 37));//цветок
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(148, 0, 37, 37));//сердце


				s_map.setPosition(j * 37, i * 37);//раскладываем квадратики в карту.

				window.draw(s_map);//рисуем квадратики на экран
			}
		std::ostringstream playerHealthString, gameTimeString;//объявили переменную здоровья и времени
		playerHealthString << p.health; gameTimeString << gameTime;//формируем строку
		text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str());//задаем строку тексту
		text.setPosition(50, 50);//задаем позицию текста
		window.draw(text);//рисуем этот текст

		window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
		window.display();
	}
	return 0;
}