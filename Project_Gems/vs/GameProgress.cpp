#include "Field.h"
#include "GameProgress.h"
#include "GameOver.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Bomb.h"
#include "Repainting.h"


void GameLoop(void) {
	int bonusProbability; 
	point bonusCoordinates;
	int arr[8][8], zero_draw = 0;
	struct point startDrawPoint, firstPoint, secondPoint;
	bool secondClick = false, match = false;
	Font font; 
	clock_t Time_Left = clock() + 300 * CLOCKS_PER_SEC, delta_t = 0;
    int qurMin = 5, qurSec = 0;

	font.loadFromFile("19076.ttf");
	Text text("", font, 50);
	text.setFillColor(Color::Black);
	text.setPosition(700, 60);

	std::ostringstream playerTimerMin, playerTimerSec; 
	playerTimerMin << qurMin;
	playerTimerSec << qurSec;
	text.setString("Timer: " + playerTimerMin.str() + " : " + playerTimerSec.str());
	
	GameOver endgame;

	std::shared_ptr <Field> field;
	field = std::make_shared<Field>(arr);
	field->InitField();
 
	std::shared_ptr <sf::RenderWindow> window;
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 720), "Gems");

	window->setFramerateLimit(60);

	startDrawPoint.x = field->GetStartPoint();
	startDrawPoint.y = field->GetStartPoint();

	Texture t;
	t.loadFromFile("images/back.jpg");

	Sprite background(t);

	while (window->isOpen())
	{
		Event event;
		delta_t = clock();
		while (window->pollEvent(event)) {


			/* if the user clicked on the crossand wants to close the game */
			if (event.type == Event::Closed)
				window->close();

			/* if the user clicked the mouse button */
			if (event.type == Event::MouseButtonPressed) {

				/* if it is the left mouse button */
				if (event.key.code == Mouse::Left) {

					/* if this is the first click */
					if (secondClick == false) {

						/* we get the mouse coordinates of the place where we clicked */
						Vector2i position = Mouse::getPosition(*window);

						/* translate the obtained coordinates to the heme position in the array */
						firstPoint = field->TransleteCoordinat(position.x, position.y, startDrawPoint.x, startDrawPoint.y);
						field->ClickOnGem(firstPoint.x, firstPoint.y);
						secondClick = true;
					}
					/* if this is the second click  */
					else {
						/* we get the mouse coordinates of the place where we clicked */
						Vector2i position = Mouse::getPosition(*window);
						secondPoint = field->TransleteCoordinat(position.x, position.y, startDrawPoint.x, startDrawPoint.y);

						
						bonusProbability = rand() % 4 + 1;

						do {
							bonusCoordinates.x = secondPoint.x - 3 + rand() % 6;
						} while (bonusCoordinates.x < 0 || bonusCoordinates.x > 7);

						do {
							bonusCoordinates.y = secondPoint.y - 3 + rand() % 6;
						} while (bonusCoordinates.y < 0 || bonusCoordinates.y > 7);
						
					
						/* if you double-clicked on the same gems, then the user changed his mind about rearranging it */
						if (firstPoint.x == secondPoint.x && firstPoint.y == secondPoint.y) {
							field->CancelClick(firstPoint.x, firstPoint.y);
							secondClick = false;
						}
						
						/* otherwise he wants to rearrange them */
						else {
							field->ClickOnGem(secondPoint.x, secondPoint.y);
							/* check if two gems are adjacent to each other */
							int cases = field->CheckNeighbors(firstPoint, secondPoint);
							if (cases != 0) {
								/* if so, then swap them */
								field->MoveGems(cases, firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y, *window, text);
								field->Swap(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);
								field->RemoveClick(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);
								/* do a check for three in a row */
								match = field->Match3(*window, text);

								if (match == false) {
									field->MoveGems(cases, firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y, *window, text);
									field->Swap(secondPoint.x, secondPoint.y, firstPoint.x, firstPoint.y);
								}
								else {
									match = false;

									/* if the chance of a bonus is 2 - the bomb is called */
									if (bonusProbability == 2) {
										Bomb bomb(bonusCoordinates.x, bonusCoordinates.y);
										bomb.DrawBonusTexture(window, field);
										bomb.Actuation(field);
										field->CheckEmptyGems(*window, text);
										field->Match3(*window, text);
									}
									else
										/* if the chance of a bonus is 3 - the artist is called */
										if (bonusProbability == 3) {
											Repainting painter(bonusCoordinates.x, bonusCoordinates.y);
											painter.DrawBonusTexture(window, field);
											painter.Actuation(field);
											field->Match3(*window, text);
										}
								}
							}
							else {
								field->RemoveClick(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);
							}
							secondClick = false;
						}	
					}
				}
			}
		}

		playerTimerMin.str("");
		playerTimerMin.clear();

		playerTimerSec.str("");
		playerTimerSec.clear();
		
		
		qurMin = (Time_Left - 2 * clock() + delta_t) / (60 * CLOCKS_PER_SEC);
		qurSec = (Time_Left - 2 * clock() + delta_t) % (60 * CLOCKS_PER_SEC) / 1000;
		
		if (qurMin <= 0 && qurSec <= 0) {
			window->close();
			endgame.Initialization(field->GetScore());
		}
		
		playerTimerMin << qurMin;
		playerTimerSec << qurSec;
		text.setString("Timer: " + playerTimerMin.str() + " : " + playerTimerSec.str());

		window->clear();
		window->draw(background);
		field->DrawField(*window);

		if (zero_draw == 0) {
			zero_draw = 1;
			field->Match3(*window, text);
		}
		window->draw(text);
		window->display();

	}

}

