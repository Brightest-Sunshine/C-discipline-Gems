#include "Field.h"
#include <stdlib.h>

/* number of points */
int gameScore = 0;

Field::Field(int gemsArray[8][8]): _gemsArray() {}

Field::~Field() {}

IntRect Field::GetSprite(int Color)
{
	switch (Color) {
	case RED:
		return IntRect(0, 0, 64, 64);
		break;
	case DARKRED:
		return IntRect(0, 64, 64, 64);
		break;
	case ORANG:
		return IntRect(64, 0, 64, 64);
		break;
	case DARKORANG:
		return IntRect(64, 64, 64, 64);
		break;
	case YELLOW:
		return IntRect(128, 0, 64, 64);
		break;
	case DARKYELLOW:
		return IntRect(128, 64, 64, 64);
		break;
	case GREEN:
		return IntRect(192, 0, 64, 64);
		break;
	case DARKGREEN:
		return IntRect(192, 64, 64, 64);
		break;
	case BLUE:
		return IntRect(256, 0, 64, 64);
		break;
	case DARKBLUE:
		return IntRect(256, 64, 64, 64);
		break;
	case PURPLE:
		return IntRect(320, 0, 64, 64);
		break;
	case DARKPURPLE:
		return IntRect(320, 64, 64, 64);
		break;
	case GRAY:
		return IntRect(384, 0, 64, 64);
		break;
	case DARKGRAY:
		return IntRect(384, 64, 64, 64);
		break;
	case TRANSPARENT:
		return IntRect(448, 64, 64, 64);
		break;
	default:
		break;
	}
	return IntRect();
}

void Field::InitField()
{
	srand((unsigned int)time(0));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_gemsArray[i][j] = (int)rand() % 7 + 1;
		}
	}
}

void Field::DrawField(RenderWindow& window)
{
	Texture tex;
	Sprite gem;
	tex.loadFromFile("images/gems.png");
	gem.setTexture(tex);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			gem.setTextureRect(this->GetSprite(_gemsArray[i][j]));
			gem.setPosition(float(i * (_gemSize + _indent) + _startPoint), float(j * (_gemSize + _indent) + _startPoint));
			window.draw(gem);
		}
	} 

}

void Field::ClickOnGem(int i, int j)
{
	_gemsArray[i][j] = _gemsArray[i][j] + 10;
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
	_gemsArray[i][j] = _gemsArray[i][j] - 10;
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
	_gemsArray[x1][y1] = _gemsArray[x1][y1] - 10;
	_gemsArray[x2][y2] = _gemsArray[x2][y2] - 10;
}


void Field::MoveGems(int cases, int x1, int y1, int x2, int y2, RenderWindow& window, Text text)
{
	double dx = 0, dy = 0;
	int tmp1 = _gemsArray[x1][y1], tmp2 = _gemsArray[x2][y2];
	Texture back, tex;
	Sprite gem1, gem2, background;
	tex.loadFromFile("images/gems.png");
	back.loadFromFile("images/back.jpg");
	gem1.setTexture(tex);
	gem2.setTexture(tex);
	background.setTexture(back);

	gem1.setTextureRect(this->GetSprite(_gemsArray[x1][y1]));
	gem2.setTextureRect(this->GetSprite(_gemsArray[x2][y2]));
	
	switch (cases)
	{
	case 1:
		do {
			_gemsArray[x1][y1] = TRANSPARENT;
			_gemsArray[x2][y2] = TRANSPARENT;
			gem1.setPosition(float(x1 * (_gemSize + _indent) + _startPoint + dx), float(y1 * (_gemSize + _indent) + _startPoint));
			gem2.setPosition(float(x2 * (_gemSize + _indent) + _startPoint - dx), float(y2 * (_gemSize + _indent) + _startPoint));
			dx += (x2 - x1) * 5;
			window.clear();
			window.draw(background);
			this->DrawField(window);
			window.draw(gem1);
			window.draw(gem2);
			window.draw(text);
			window.display();
		} while (float(x1 * (_gemSize + _indent) + _startPoint + dx) != float(x2 * (_gemSize + _indent) + _startPoint));
		_gemsArray[x1][y1] = tmp1;
		_gemsArray[x2][y2] = tmp2;
		break;

	case 2:
		 do {
			_gemsArray[x1][y1] = TRANSPARENT;
			_gemsArray[x2][y2] = TRANSPARENT;
			gem1.setPosition(float(x1 * (_gemSize + _indent) + _startPoint), float(y1 * (_gemSize + _indent) + _startPoint + dy));
			gem2.setPosition(float(x2 * (_gemSize + _indent) + _startPoint), float(y2 * (_gemSize + _indent) + _startPoint - dy));
			dy += (y2 - y1) * 5;
			window.clear();
			window.draw(background);
			this->DrawField(window);
			window.draw(gem1);
			window.draw(gem2);
			window.draw(text);
			window.display();
		 } while (float(y1 * (_gemSize + _indent) + _startPoint + dy) != float(y2 * (_gemSize + _indent) + _startPoint));
		_gemsArray[x1][y1] = tmp1;
		_gemsArray[x2][y2] = tmp2;
		break;
	
	default:
		break;
	}
}

