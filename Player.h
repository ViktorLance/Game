#ifndef Player_h
#define Player_h

using namespace sf;
class Player :public Entity { 
public:// ����� ������
	int  money, photo, money1; // ������� ����, ���-�� ������ ��� �������� ��������,���������� � "������", ���-�� ����� �� ������

							   //����������� � ����������� ��� ������ Player
	
	Player(Image &image, float X, float Y, float W, float H, std::string Name) ;
	void control();
	//����� �������� ������������ � ���������� �����
	void checkCollisionWithMap(float Dx, float Dy);

	void update(float time);
};
#endif