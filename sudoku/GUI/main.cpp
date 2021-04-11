#include "Manager.h"

int main() {
	// program entry //
	sf::RenderWindow window(sf::VideoMode(650, 500), "Sudoku Solver", sf::Style::Titlebar | sf::Style::Close);
  
  // setting the icon //
	sf::Image icon;
	icon.loadFromFile("rsrc/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  
	Manager manager;
	manager.Loop(window);

	return 0;
}
