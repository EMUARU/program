#ifndef POKEMON
#define POKEMON
#include <iostream>
#include <vector>
using namespace std;

class Pokemon
{
public:
	Pokemon();
	Pokemon(int type, const vector< Pokemon > list);
	int getID() const;
	string getName() const;
	string getType() const;
	double getHP() const;
	double getMaxHP() const;
	double getATK() const;
	double getDEF() const;
	double getSpeed() const;
	int getAbility() const;
	int getCount()const;
	bool getLowerAttack() const;
	bool getLowerDefence() const;
	bool getLowerSpeed() const;
	bool getPoison() const;
	bool getAbilityIsActivated() const;
	void setID(int id);
	void setName(string name);
	void setType(string type);
	virtual void setHP(double hp, Pokemon& poke, bool attack);
	virtual void setATK(double atk);
	virtual void setDEF(double def);
	virtual void setSpeed(double speed);
	void setMaxHP(double hp);
	void setInitialATK(double atk);
	void setInitialDEF(double def);
	void setInitialSpeed(double speed);
	void setAbility(int ability);
	void setCount(int count);
	void setLowerAttack(bool lowerAttack);
	void setLowerDefence(bool lowerDefence);
	void setLowerSpeed(bool lowerSpeed);
	void setPoison(bool poison);
	void setAbilityIsActivated(bool abilityIsActivated);
	void showStats() const;
	virtual void attack(Pokemon &poke);
	void countdown();
	void reset();
private:
	int ID = 0;
	string Name = "";
	string Type = "";
	double HP = 0;
	double MaxHP = 0;
	double ATK = 0;
	double InitialATK = 0;
	double DEF = 0;
	double InitialDEF = 0;
	double Speed = 0;
	double InitialSpeed = 0;
	int Ability = 0;
	int Count = 0;
	bool LowerAttack = 0;
	bool LowerDefence = 0;
	bool LowerSpeed = 0;
	bool Poison = 0;
	bool AbilityIsActivated = 0;
};

class Type0 : public Pokemon
{
public:
	Type0(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type1 : public Pokemon
{
public:
	Type1(int number, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type2 : public Pokemon
{
public:
	Type2(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type3 : public Pokemon
{
public:
	Type3(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
	void setHP(double hp, Pokemon& poke, bool attack);
};

class Type4 : public Pokemon
{
public:
	Type4(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
	void setATK();
	void setDEF();
	void setSpeed();
};

class Type5 : public Pokemon
{
public:
	Type5(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type6 : public Pokemon
{
public:
	Type6(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
	void setHP(double hp, Pokemon& poke, bool attack);
};

class Type7 : public Pokemon
{
public:
	Type7(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type8 : public Pokemon
{
public:
	Type8(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type9 : public Pokemon
{
public:
	Type9(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type10 : public Pokemon
{
public:
	Type10(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
	void setHP(double hp, Pokemon& poke, bool attack);
};

class Type11 : public Pokemon
{
public:
	Type11(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

class Type12 : public Pokemon
{
public:
	Type12(int type, const vector< Pokemon > list);
	void attack(Pokemon& poke);
};

#endif // !POKEMON