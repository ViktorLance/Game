#ifndef Entity_h
#define Entity_h

using namespace sf;
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
	Entity(Image &image, float X, float Y, int W, int H, std::string Name); 
	virtual void update(float time) = 0;
	FloatRect getRect() {//����� ��������� ��������������. ��� �����, ������� (���,�����).
		FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect
		return FR;
		//return FloatRect(x, y, w, h);
		//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
		//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
		//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
		//��� �-��� ����� ��� �������� ����������� 
	}
};
#endif