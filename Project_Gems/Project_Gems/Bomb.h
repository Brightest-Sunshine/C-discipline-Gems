#pragma once
#include "Bonus.h"

class Bomb :
	public Bonus
{
private:
	int const countDestroyGems = 5;
public:
	Bomb(int new_x, int new_y) :Bonus(new_x, new_x, 0) {}
	~Bomb();
	int Actuation(std::shared_ptr<Field> field) override;
	void DrawBonusTexture(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr<Field> field) override;
};

