#include "Manager.h"

Manager::Manager() {
	font.loadFromFile("rsrc/AndBasR.ttf");
	focusedX = focusedY = 0; // the 0, 0 field is 'hovered' by default
	// fields setup: preparing each square appearance //
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
			fields[i][j].square = sf::RectangleShape(sf::Vector2f(35, 35));
			fields[i][j].square.setPosition(40 + 45 * (i), 40 + 45 * (j));
			fields[i][j].square.setOutlineThickness(2);
			fields[i][j].square.setOutlineColor(sf::Color::Black);

			fields[i][j].numberText = sf::Text("1", font, 25);
			fields[i][j].numberText.setFillColor(sf::Color::Black);
			fields[i][j].numberText.setPosition(fields[i][j].square.getPosition().x + 10, fields[i][j].square.getPosition().y + 2);
		}
}

void Manager::Loop(sf::RenderWindow& window) {
	// solve button //
	sf::RectangleShape solveBtn(sf::Vector2f(120, 50));
	solveBtn.setFillColor(sf::Color::White);
	solveBtn.setOutlineColor(sf::Color::Black);
	solveBtn.setOutlineThickness(2);
	solveBtn.setPosition(480, 150);


	// clear button //
	sf::RectangleShape clearBtn = sf::RectangleShape(sf::Vector2f(120, 50));
	clearBtn.setFillColor(sf::Color::White);
	clearBtn.setOutlineColor(sf::Color::Black);
	clearBtn.setOutlineThickness(2);
	clearBtn.setPosition(480, 230);

	// setting texts properities //
	sf::Text author("@Dziobex 2021", font, 20), solveText("Solve", font, 30), clearText("Clear", font, 30), steps("Steps: 0", font, 20),
		statusText("Status: Unknown", font, 20);
	solveText.setFillColor(sf::Color::Black);
	solveText.setPosition(502, 157);

	author.setFillColor(sf::Color(150, 150, 150));
	author.setPosition(485, 455);

	clearText.setFillColor(sf::Color::Black);
	clearText.setPosition(503, 237);

	steps.setFillColor(sf::Color::Black);
	steps.setPosition(200, 450);

	statusText.setFillColor(sf::Color::Black);
	statusText.setPosition(35, 5);

	// setting music (which is played if the sudoku is unsolvable) //
	sf::SoundBuffer sb;
	sb.loadFromFile("rsrc/oof.wav");
	sf::Sound s;
	s.setBuffer(sb);

	while (window.isOpen()) {
		sf::Event e;
		bool mousePressed = false;

		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					focusedY = focusedY == 0 ? 8 : focusedY - 1;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					focusedY = focusedY == 8 ? 0 : focusedY + 1;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					focusedX = focusedX == 0 ? 8 : focusedX - 1;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					focusedX = focusedX == 8 ? 0 : focusedX + 1;

				// changing number placed on the 'focused' field //
				if ((int)e.key.code >= 27 && (int)e.key.code <= 38)
					fields[focusedX][focusedY].number = (int)e.key.code - 26;
				else if (e.key.code == sf::Keyboard::Num0 || e.key.code == sf::Keyboard::Delete || e.key.code == sf::Keyboard::BackSpace)
					fields[focusedX][focusedY].number = 0;
			}
			case sf::Event::MouseButtonPressed: mousePressed = true; break;
			default: break;
			}
		}

		window.clear(sf::Color::White);

		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

		// changing the focused field if possible //
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j) {
				if (fields[i][j].Hover((focusedX == i && focusedY == j) || fields[i][j].square.getGlobalBounds().contains(mousePos))) {
					focusedX = i;
					focusedY = j;
				}
				if (focusedX == i && focusedY == j) fields[i][j].square.setFillColor(sf::Color(150, 150, 150));
				else fields[i][j].square.setFillColor(sf::Color::White);
				fields[i][j].Render(window);
			}

		window.draw(author);

		// event handling: solve button was pressed //
		if (solveBtn.getGlobalBounds().contains(mousePos)) {
			solveBtn.setFillColor(sf::Color(150, 150, 150));
			solveText.setFillColor(sf::Color::White);
			if (mousePressed) {
				int grid[9][9]{};
				// the numbers from the fields are copied to the solver's grid //
				for (int i = 0; i < 9; ++i)
					for (int j = 0; j < 9; ++j) {
						grid[i][j] = fields[j][i].number;
					}
				if (!solver.Initialize(grid)) {
					statusText.setString("Status: Unsolvable");
					statusText.setFillColor(sf::Color::Red);
					s.play();
				}
				else if (!solver.Solve(0, -1)) {
					statusText.setString("Status: Unsolvable");
					statusText.setFillColor(sf::Color::Red);
					s.play();
				}
				else {
					// the grid from solver is copied to the fields //
					for (int i = 0; i < 9; ++i)
						for (int j = 0; j < 9; ++j)
							fields[j][i].number = solver.grid[i][j];
					steps.setString("Steps: " + std::to_string(solver.GetSteps()));
					statusText.setString("Status: Solved");
					statusText.setFillColor(sf::Color::Green);
				}
			}
		}
		else {
			solveBtn.setFillColor(sf::Color::White);
			solveText.setFillColor(sf::Color::Black);
		}

		// event handling: clear button was pressed //
		if (clearBtn.getGlobalBounds().contains(mousePos)) {
			clearBtn.setFillColor(sf::Color(150, 150, 150));
			clearText.setFillColor(sf::Color::White);
			if (mousePressed) {
				for (int i = 0; i < 9; ++i) // reseting grid
					for (int j = 0; j < 9; ++j)
						fields[j][i].number = 0;
				steps.setString("Steps: 0");
				statusText.setString("Status: Unknown");
				statusText.setFillColor(sf::Color::Black);
			}
		}
		else {
			clearBtn.setFillColor(sf::Color::White);
			clearText.setFillColor(sf::Color::Black);
		}

		// drawing sudoku status: none (unknown), solved, unsolvable //
		window.draw(statusText);

		// drawing buttons //
		window.draw(solveBtn);
		window.draw(solveText);

		window.draw(clearBtn);
		window.draw(clearText);

		// drawing steps counter //
		window.draw(steps);

		window.display();
	}
}

// changing color of the square and the number if the square is hovered //
bool Manager::Field::Hover(bool hovered) {
	if (hovered) {
		square.setFillColor(sf::Color(150, 150, 150));
		numberText.setFillColor(sf::Color::White);
		return true;
	}
	square.setFillColor(sf::Color::White);
	numberText.setFillColor(sf::Color::Black);
	return false;
}

// rendering field (the square and the number inside) //
void Manager::Field::Render(sf::RenderWindow& window) {
	numberText.setString(number != 0 ? std::to_string(number) : "");
	window.draw(square);
	window.draw(numberText);
}
