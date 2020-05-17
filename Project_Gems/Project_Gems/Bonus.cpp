#include "Bonus.h"

Bonus::Bonus(int new_x, int new_y, int newType) {
	x = new_x;
	y = new_y;
	bonusType = newType;
}

Bonus::~Bonus() {}

int Bonus::Actuation(std::shared_ptr<Field> field) {
	return 0;
}

void Bonus::DrawBonusTexture(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Field> field) {}
