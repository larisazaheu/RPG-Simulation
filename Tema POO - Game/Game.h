#pragma once
#include "Character.h"

#include <vector>
#include <string>

class Game
{
public:
    Game(const Game&) = delete;
    ~Game();
    Game& operator=(const Game&) = delete;

    static Game* getInstance();
   
    void Initialize(const std::string& filename);
    void Run();

private:
    Game();

    int playerChoice();
    void processEnemyTurn(Character& enemy);

    void displayHealthBars(Character& player, Character& enemy);
    void displayPlayerStats();
    void displayCharactersArt(Character& enemy, int artIndex);
    void displayMenu();
    void clearScreen();
    std::string buildHealthBar(const Character& c);


private:
    static Game* instance;

    Character mainCharacter;
    Character* enemies;
    static const int enemiesCount = 15;

    int currentEnemyIndex;
    int defeatedEnemiesCount;

    std::vector<std::string> playerArt;
    std::vector<std::vector<std::string>> enemyArts;
};