void Field::ThreeInLine(point coordinate, int count)
{
	for (int i = coordinate.x; i < coordinate.x + count; i++) {
		_gemsArray[i][coordinate.y] = _gemsArray[i][coordinate.y] * (-1);
	}
}

void Field::ThreeInColumne(point coordinate, int count)
{
	for (int j = coordinate.y; j < coordinate.y + count; j++) {
		/* if the vertex is not marked yet */
		if (_gemsArray[coordinate.x][j] > 0)
			_gemsArray[coordinate.x][j] = TRANSPARENT;
	}
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

void Field::FallOfGems(int x1, int y1, int x2, int y2, int countGems, RenderWindow& window, Text  text)
{
	double dy = 0;
	Texture back, tex;
	Sprite background;

	Sprite* gems = new Sprite[8];
	int* tmp = new int[8];

	tex.loadFromFile("images/gems.png");
	back.loadFromFile("images/back.jpg");
	background.setTexture(back);

	for (int j = y1; j > -1; j--) {
		gems[j].setTexture(tex);
		gems[j].setTextureRect(this->GetSprite(_gemsArray[x1][j]));
		tmp[j] = _gemsArray[x1][j];
	}

	for (int j = y1; j > -1; j--) {
		_gemsArray[x1][j] = TRANSPARENT;
	}

	do {
		for (int j = y1; j > y1 - countGems; j--) {
			gems[j].setPosition(float(x1 * (_gemSize + _indent) + _startPoint), float(j * (_gemSize + _indent) + _startPoint + dy));
		}
		dy += 7;
		window.clear();
		window.draw(background);
		this->DrawField(window);
		for (int j = y1; j > y1 - countGems; j--) {
			window.draw(gems[j]);
		}
		window.draw(text);
		window.display();

	} while (float(y1 * (_gemSize + _indent) + _startPoint + dy) <= float(y2 * (_gemSize + _indent) + _startPoint));


	for (int j = y2, i = y1; i >= 0; j--, i--) {
		_gemsArray[x2][j] = tmp[i];
	}
}

void Field::NewGems(int x1, int countZero, RenderWindow& window, Text text)
{
	double dy = 0;
	Texture back, tex;
	Sprite background;

	Sprite* newG = new Sprite[countZero];
	int* newGems = new int[countZero];

	tex.loadFromFile("images/gems.png");
	back.loadFromFile("images/back.jpg");
	background.setTexture(back);

	for (int i = countZero - 1; i >= 0; i--) {
		newGems[i] = (int)rand() % 7 + 1;
		newG[i].setTexture(tex);
		newG[i].setTextureRect(this->GetSprite(newGems[i]));
	}

	do {
		for (int i = countZero - 1; i >= 0; i--) {
			newG[i].setPosition(float(x1 * (_gemSize + _indent) + _startPoint), float((i - countZero) * (_gemSize + _indent) + _startPoint + dy));
		}
		dy += 10;
		window.clear();
		window.draw(background);
		this->DrawField(window);
		for (int i = countZero - 1; i >= 0; i--) {
			window.draw(newG[i]);
		}
		window.draw(text);
		window.display();
	} while (float(-1 * (_gemSize + _indent) + _startPoint + dy) <= float((countZero - 1) * (_gemSize + _indent) + _startPoint));

	for (int i = countZero - 1; i >= 0; i--) {
		_gemsArray[x1][i] = newGems[i];
	}
}

void Field::DeleteGems()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (_gemsArray[i][j] < 0) {
				_gemsArray[i][j] = TRANSPARENT;
			}
		}
	}
}

