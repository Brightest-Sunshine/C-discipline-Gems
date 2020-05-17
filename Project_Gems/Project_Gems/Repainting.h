#pragma once
#include "Bonus.h"

class Repainting :
	public Bonus
{
private:
	int countPaintedGems = 2;
	int paintingRadius = 3;
public:
	Repainting(int new_x, int new_y) :Bonus(new_x, new_x, 1) {}
	~Repainting();
	int Actuation(std::shared_ptr<Field> field) override;
	void DrawBonusTexture(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr<Field> field) override;

};

