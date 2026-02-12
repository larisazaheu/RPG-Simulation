#include "Character.h"
#include <algorithm>
#include <iostream>

const int Character::baseAttackDamage = 2;
const int Character::baseDefence = 40;
const int Character::baseHealthPoints = 35;

const int Character::maxAttackDamage = 44;
const int Character::maxDefence = 450;
const int Character::maxHealthPoints = 300;

const int Character::startLevel = 1;
const int Character::startHealthPotionsCount = 4;
const int Character::healPotionRestorationEffect = 30;

Character::Character()
{
    name = "";
    level = startLevel;
    attackDamage = baseAttackDamage;
    defence = baseDefence;
    healthPoints = baseHealthPoints;
    remainingHealthPoints = baseHealthPoints;
    healthPotionsCount = startHealthPotionsCount;
}

Character::Character(std::string name, int attackDamage, int defence, int healthPoints)
{
    setName(name);
    setAttackDamage(attackDamage);
    setDefence(defence);
    setHealthPoints(healthPoints);

    level = startLevel;
    remainingHealthPoints = healthPoints;
    healthPotionsCount = startHealthPotionsCount;
}

void Character::setName(const std::string& newName) 
{
    name = newName; 
}

void Character::setLevel(int newLevel)
{
    if (newLevel >= 1) level = newLevel; 
}

void Character::setAttackDamage(int newAttack)
{
    if (newAttack < baseAttackDamage) attackDamage = baseAttackDamage;
    else if (newAttack > maxAttackDamage) attackDamage = maxAttackDamage;
    else attackDamage = newAttack;
}

void Character::setDefence(int newDefence)
{
    if (newDefence < baseDefence) defence = baseDefence;
    else if (newDefence > maxDefence) defence = maxDefence;
    else defence = newDefence;
}

void Character::setHealthPoints(int newHealth)
{
    if (newHealth < baseHealthPoints) healthPoints = baseHealthPoints;
    else if (newHealth > maxHealthPoints) healthPoints = maxHealthPoints;
    else healthPoints = newHealth;

    remainingHealthPoints = healthPoints;
}

void Character::setRemainingHealthPoints(int newRemainingHealthPoints)
{
    if (newRemainingHealthPoints < 0) remainingHealthPoints = 0;
    else if (newRemainingHealthPoints > healthPoints) remainingHealthPoints = healthPoints;
    else remainingHealthPoints = newRemainingHealthPoints;
}

void Character::setHealthPotionsCount(int newHealthPotionsCount) 
{ 
    healthPotionsCount = newHealthPotionsCount; 
}


std::string Character::getName() const 
{ 
    return name; 
}
int Character::getLevel() const 
{
    return level; 
}

int Character::getAttackDamage() const
{
    return attackDamage;
}

int Character::getDefence() const 
{
    return defence; 
}

int Character::getHealthPoints() const 
{ 
    return healthPoints; 
}

int Character::getRemainingHealthPoints() const 
{
    return remainingHealthPoints;
}

int Character::getHealthPotionsCount() const
{
    return healthPotionsCount;
}

void Character::heal()
{
    if (healthPotionsCount > 0)
    {
        remainingHealthPoints += healPotionRestorationEffect;
        if (remainingHealthPoints > healthPoints) remainingHealthPoints = healthPoints;
        healthPotionsCount--;
    }
}

void Character::attack(Character& enemy)
{
    int damageDealt = attackDamage * std::min((double)enemy.healthPoints / enemy.defence, 1.0);
    enemy.setRemainingHealthPoints(enemy.getRemainingHealthPoints() - damageDealt);
}

bool Character::isAlive() 
{ 
    return remainingHealthPoints > 0;
}

bool Character::isDead() 
{ 
    return remainingHealthPoints <= 0;
}

void Character::levelUp()
{
    level++;
    setHealthPoints(healthPoints + baseHealthPoints);
    setDefence(defence + baseDefence);
    setAttackDamage(attackDamage + baseAttackDamage);
    remainingHealthPoints = healthPoints;

    std::cout << "\n*** You are now level " << level << " ***\n";
}

std::istream& operator>>(std::istream& in, Character& player)
{
    std::string name;
    int damage, health, defence;

    in >> name >> damage >> health >> defence;

    player.setName(name);
    player.setAttackDamage(damage);
    player.setHealthPoints(health);
    player.setDefence(defence);
    player.setHealthPotionsCount(Character::startHealthPotionsCount);
    player.setLevel(Character::startLevel);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Character& player)
{
    out << player.getName() << " "
        << player.getAttackDamage() << " "
        << player.getRemainingHealthPoints() << " "
        << player.getDefence();
    return out;
}

bool Character::operator<(const Character& other) const
{
    return (remainingHealthPoints * attackDamage * defence) <
        (other.remainingHealthPoints * other.attackDamage * other.defence);
}

bool Character::operator>(const Character& other) const
{
    return (remainingHealthPoints * attackDamage * defence) >
        (other.remainingHealthPoints * other.attackDamage * other.defence);
}

bool Character::operator==(const Character& other) const
{
    return (remainingHealthPoints * attackDamage * defence) ==
        (other.remainingHealthPoints * other.attackDamage * other.defence);
}


bool Character::operator!=(const Character& other) const 
{
    return !(*this == other); 
}

void Character::operator++() { 
    levelUp(); 
}

void Character::operator++(int) { 
    levelUp(); 
}
