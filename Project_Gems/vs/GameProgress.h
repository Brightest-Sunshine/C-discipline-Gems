#pragma once
#include <SFML/Graphics.hpp>
#include <xlocinfo>


/* structure - location of a point on the screen */
struct point {
	int x, y;
};

void GameLoop(void);