#include <iostream>
#include "Character.h"
#include "Game.h"

int main() {
	Game* play = Game::getInstance();
	play->Initialize("file.txt");
	play->Run();
	return 0;
}
