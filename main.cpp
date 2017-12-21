#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace sf;
////////////////////////////КЛАСС ИГРОКА////////////////////////
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { // класс Игрока
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота и ширина, 
										 //ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	std::string File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 


				  //Конструктор с параметрами для класса Player. При создании объекта класса мы будем задавать //имя файла, координату Х и У, ширину и высоту
	Player(std::string F, float X, float Y, float W, float H) {
		File = F; //имя файла+расширение
		w = W; h = H; //высота и ширина
		image.loadFromFile("images/" + File);//загружаем в image изображение, вместо File
											 //передадим то, что пропишем при создании объекта. В нашем случае это "hero.png". Получится
											 //запись, идентичная image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59)); //убираем ненужный темно-синий цвет
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
		x = X; y = Y; //координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для
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
	}
};

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 7");

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	Player p("pacman.png", 250, 250, 35.0, 35.0);//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

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

		/////////////////////////Управление персонажем с анимацией//////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения.
									 //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 35, 35, 35)); //через объект p
																				  //класса player меняем спрайт, делая анимацию 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;//направление вправо
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(35 * int(CurrentFrame), 0, 35, 35)); //через объект p 								//класса player меняем спрайт, делая анимацию 
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;//направление вниз
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(70, 35 * int(CurrentFrame), 35, 35)); //через объект p 				//класса player меняем спрайт, делая анимацию (используя оператор точку)

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			p.dir = 2; p.speed = 0.1;//направление вверх
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			p.sprite.setTextureRect(IntRect(105, 35 * int(CurrentFrame),  35, 35));
		}

		p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml,
						// передавая время в качестве параметра функции update. 

		window.clear();
		window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”
		window.display();
	}
	return 0;
}



