#include <iostream>
#include <ctime>
#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon()
{
}

Pokemon::Pokemon(int number, const vector< Pokemon > list)
{
	for (int i(0); i < list.size(); i++)
		if (i == number - 1)
		{
			setID(list[i].ID);
			setName(list[i].Name);
			setType(list[i].Type);
			setHP(list[i].HP, *this, 0);
			setATK(list[i].ATK);
			setDEF(list[i].DEF);
			setSpeed(list[i].Speed);
			setMaxHP(list[i].MaxHP);
			setInitialATK(list[i].InitialATK);
			setInitialDEF(list[i].InitialDEF);
			setInitialSpeed(list[i].InitialSpeed);
			setAbility(list[i].Ability);
			break;
		}
}

int Pokemon::getID() const
{
	return ID;
}

string Pokemon::getName() const
{
	return Name;
}

string Pokemon::getType() const
{
	return Type;
}

double Pokemon::getHP() const
{
	return HP;
}

double Pokemon::getMaxHP() const
{
	return MaxHP;
}

double Pokemon::getATK() const
{
	return ATK;
}

double Pokemon::getDEF() const
{
	return DEF;
}

double Pokemon::getSpeed() const
{
	return Speed;
}

int Pokemon::getAbility() const
{
	return Ability;
}

int Pokemon::getCount() const
{
	return Ability;
}

bool Pokemon::getLowerAttack() const
{
	return LowerAttack;
}

bool Pokemon::getLowerDefence() const
{
	return LowerDefence;
}

bool Pokemon::getLowerSpeed() const
{
	return LowerSpeed;
}

bool Pokemon::getPoison() const
{
	return Poison;
}

bool Pokemon::getAbilityIsActivated() const
{
	return AbilityIsActivated;
}

void Pokemon::setID(int id)
{
	ID = id;
}

void Pokemon::setName(string name)
{
	Name = name;
}

void Pokemon::setType(string type)
{
	Type = type;
}

void Pokemon::setHP(double hp, Pokemon& poke, bool attack)
{
	HP = hp;
}

void Pokemon::setATK(double atk)
{
	ATK = atk;
}

void Pokemon::setDEF(double def)
{
	DEF = def;
}

void Pokemon::setSpeed(double speed)
{
	Speed = speed;
}

void Pokemon::setMaxHP(double hp)
{
	HP = MaxHP = hp;
}

void Pokemon::setInitialATK(double atk)
{
	ATK  = InitialATK = atk;
}

void Pokemon::setInitialDEF(double def)
{
	DEF = InitialDEF = def;
}

void Pokemon::setInitialSpeed(double speed)
{
	Speed = InitialSpeed = speed;
}

void Pokemon::setAbility(int ability)
{
	Ability = ability;
}

void Pokemon::setCount(int count)
{
	Count = count;
}

void Pokemon::setLowerAttack(bool lowerAttack)
{
	LowerAttack = lowerAttack;
}

void Pokemon::setLowerDefence(bool lowerDefence)
{
	LowerDefence = lowerDefence;
}

void Pokemon::setLowerSpeed(bool lowerSpeed)
{
	LowerSpeed = lowerSpeed;
}

void Pokemon::setPoison(bool poison)
{
	Poison = poison;
}

void Pokemon::setAbilityIsActivated(bool abilityIsActivated)
{
	AbilityIsActivated = abilityIsActivated;
}

void Pokemon::showStats() const
{

}

void Pokemon::attack(Pokemon& poke)
{
}

void Pokemon::countdown()
{
	if (Count > 0)
	{
		if (getPoison())
			setHP(getHP() - 2, *this, 0);
		if (getLowerSpeed() && Count == 2)
			setSpeed(getSpeed() - 2);
		if (getLowerDefence() && Count == 2)
			setDEF(getDEF() - 2);
		if (getLowerAttack() && Count == 2)
			setATK(getATK() - 2);
		--Count;

		if (Count == 0)
		{
			Poison = 0;
			LowerSpeed = 0;
			LowerDefence = 0;
			LowerAttack = 0;
		}
	}
}

void Pokemon::reset()
{
	HP = MaxHP;
	ATK = InitialATK;
	DEF = InitialDEF;
	Speed = InitialSpeed;
	Count = 0;
	LowerAttack = 0;
	LowerDefence = 0;
	LowerSpeed = 0;
	Poison = 0;
	AbilityIsActivated = 0;
}

Type0::Type0(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type0::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);
}

Type1::Type1(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type1::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	setHP(getHP() + 3, *this, 1);

	if(getHP() > getMaxHP())
		setHP(getMaxHP(), *this, 0);
}

Type2::Type2(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type2::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	srand(time(0));

	poke.setHP(poke.getHP() - (rand() % 3 + 1.0), *this, 0);
}

Type3::Type3(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type3::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);
}

void Type3::setHP(double hp, Pokemon& poke, bool attack)
{
	Pokemon::setHP(hp, *this, attack);

	if (hp < getHP() && &poke != this)
		poke.setHP(poke.getHP() - ((getHP() - hp) / 5), *this, 0);
}

Type4::Type4(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type4::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);
}

void Type4::setATK()
{
	Pokemon::setATK(getATK());
}

void Type4::setDEF()
{
	Pokemon::setDEF(getDEF());
}

void Type4::setSpeed()
{
	Pokemon::setSpeed(getSpeed());
}

Type5::Type5(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type5::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF() - 2, *this, 1);

	setHP(getHP() + (rand() % 2 + 2.0), *this, 0);
}

Type6::Type6(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type6::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);
}

void Type6::setHP(double hp, Pokemon& poke, bool attack)
{
	if (attack)
	{
		if(rand() % 5)
			Pokemon::setHP(hp, *this, attack);
	}
	else
		Pokemon::setHP(hp, *this, attack);
}

Type7::Type7(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type7::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	if (!(rand() % 5))
		poke.setHP(getATK() - poke.getDEF(), *this, 1);
}

Type8::Type8(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type8::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	if (!getAbilityIsActivated())
	{
		poke.setCount(2);
		poke.setPoison(1);
		setAbilityIsActivated(1);
	}
}

Type9::Type9(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type9::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	if (!getAbilityIsActivated())
	{
		poke.setCount(2);
		poke.setLowerSpeed(1);
		setAbilityIsActivated(1);
	}
}

Type10::Type10(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type10::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);
}

void Type10::setHP(double hp, Pokemon& poke, bool attack)
{
	double currentHP = getHP();

	if (hp < getHP())
		Pokemon::setHP(hp + 2, *this, 0);

	if (getHP() > currentHP)
		setHP(currentHP, *this, 0);
}

Type11::Type11(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type11::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	if (!getAbilityIsActivated())
	{
		poke.setCount(2);
		poke.setLowerDefence(1);
		setAbilityIsActivated(1);
	}
}

Type12::Type12(int type, const vector< Pokemon > list)
	:Pokemon(type, list)
{
}

void Type12::attack(Pokemon& poke)
{
	poke.setHP(getATK() - poke.getDEF(), *this, 1);

	if (!getAbilityIsActivated())
	{
		poke.setCount(2);
		poke.setLowerAttack(1);
		setAbilityIsActivated(1);
	}
}