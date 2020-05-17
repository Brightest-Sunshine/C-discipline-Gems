#include "Field.h"

#pragma once
class Bonus
{
protected:
	int x = 0, y = 0;
	int bonusType = 0;

public:
	Bonus(int new_x, int new_y, int newType);
	~Bonus();
	virtual int Actuation(std::shared_ptr<Field> field) = 0;
	virtual void DrawBonusTexture(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr<Field> field) = 0;
};

