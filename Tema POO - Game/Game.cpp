#include "Game.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

Game* Game::instance = nullptr;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


Game* Game::getInstance()
{
	if (!instance)
		instance = new Game();
	return instance;
}


Game::Game()
{
	enemies = new Character[enemiesCount];
	currentEnemyIndex = 0;
	defeatedEnemiesCount = 0;

	playerArt = {
	   "    O    ",
	   "   /|\\   ",
	   "  / | \\   ",
	   "   / \\   ",
	   "  /   \\  "
	};

	enemyArts = {
	{
		"   (x_x)   ",
		"   /|||\\   ",
		"   | |   ",
		"    / \\    ",
		"   /   \\   "
	},
	{
		"   \\O_O/   ",
		"    |-|    ",
		"   | |    ",
		"    / \\    ",
		"   /   \\   "
	},
	{
		"   [0_0]   ",
		"   /|_|\\   ",
		"   | |    ",
		"    / \\    ",
		"   /   \\   "
	},
	{
		"   >O_O<   ",
		"    /|\\    ",
		"   | |    ",
		"    / \\    ",
		"   /   \\   "
	}
	};

}

Game::~Game()
{
	delete[] enemies;
}

void Game::Initialize(const std::string& filename)
{
	std::ifstream file(filename);
	file >> mainCharacter;

	for (int i = 0; i < enemiesCount; i++)
		file >> enemies[i];

	std::sort(enemies, enemies + enemiesCount);
	file.close();
}

void Game::clearScreen()
{
#if defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}

std::string Game::buildHealthBar(const Character& c)
{
	int totalBars = 20;
	double ratio = (double)c.getRemainingHealthPoints() / c.getHealthPoints();
	int filled = (int)(ratio * totalBars);

	std::string bar = "[";
	for (int i = 0; i < filled; i++) bar += GREEN "#";
	for (int i = filled; i < totalBars; i++) bar += RED "-";
	bar += "] ";

	bar += std::to_string(c.getRemainingHealthPoints()) + "/" +
		std::to_string(c.getHealthPoints()) + RESET;
	return bar;
}

void Game::displayHealthBars(Character& player, Character& enemy)
{
	std::cout << "\n";
	std::cout << CYAN << " " << player.getName() << " " << GREEN << buildHealthBar(player) << RESET << "\n";
	std::cout << MAGENTA << " " << enemy.getName() << " " << GREEN << buildHealthBar(enemy) << RESET << "\n\n\n";
}

void Game::displayCharactersArt(Character& enemy, int artIndex) {
	const int SPACE_BETWEEN_CHARACTERS = 20;

	for (size_t i = 0; i < std::max(playerArt.size(), enemyArts[artIndex].size()); i++)
	{
		std::string leftLine = i < playerArt.size() ? CYAN + playerArt[i] + RESET : "       ";
		std::string rightLine = i < enemyArts[artIndex].size() ? MAGENTA + enemyArts[artIndex][i] + RESET : "       ";
		std::cout << leftLine << std::string(SPACE_BETWEEN_CHARACTERS, ' ') << rightLine << "\n";
	}
	std::cout << "\n\n\n";
}

void  Game::displayMenu()
{
	std::cout << " =============== MENU ===============" << "\n";
	std::cout << " 1. HEAL\n";
	std::cout << " 2. ATTACK\n";
	std::cout << " CHOICE: ";
}

void Game::displayPlayerStats() {
	std::cout << " Health Potions: " << mainCharacter.getHealthPotionsCount() << "\n";
	std::cout << " Attack: " << mainCharacter.getAttackDamage() << "\n";
	std::cout << " Defense: " << mainCharacter.getDefence() << "\n";
}

int Game::playerChoice()
{
	int option;
	displayMenu();

	while (true)
	{
		std::cin >> option;

		std::cout << "\n";

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << RED << " Invalid input! Please enter a number.\n" << RESET;
			continue; 
		}

		if (option == 1)
		{
			if (mainCharacter.getHealthPotionsCount() > 0)
			{
				mainCharacter.heal();
				std::cout << YELLOW << " You used a healing potion. Remaining: "
					<< mainCharacter.getHealthPotionsCount() << RESET << "\n";

				break; 
			}
			else
			{
				std::cout << RED << " No potions left! Choose another action." << RESET << "\n";
				std::cout << " CHOICE: ";
				continue;
			}
		}
		else if (option == 2)
		{
			break; 
		}
		else
		{
			std::cout << RED << " Invalid choice! Choose 1 or 2.\n" << RESET;
			std::cout << " CHOICE: ";
			continue; 
		}
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return option;
}


void Game::processEnemyTurn(Character& enemy) {
	if (enemy.isAlive())
	{
		enemy.attack(mainCharacter);
		std::cout << RED <<" "<< enemy.getName() << " attacks you!" << RESET << "\n";

	}
	else
	{
		std::cout << GREEN << " Enemy defeated!" << RESET << "\n";
		currentEnemyIndex++;
		defeatedEnemiesCount++;
		if (defeatedEnemiesCount % 2 == 0)
		{
			std::cout << GREEN << " You beat 2 enemies! LEVEL UP." << RESET << "\n";
			++mainCharacter;
			displayPlayerStats();
		}

	}
}


void Game::Run()
{
	while (mainCharacter.isAlive() && currentEnemyIndex < enemiesCount)
	{
		clearScreen();
		Character& enemy = enemies[currentEnemyIndex];
		int artIndex = currentEnemyIndex % enemyArts.size();

		displayHealthBars(mainCharacter, enemy);
		displayCharactersArt(enemy, artIndex);

		int option = playerChoice(); 
		if (option == 2)
			mainCharacter.attack(enemy);

		processEnemyTurn(enemy);

		std::cout << "\n Press Enter to continue...";
		std::cin.get(); 
	}

	if (mainCharacter.isAlive())
		std::cout << GREEN << " VICTORY! YOU WON!" << RESET << "\n";
	else
		std::cout << RED << " YOU LOST :(" << RESET << "\n";
}


