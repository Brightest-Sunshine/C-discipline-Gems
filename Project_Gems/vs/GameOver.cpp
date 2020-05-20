#include "GameOver.h"
#include <iostream>
#include <sstream>
#include <string>

void GameOver::Initialization(int gamescore)
{
	Font font;
	int status = 0;
	float bottom = 345, top1 = 190, top2 = 300;
	String string1 = "Try again", string2 = "Exit";
	MyButton restart(top1, bottom, string1), exit_b(top2, bottom, string2);
	Texture text;
	text.loadFromFile("images/GameOver.jpg");
	Sprite endGame(text);
	std::ostringstream score;

	score << gamescore;

	font.loadFromFile("19076.ttf");
	Text tex1("", font, 60), tex2("", font, 60), tex3("", font, 60);
	
	tex1.setFillColor(Color::Black);
	tex1.setPosition(400, 175);
	tex1.setString(string1);

	tex2.setFillColor(Color::Black);
	tex2.setPosition(440, 285);
	tex2.setString(string2);

	tex3.setFillColor(Color::Red);
	tex3.setPosition(400, 405);
	tex3.setString("Score:   " + score.str());

	RenderWindow gameOverWindow(sf::VideoMode(1000, 720), "Game over");
	gameOverWindow.setFramerateLimit(60);

	while (gameOverWindow.isOpen()) {
		Event event;
		while (gameOverWindow.pollEvent(event)) {

			/* if the user clicked on the cross and wants to close the window */
			if (event.type == Event::Closed)
				gameOverWindow.close();

			/* if the user clicked the mouse button */
			if (event.type == Event::MouseButtonPressed) {

				/* if it is the left mouse button */
				if (event.key.code == Mouse::Left) {

					/* we get the mouse coordinates of the place where we clicked */
					Vector2i position = Mouse::getPosition(gameOverWindow);
					status = this->PushButton(position);

					if (status == TRYAGAIN) {
						gameOverWindow.close();
						GameLoop();
					}
					if (status == EXIT) {
						exit(0);
					}
				}
			}
		}
		gameOverWindow.clear();
		gameOverWindow.draw(endGame);
		restart.Draw(gameOverWindow);
		gameOverWindow.draw(tex1);
		exit_b.Draw(gameOverWindow);
		gameOverWindow.draw(tex2);
		gameOverWindow.draw(tex3);
		gameOverWindow.display();
	}
}

int GameOver::PushButton(Vector2i position)
{
	if (position.x >= 345 && position.x <= 645) {
		if (position.y >= 190 && position.y <= 250) {
			return TRYAGAIN;
		}
		else if (position.y >= 300 && position.y <= 360) {
			return EXIT;
		}
	}
	return 0;
}
