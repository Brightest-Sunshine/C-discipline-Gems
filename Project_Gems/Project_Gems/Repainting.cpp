#include "Repainting.h"

Repainting::~Repainting() {}

void Repainting::DrawBonusTexture(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Field> field)
{
	Sprite painter;
	Texture tex;

	tex.loadFromFile("images/painter.png");
	painter.setTexture(tex);

	field->_gemsArray[x][y] = field->TRANSPARENT;

	for (int i = 0; i < 25; i++) {
		field->DrawField(*window);
		window->display();
	}
	
	painter.setPosition(float(x * (field->_gemSize + field->_indent) + field->_startPoint), float(y * (field->_gemSize + field->_indent) + field->_startPoint));
	
	for (int i = 0; i < 40; i++) {
		window->draw(painter);
		window->display();
	}
	
}

int Repainting::Actuation(std::shared_ptr<Field> field)
{
	int new_color, tmp1, tmp2, tmp_x, tmp_y;
	new_color = rand() % 7;
	field->_gemsArray[x][y] = new_color;

	for (int i = 0; i < countPaintedGems; i++) {
		tmp1 = rand() % paintingRadius + 1;
		tmp2 = rand() % paintingRadius + 1;
		if (x + tmp1 <= 7)
			tmp_x = x + tmp1;
		else
			tmp_x = x - tmp1;
		if (y - tmp2 >= 0)
			tmp_y = y - tmp2;
		else
			tmp_y = y + tmp2;
		field->_gemsArray[tmp_x][tmp_y] = new_color;
	}
	return 0;
}
