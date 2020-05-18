#include "Field.h"
#include <stdlib.h>

/* number of points */
int gameScore = 0;

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

