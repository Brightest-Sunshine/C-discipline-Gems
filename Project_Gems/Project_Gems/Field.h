#include <SFML/Graphics.hpp>
#include "GameProgress.h"
using namespace sf;

#pragma once
class Field
{
public:
	enum Color : int {
		RED = 1, DARKRED = 11,
		ORANG = 2, DARKORANG = 12,
		YELLOW = 3, DARKYELLOW = 13,
		GREEN = 4, DARKGREEN = 14,
		BLUE = 5, DARKBLUE = 15,
		PURPLE = 6, DARKPURPLE = 16,
		GRAY = 7, DARKGRAY = 17,
		TRANSPARENT = 0, 
		BOMB = 8,
		PAINTER = 9
	};
	
	int _gemsArray[8][8]; // array with gems
	int _gemSize = 64; 
	int _indent = 6;
	int _startPoint = 60;

	Field(int gemsArray[8][8]);// constructor
	~Field(); // destructor
	IntRect GetSprite(int Color);
	void InitField(); // fill in the gems field
	void DrawField(RenderWindow& window); // draw the resulting gems array
	void ClickOnGem(int i, int j);
	struct point TransleteCoordinat(int x, int y, int x0, int y0);
	void CancelClick(int i, int j);
	int CheckNeighbors(struct point first, struct point second);
	void Swap(int x1, int y1, int x2, int y2);
	void RemoveClick(int x1, int y1, int x2, int y2);
	void MoveGems(int cases, int x1, int y1, int x2, int y2, RenderWindow& window, Text text);
	void ThreeInLine(point coordinate, int count);
	void ThreeInColumne(point coordinate, int count);
	void ReplaceGems(point coordinate, int count, RenderWindow& window, Text text);
	void FallOfGems(int x1, int y1, int x2, int y2, int countGems, RenderWindow& window, Text text);
	void NewGems(int x1, int countZeroes, RenderWindow& window, Text text);
	void DeleteGems();
	void CheckEmptyGems(RenderWindow& window, Text text);
	void LineMatches(point coordinate, int* count, int* match, bool* help);
	void ColumnMatches(point coordinate, int* count, int* match, bool* help);
	bool Match3(RenderWindow& window, Text text);
	int GetScore();
};