void Field::CheckEmptyGems(RenderWindow& window, Text text)
{
	int t = 0, countZero = 0, countGems = 0;
	point lastGem, lastZero;

	for (int i = 0; i < 8; i++) {
		int j = 0;
		while (j != 8) {
			/* skip all empty */
			while (j < 8 && _gemsArray[i][j] == TRANSPARENT) {
				t++;
				j++;
			}

			/* count the number of pebbles */
			while (j < 8 && _gemsArray[i][j] != TRANSPARENT) {
				countGems += 1;
				lastGem.x = i;
				lastGem.y = j;
				j++;
			}
			/* count the number of empty cells */
			while (j < 8 && _gemsArray[i][j] == TRANSPARENT) {
				countZero += 1;
				lastZero.x = i;
				lastZero.y = j;
				j++;
			}

			if (countZero != 0) {
				this->FallOfGems(lastGem.x, lastGem.y, lastZero.x, lastZero.y, countGems, window, text);
				this->NewGems(lastGem.x, countZero + t, window, text);
			}
			else {
				this->NewGems(lastGem.x, t, window, text);
			}

			countGems = 0;
			countZero = 0;
			t = 0;
		}
	}
}

void Field::LineMatches(point coordinate, int* count, int* match, bool* help)
{
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 7; i++) {

			/* if you find two identical pebbles in a row */
			if (_gemsArray[i][j] > 0 && _gemsArray[i][j] == _gemsArray[i + 1][j]) {
				coordinate.x = i;
				coordinate.y = j;
				int k = i;
				/* see if there are any more similar pebbles and how many */
				while (k <= 6 && _gemsArray[k][j] == _gemsArray[k + 1][j]) {
					*count += 1;
					k++;
				}

				/* if there are three or more identical gems, then we mark them */
				if (*count >= 3) {
					gameScore += *count;
					this->ThreeInLine(coordinate, *count);
					*match += 1;
					*help = true;
					i = 0;
				}
			}
			*count = 1;
		}
	}
}

void Field::ColumnMatches(point coordinate, int* count, int* match, bool* help)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {

			/* if you find two identical pebbles in a row */
			if (_gemsArray[i][j] != 0 && abs(_gemsArray[i][j]) == abs(_gemsArray[i][j + 1])) {
				coordinate.x = i;
				coordinate.y = j;
				int k = j;
				/* see if there are any more similar pebbles and how many */
				while (k <= 6 && abs(_gemsArray[i][k]) == abs(_gemsArray[i][k + 1])) {
					*count += 1;
					k++;
				}
				/* if there are three or more identical gems, then mark them */
				if (*count >= 3) {
					gameScore += *count;
					this->ThreeInColumne(coordinate, *count);
					*match += 1;
					*help = true;
					j = 0;
				}
			}
			*count = 1;
		}
	}
}

bool Field::Match3(RenderWindow& window, Text text)
{
	bool help = false;
	int match = 0; //variable for the presence or absence of combinations
	point coordinate; // the coordinates of the first gems from the combination
	int count = 1; // number of gems in combination
	coordinate.x = 0;
	coordinate.y = 0;

	/* search the field as long as there are combinations of pebbles */
	do {
		match = 0;
		/* check the field for string matches */
		this->LineMatches(coordinate, &count, &match, &help);
		/* check the field for vertical matches */
		this->ColumnMatches(coordinate, &count, &match, &help);
		/* make all negative cells transparent */
		this->DeleteGems();
		/* look for empty cells and fill them */
		this->CheckEmptyGems(window, text);
		
	} while (match);

	return help;
}

int Field::GetScore()
{
	return gameScore;
}
