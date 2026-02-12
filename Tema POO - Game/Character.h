#pragma once
#include <string>

class Character
{
public:
    Character();
    Character(std::string name, int attackDamage, int defence, int healthPoints);

    void setName(const std::string& newName);
    void setLevel(int newLevel);
    void setAttackDamage(int newAttack);
    void setDefence(int newDefence);
    void setHealthPoints(int newHealth);
    void setRemainingHealthPoints(int newRemainingHealthPoints);
    void setHealthPotionsCount(int newHealthPotionsCount);

    std::string getName() const;
    int getLevel() const;
    int getAttackDamage() const;
    int getDefence() const;
    int getHealthPoints() const;
    int getRemainingHealthPoints() const;
    int getHealthPotionsCount() const;

    void heal();
    void attack(Character& enemy);
    bool isAlive();
    bool isDead();
    void levelUp();

public:
    static const int baseAttackDamage;
    static const int baseDefence;
    static const int baseHealthPoints;

    static const int maxAttackDamage;
    static const int maxDefence;
    static const int maxHealthPoints;

    static const int startLevel;
    static const int startHealthPotionsCount;
    static const int healPotionRestorationEffect;

    bool operator < (const Character& other) const;
    bool operator > (const Character& other) const;
    bool operator ==(const Character& other) const;
    bool operator !=(const Character& other) const;
    void operator ++();
    void operator ++(int);

private:
    std::string name;
    int level;
    int attackDamage;
    int defence;
    int healthPoints;
    int remainingHealthPoints;
    int healthPotionsCount;
};

std::istream& operator>>(std::istream& in, Character& player);
std::ostream& operator<<(std::ostream& out, const Character& player);
