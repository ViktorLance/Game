//////////////////////////// Ћј—— —”ўЌќ—“№////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечислени€ - состо€ние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер дл€ будущих целей
	int w, h, health; //переменна€ УhealthФ, хран€ща€ жизни игрока
	bool life; //переменна€ УlifeФ жизнь, логическа€
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
	//каждому можно дать свое действие в update() в зависимости от имени

	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
		x = X; y = Y; //координата по€влени€ спрайта
		w = W; h = H; 
		name = Name; 
		moveTimer = 0;
		dx = 0; dy = 0; 
		speed = 0; 
		CurrentFrame = 0;
		health = 100;
		life = true; //инициализировали логическую переменную жизни, герой жив
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
	}

FloatRect getRect(){//метод получени€ пр€моугольника. его коорд, размеры (шир,высот).
	FloatRect FR(x, y, w, h); // переменна€ FR типа FloatRect
	return FR;
	//return FloatRect(x, y, w, h);
	//“ип данных (класс) "sf::FloatRect" позвол€ет хранить четыре координаты пр€моугольника
		//в нашей игре это координаты текущего расположени€ тайла на карте
		//далее это позволит спросить, есть ли ещЄ какой-либо тайл на этом месте 
		//эта ф-ци€ нужна дл€ проверки пересечений 
	}
	virtual void update(float time) = 0;
};
