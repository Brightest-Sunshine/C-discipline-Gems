#include "Field.h"
#include <stdlib.h>


Field::Field(int gemsArray[8][8]): _gemsArray() {}

Field::~Field() {}

void Field::InitField()
{
	srand((unsigned int)time(0));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_gemsArray[i][j] = (int)rand() % 7 + 1;
		}
	}
}

float Field::GetPositionX(int x) {
	return x * (this->GetGemSize() + this->GetIndent()) + this->GetStartPoint();
}

float Field::GetPositionY(int y) {
	return y * (this->GetGemSize() + this->GetIndent()) + this->GetStartPoint();
}

void Field::DoTransparent(int x, int y) {
	this->_gemsArray[x][y] = TRANSPARENT;
}

void Field::ChangeColor(int x, int y, int color) {
	_gemsArray[x][y] = color;
}

void Field::ClickOnGem(int i, int j)
{
	_gemsArray[i][j] = _gemsArray[i][j] + DIFFERENCE;
}

point Field::TransleteCoordinat(int x, int y, int x0, int y0)
{
	point coordinates;
	coordinates.x = (int)((x - x0) / (_gemSize + _indent));
	coordinates.y = (int)((y - y0) / (_gemSize + _indent));
	return coordinates;
}

void Field::CancelClick(int i, int j)
{
	_gemsArray[i][j] = _gemsArray[i][j] - DIFFERENCE;
}

int Field::CheckNeighbors(point first, point second)
{
	if ((first.x == second.x + 1 && first.y == second.y) || (first.x == second.x - 1 && first.y == second.y))
		return 1;
	if ((first.y == second.y + 1 && first.x == second.x) || (first.y == second.y - 1 && first.x == second.x))
		return 2;
	return 0;
}

void Field::Swap(int x1, int y1, int x2, int y2)
{
	int tmp = _gemsArray[x1][y1];
	_gemsArray[x1][y1] = _gemsArray[x2][y2];
	_gemsArray[x2][y2] = tmp;
}

void Field::RemoveClick(int x1, int y1, int x2, int y2)
{
	_gemsArray[x1][y1] = _gemsArray[x1][y1] - DIFFERENCE;
	_gemsArray[x2][y2] = _gemsArray[x2][y2] - DIFFERENCE;
}

void Field::ReplaceGems(point coordinate, int count, RenderWindow& window, Text text)
{
	for(int j  = coordinate.y; j > 0; j--){
		for (int i = coordinate.x; i < coordinate.x + count; i++) {
			this->MoveGems(2, i, coordinate.y, i, coordinate.y - 1, window, text);
			_gemsArray[i][j] = _gemsArray[i][j - 1];
		}
	}

	for (int i = 0; i < coordinate.x + count; i++)
		_gemsArray[i][0] = rand() % 7 + 1;

}


void Field::DeleteGems()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_gemsArray[i][j] < 0) {
				this->DoTransparent(i, j);
			}
		}
	}
}

