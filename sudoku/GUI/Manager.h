#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Solver.h"

class Manager
{
	sf::Font font;
	Solver solver;

	struct Field {
		int number = 0;
		sf::RectangleShape square;
		sf::Text numberText;
		bool Hover(bool hovered);
		void Render(sf::RenderWindow& window);
	};

	Field fields[9][9];
	int focusedX, focusedY;

public:
	Manager();
	void Loop(sf::RenderWindow& window);
};

