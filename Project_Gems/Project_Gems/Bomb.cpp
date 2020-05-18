#include "Bomb.h"

Bomb::~Bomb() {}

void Bomb::DrawBonusTexture(std::shared_ptr <sf::RenderWindow> window, std::shared_ptr<Field> field) {
	Texture tex, tex2;
	Sprite bomb, empty;

	tex.loadFromFile("images/gems.png");
	tex2.loadFromFile("images/back.jpg");

	bomb.setTexture(tex);
	empty.setTexture(tex2);

	bomb.setTextureRect(IntRect(448, 0, 64, 64));
	empty.setTextureRect(IntRect(0, 0, 64, 64));

	empty.setPosition(float(x * (field->GetGemSize() + field->GetIndent()) + field->GetStartPoint()), float(y * (field->GetGemSize() + field->GetIndent()) + field->GetStartPoint()));

	field->DoTransparent(x, y);
	window->draw(empty);
	window->display();

	bomb.setPosition(float(x * (field->GetGemSize() + field->GetIndent()) + field->GetStartPoint()), float(y * (field->GetGemSize() + field->GetIndent()) + field->GetStartPoint()));
	
	for (int i = 0; i < 40; i++) {
		window->draw(empty);
		window->display();

		window->draw(bomb);
		window->display();
	}
	
}

int Bomb::Actuation(std::shared_ptr<Field> field)
{
	int tmp, tmp_x, tmp_y;
	for (int i = 0; i < countDestroyGems; i++) {
		tmp = rand() % 7;
		tmp_x = (x + tmp) / 2;
		tmp = rand() % 7;
		tmp_y = (y + tmp) / 2;
		
		if (field->CheckTableCell(tmp_x, tmp_y) != field->TRANSPARENT)
			field->DoTransparent(tmp_x, tmp_y);
		else
			i--;
	}
	return 0;
}


