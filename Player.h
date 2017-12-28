#ifndef Player_h
#define Player_h

using namespace sf;
class Player :public Entity { 
public:// класс їгрока
	int  money, photo, money1; // игровые очки, кол-во кадров дл€ анимации движени€,переменна€ с "жизнью", кол-во очков до победы

							   // онструктор с параметрами дл€ класса Player
	
	Player(Image &image, float X, float Y, float W, float H, std::string Name) ;
	void control();
	//ћетод проверки столкновений с элементами карты
	void checkCollisionWithMap(float Dx, float Dy);

	void update(float time);
};
#endif