#include <SFML/Graphics.hpp>
#include <ctime>
#include "Field.h"
#include "Menu.h"

MyButton::MyButton(float top, float bottom, String string):_top(top), _bottom(bottom) {}

MyButton::~MyButton() {}

void MyButton::Draw(RenderWindow& menu)
{	
	// Create a rectangle
	RectangleShape rectangle(Vector2f(_weight, _height));
	// Move it
	rectangle.move(_bottom, _top);
	// Set it color
	rectangle.setFillColor(Color(201, 251, 255));
	menu.draw(rectangle);
}

Menu::Menu(){}
Menu::~Menu(){}

void Menu::Initialization(void)
{
	Font font;
	int status = 0;
	float bottom = 345, top1 = 190,  top2 = 300, top3 = 420;
	String string1 = "Play game", string2 = "Rules", string3 = "Exit";
	MyButton startGame(top1,bottom,string1), rules(top2, bottom, string2), exit_b(top3,bottom, string3);
	Texture text; 
	text.loadFromFile("images/menu.jpg");
	Sprite spriteMenu(text);

	font.loadFromFile("19076.ttf");
	Text tex1("", font, 60), tex2("", font, 60), tex3("", font, 60);

	tex1.setFillColor(Color::Black);
	tex1.setPosition(400, 175);
	tex1.setString(string1);

	tex2.setFillColor(Color::Black);
	tex2.setPosition(440, 285);
	tex2.setString(string2);

	tex3.setFillColor(Color::Black);
	tex3.setPosition(455, 405);
	tex3.setString(string3);

	RenderWindow menu(sf::VideoMode(1000, 720), "Menu");
	menu.setFramerateLimit(60);

	while (menu.isOpen()){
		Event event;
		while (menu.pollEvent(event)) {

			/* if the user clicked on the cross and wants to close the window */
			if (event.type == Event::Closed)
				menu.close();

			/* if the user clicked the mouse button */
			if (event.type == Event::MouseButtonPressed) {

				/* if it is the left mouse button */
				if (event.key.code == Mouse::Left) {

					/* we get the mouse coordinates of the place where we clicked */
					Vector2i position = Mouse::getPosition(menu);
					status = this->PushButton(position);

					if (status == PLAYGAME) {
						menu.close();
						GameLoop();
					}
					if (status == EXIT) {
						exit(0);
					}
				}
			}

		}

		menu.clear();	
		menu.draw(spriteMenu);
		startGame.Draw(menu);
		menu.draw(tex1);
		rules.Draw(menu);
		menu.draw(tex2);
		exit_b.Draw(menu);
		menu.draw(tex3);
		menu.display();
	}
}

int Menu::PushButton(Vector2i position)
{
	if (position.x >= 345 && position.x <= 645) {
		if (position.y >= 190 && position.y <= 250) {
			return PLAYGAME;
		}
		else if (position.y >= 300 && position.y <= 360) {
			return RULES;
		}
		else if (position.y >= 420 && position.y <= 480) {
			return EXIT;
		}
	}
	return 0;
}
