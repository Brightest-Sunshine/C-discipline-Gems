#pragma once
#include "Menu.h"

class GameOver :
	public Menu
{
public:
	virtual void Initialization(int gamescore);
	virtual int PushButton(Vector2i position);
};

