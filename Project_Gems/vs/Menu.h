#include <SFML/Graphics.hpp>
#include <SFML\System\String.hpp>
#include "GameProgress.h"

using namespace sf;
#pragma once

class MyButton
{	
	private:
		float _top, _bottom;
		String _string;
	public:
		float const _weight = 300, _height = 60;
		MyButton(float top, float bottom, String string);
		~MyButton();
		void Draw(RenderWindow& menu);
		
};

class Menu
{
public:
	enum {
		PLAYGAME = 1,
		RULES = 2,
		EXIT = 3,
		TRYAGAIN = 4
	};
	Menu();
	~Menu(); 
	virtual void Initialization(void);
	virtual int PushButton(Vector2i position);
};

