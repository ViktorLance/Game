#include <SFML/Graphics.hpp>

using namespace sf;
int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 4");

	Texture herotexture;
	herotexture.loadFromFile("images/pacman.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	//�������� ������ ��� ������������� � �����
	herosprite.setTextureRect(IntRect(35, 0, 35, 35));
	herosprite.setPosition(250, 250); //������� ������ � ������� x y 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//���������� Y, �� ������� ����� ��������� ������ ����� ����� 96
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(0, 35, 35, 35));
		}

		//���������� Y, �� ������� ����� ��������� ������ ������ ����� 96+96=192
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(35, 0, 35, 35));
		}

		//���������� Y �� ������� ����� ��������� ������ ����� ����� 288
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(70, 0, 35, 35));
		}

		//���������� 0, ��� ������� ����� ����������� � ������, �� ��� � ������������� 			//������� ������������ �� 96.
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			herosprite.move(0, 0.1); herosprite.setTextureRect(IntRect(105, 35, 35, 35));
		}

		// �������� ����� � ������� ���� �� ������� ����� ������� ����
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			herosprite.setColor(Color::Red);
		}

		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}


