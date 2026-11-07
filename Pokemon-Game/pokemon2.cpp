// 神奇寶貝們
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Pokemon2r.h"
#include "rlutil.h"

using namespace rlutil;
using namespace std;

// 空建構子
Pokemon2::Pokemon2()
{
}

// 初始化神奇寶貝
Pokemon2::Pokemon2(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate)
{
	setID(list[number - 1].ID); // 設置ID
	setName(list[number - 1].Name); // 設置Name
	setType(list[number - 1].Type); // 設置Type
	setHP(list[number - 1].HP, *this, 0); // 設置HP
	setATK(list[number - 1].ATK); // 設置ATK
	setDEF(list[number - 1].DEF); // 設置DEF
	setSpeed(list[number - 1].Speed); // 設置Speed
	setMaxHP(list[number - 1].MaxHP); // 設置MaxHP
	setInitialATK(list[number - 1].InitialATK); // 設置InitialATK
	setInitialDEF(list[number - 1].InitialDEF); // 設置InitialDEF
	setInitialSpeed(list[number - 1].InitialSpeed); // 設置InitialSpeed
	setAbility(list[number - 1].Ability); // 設置Ability

	damageRate = Rate; // 設置傷害倍率
}

// 回傳ID
int Pokemon2::getID() const
{
	return ID; // 回傳ID
}

// 回傳Name
string Pokemon2::getName() const
{
	return Name; // 回傳Name
}

// 回傳Type
string Pokemon2::getType() const
{
	return Type; // 回傳Type
}

// 回傳HP
double Pokemon2::getHP() const
{
	return HP; // 回傳HP
}

// 回傳MaxHP
double Pokemon2::getMaxHP() const
{
	return MaxHP; // 回傳MaxHP
}

// 回傳ATK
double Pokemon2::getATK() const
{
	return ATK; // 回傳ATK
}

// 回傳DEF
double Pokemon2::getDEF() const
{
	return DEF; // 回傳DEF
}

// 回傳Speed
double Pokemon2::getSpeed() const
{
	return Speed; // 回傳Speed
}

// 回傳能力
int Pokemon2::getAbility() const
{
	return Ability; // 回傳能力
}

// 回傳是否為減攻狀態
bool Pokemon2::getLowerAttack() const
{
	return LowerAttack; // 回傳是否為減攻狀態
}

// 回傳是否為減防狀態
bool Pokemon2::getLowerDefence() const
{
	return LowerDefence; // 回傳是否為減防狀態
}

// 回傳是否為減速狀態
bool Pokemon2::getLowerSpeed() const
{
	return LowerSpeed; // 回傳是否為減速狀態
}

// 回傳是否為劇毒狀態
bool Pokemon2::getPoison() const
{
	return Poison; // 回傳是否為劇毒狀態
}

// 回傳能力是否已發動
bool Pokemon2::getAbilityIsActivated() const
{
	return AbilityIsActivated; // 回傳能力是否已發動
}

// 設置ID
void Pokemon2::setID(int id)
{
	ID = id; // 設置ID
}

// 設置Name
void Pokemon2::setName(string name)
{
	Name = name; // 設置Name
}

// 設置Type
void Pokemon2::setType(string type)
{
	Type = type; // 設置Type
}

// 設置HP　　　　　　新hp　　　　誰造成的　　　　是否為攻擊造成的
void Pokemon2::setHP(double hp, Pokemon2& poke, bool attack)
{
	HP = hp; // 設置HP
}

// 設置ATK
void Pokemon2::setATK(double atk)
{
	ATK = atk; // 設置ATK
}

// 設置DEF
void Pokemon2::setDEF(double def)
{
	DEF = def; // 設置DEF
}

// 設置Speed
void Pokemon2::setSpeed(double speed)
{
	Speed = speed; // 設置Speed
}

// 設置MaxHP
void Pokemon2::setMaxHP(double hp)
{
	HP = MaxHP = hp; // 設置MaxHP
}

// 設置InitialATK
void Pokemon2::setInitialATK(double atk)
{
	ATK = InitialATK = atk; // 設置InitialATK
}

// 設置InitialDEF
void Pokemon2::setInitialDEF(double def)
{
	DEF = InitialDEF = def; // 設置InitialDEF
}

// 設置InitialSpeed
void Pokemon2::setInitialSpeed(double speed)
{
	Speed = InitialSpeed = speed; // 設置InitialSpeed
}

// 設置
void Pokemon2::setAbility(int ability)
{
	Ability = ability; // 設置能力
}

// 設置倒數計數器
void Pokemon2::setCount(int countATK, int countDEF, int countSpeed, int countPoison)
{ // 設置各種倒數計數器
	CountLowerAttack = countATK;
	CountLowerDefence = countDEF;
	CountLowerSpeed = countSpeed;
	CountPoison = countPoison;
}

// 設置減攻狀態
void Pokemon2::setLowerAttack(bool lowerAttack)
{
	LowerAttack = lowerAttack; // 設置減攻狀態
}

// 設置減防狀態
void Pokemon2::setLowerDefence(bool lowerDefence)
{
	LowerDefence = lowerDefence; // 設置減防狀態
}

// 設置減速狀態
void Pokemon2::setLowerSpeed(bool lowerSpeed)
{
	LowerSpeed = lowerSpeed; // 設置減速狀態
}

// 設置劇毒狀態
void Pokemon2::setPoison(bool poison)
{
	Poison = poison; // 設置劇毒狀態
}

// 設置能力發動狀態
void Pokemon2::setAbilityIsActivated(bool abilityIsActivated)
{
	AbilityIsActivated = abilityIsActivated; // 設置能力發動狀態
}

// 輸出神奇寶貝狀態
void Pokemon2::showStats() const
{ // 輸出神奇寶貝狀態
	std::cout << std::setw(10) << getName() << " ( " << std::setw(2) << (getHP() > 0 ? getHP() : 0) << " / " << std::setw(2) << getMaxHP() << " )" << std::endl;// 輸出狀態
}

// 虛擬攻擊函式
void Pokemon2::attack(Pokemon2& poke)
{
}

// 倒數
void Pokemon2::countdown()
{
	if (CountLowerAttack == 0) // 若倒數歸０則解除狀態
	{
		LowerAttack = 0;
		ATK = InitialATK;
	}
	if (CountLowerDefence == 0)
	{
		LowerDefence = 0;
		DEF = InitialDEF;
	}
	if (CountLowerSpeed == 0)
	{
		LowerSpeed = 0;
		Speed = InitialSpeed;
	}
	if (CountPoison == 0)
		Poison = 0;

	if (CountLowerAttack > 0 || CountLowerDefence > 0 || CountLowerSpeed > 0 || CountPoison > 0)
	{
		if (getPoison()) // 根據狀態調降數值
			setHP(getHP() - 2, *this, 0);
		if (getLowerSpeed() && CountLowerSpeed == 2)
			setSpeed(getSpeed() - 2);
		if (getLowerDefence() && CountLowerDefence == 2)
			setDEF(getDEF() - 2);
		if (getLowerAttack() && CountLowerAttack == 2)
			setATK(getATK() - 2);

		if (CountLowerAttack > 0) // 倒數
			--CountLowerAttack;
		if (CountLowerDefence > 0)
			--CountLowerDefence;
		if (CountLowerSpeed > 0)
			--CountLowerSpeed;
		if (CountPoison > 0)
			--CountPoison;
	}
}

// 回傳傷害倍率
template < typename T, typename Ty >
double Pokemon2::getDamageRate(T atk, Ty def)
{
	Pokemon2 *pokemons[2] = {&atk, &def};
	int Type[2] = {0, 0};

	for (int i(0); i < 2; i++) // 根據雙方屬性決定傷害倍率
	{
		if (pokemons[i]->getType() == "Fire")
			Type[i] = 1;
		else if (pokemons[i]->getType() == "Water")
			Type[i] = 2;
		else if (pokemons[i]->getType() == "Electric")
			Type[i] = 3;
		else if (pokemons[i]->getType() == "Grass")
			Type[i] = 4;
		else if (pokemons[i]->getType() == "Ice")
			Type[i] = 5;
		else if (pokemons[i]->getType() == "Fighting")
			Type[i] = 6;
		else if (pokemons[i]->getType() == "Poison")
			Type[i] = 7;
		else if (pokemons[i]->getType() == "Ground")
			Type[i] = 8;
		else if (pokemons[i]->getType() == "Flying")
			Type[i] = 9;
		else if (pokemons[i]->getType() == "Psychic")
			Type[i] = 10;
		else if (pokemons[i]->getType() == "Bug")
			Type[i] = 11;
		else if (pokemons[i]->getType() == "Rock")
			Type[i] = 12;
		else if (pokemons[i]->getType() == "Ghost")
			Type[i] = 13;
		else if (pokemons[i]->getType() == "Dragon")
			Type[i] = 14;
		else if (pokemons[i]->getType() == "Dark")
			Type[i] = 15;
		else if (pokemons[i]->getType() == "Steel")
			Type[i] = 16;
		else if (pokemons[i]->getType() == "Fairy")
			Type[i] = 17;
	}
	return damageRate[Type[0]][Type[1]]; // 回傳傷害倍率
}

// 回傳InitialATK
double Pokemon2::getInitialATK() const
{
	return InitialATK; // 回傳InitialATK
}

// 回傳InitialDEF
double Pokemon2::getInitialDEF() const
{
	return InitialDEF; // 回傳InitialDEF
}

// 回傳InitialSpeed
double Pokemon2::getInitialSpeed() const
{
	return InitialSpeed; // 回傳InitialSpeed
}

// 回復初始狀態
void Pokemon2::reset()
{
	Pokemon2::setHP(getMaxHP(), *this, 0);
	setATK(getInitialATK());
	setDEF(getInitialDEF());
	setSpeed(getInitialSpeed());
	setCount(0, 0, 0, 0);
	setLowerAttack(0);
	setLowerDefence(0);
	setLowerSpeed(0);
	setPoison(0);
	setAbilityIsActivated(0);
}

//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**
//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**//**//**/**//**//**

 // 子類別建構子　調用父類別建構子
Bulbasaur::Bulbasaur(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a1
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Bulbasaur::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	int oldHP(getHP());

	int newHP(getHP() + 3 > getMaxHP() ? getMaxHP() : getHP() + 3);

	setHP(newHP, *this, 0); // 回復生命

	if (getHP() - oldHP > 0) // 提示訊息
	{
		setColor(10);
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "已回復" << newHP - oldHP << "點生命 <<<<<<<<<<\n\n";
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Ivysaur::Ivysaur(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a1
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Ivysaur::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	int oldHP(getHP());

	int newHP(getHP() + 3 > getMaxHP() ? getMaxHP() : getHP() + 3);

	setHP(newHP, *this, 0); // 回復生命

	if (getHP() - oldHP > 0) // 提示訊息
	{
		setColor(10);
		cout << endl << "     >>>>>>>>>> " << this->getName() << "已回復" << newHP - oldHP << "點生命 <<<<<<<<<<\n\n";
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Venusaur::Venusaur(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a1
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Venusaur::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	int oldHP(getHP());

	int newHP(getHP() + 3 > getMaxHP() ? getMaxHP() : getHP() + 3);

	setHP(newHP, *this, 0); // 回復生命

	if (getHP() - oldHP > 0) // 提示訊息
	{
		setColor(10);
		cout << endl << "     >>>>>>>>>> " << this->getName() << "已回復" << newHP - oldHP << "點生命 <<<<<<<<<<\n\n";
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Charmander::Charmander(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a2
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Charmander::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	srand(time(0));

	double damage(0);

	setColor(4); // 提示訊息
	cout << endl << "     >>>>>>>>>> "  << this->getName() << "對" << poke.getName() << "造成" << (damage = rand() % 3 + 1.0) << "點附加傷害 <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - damage, *this, 0); // 附加傷害

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Charmeleon::Charmeleon(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a2
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Charmeleon::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	double damage(0);

	setColor(4); // 提示訊息
	cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "造成" << (damage = rand() % 3 + 1.0) << "點附加傷害 <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - damage, *this, 0); // 附加傷害

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Charizard::Charizard(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a2
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Charizard::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	double damage(0);

	setColor(4); // 提示訊息
	cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "造成" << (damage = rand() % 3 + 1.0) << "點附加傷害 <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - damage, *this, 0); // 附加傷害

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Squirtle::Squirtle(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a3
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Squirtle::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Squirtle::setHP(double hp, Pokemon2& poke, bool attack)
{
	double damage((getHP() - hp) / 5);

	Pokemon2::setHP(hp, *this, attack);

	if (damage > 0)
	{
		setColor(1); // 提示訊息
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "對" << poke.getName() << "造成" << damage << "點反擊傷害 <<<<<<<<<<\n\n";
	}

	if (attack && &poke != this)
		poke.setHP(poke.getHP() - damage, *this, 0); // 反擊傷害

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Wartortle::Wartortle(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a3
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Wartortle::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Wartortle::setHP(double hp, Pokemon2& poke, bool attack)
{
	double damage((getHP() - hp) / 5);

	Pokemon2::setHP(hp, *this, attack);

	if (damage > 0)
	{
		setColor(1); // 提示訊息
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "造成" << damage << "點反擊傷害 <<<<<<<<<<\n\n";
	}

	if (attack && &poke != this)
		poke.setHP(poke.getHP() - damage, *this, 0); // 反擊傷害

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Blastoise::Blastoise(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a3
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Blastoise::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Blastoise::setHP(double hp, Pokemon2& poke, bool attack)
{
	double damage((getHP() - hp) / 5);

	Pokemon2::setHP(hp, *this, attack);

	if (damage > 0)
	{
		setColor(1); // 提示訊息
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "造成" << damage << "點反擊傷害 <<<<<<<<<<\n\n";
	}

	if (attack && &poke != this)
		poke.setHP(poke.getHP() - damage, *this, 0); // 反擊傷害

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Caterpie::Caterpie(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a4
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Caterpie::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別建構子　調用父類別建構子
Metapod::Metapod(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a4
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Metapod::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別建構子　調用父類別建構子
Butterfree::Butterfree(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a4
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Butterfree::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別建構子　調用父類別建構子
Weedle::Weedle(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a5
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Weedle::attack(Pokemon2& poke)
{
	setColor(15);

	int damage = rand() % 2 + 2.0;

	cout << endl << "     >>>>>>>>>> "  << this->getName() << "從" << poke.getName() << "吸收了" << damage << "點生命 <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke) - damage, *this, 1); // 攻擊傷害

	setHP(getHP() + (damage), *this, 0); // 吸收生命

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Kakuna::Kakuna(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a5
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Kakuna::attack(Pokemon2& poke)
{
	setColor(15);

	int damage = rand() % 2 + 2.0;

	cout << endl << "     >>>>>>>>>> "  << this->getName() << "從" << poke.getName() << "吸收了" << damage << "點生命 <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke) - damage, *this, 1); // 攻擊傷害

	setHP(getHP() + (damage), *this, 0); // 吸收生命

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Beedrill::Beedrill(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a5
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Beedrill::attack(Pokemon2& poke)
{
	setColor(15);

	int damage = rand() % 2 + 2.0;

	cout << endl << "     >>>>>>>>>> "  << this->getName() << "從" << poke.getName() << "吸收了" << damage << "點生命 <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke) - damage, *this, 1); // 攻擊傷害

	setHP(getHP() + (damage), *this, 0); // 吸收生命

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Pidgey::Pidgey(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a6
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Pidgey::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Pidgey::setHP(double hp, Pokemon2& poke, bool attack)
{
	if (attack)
	{
		if (rand() % 5)
			Pokemon2::setHP(hp, *this, attack);
		else
		{
			setColor(11); // 迴避傷害
			cout << endl << "     >>>>>>>>>> "  << this->getName() << "迴避了這次攻擊 <<<<<<<<<<\n\n";
		}
	}
	else
		Pokemon2::setHP(hp, *this, attack);

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Pidgeotto::Pidgeotto(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a6
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Pidgeotto::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Pidgeotto::setHP(double hp, Pokemon2& poke, bool attack)
{
	if (attack)
	{
		if (rand() % 5)
			Pokemon2::setHP(hp, *this, attack);
		else
		{
			setColor(11); // 迴避傷害
			cout << endl << "     >>>>>>>>>> " << this->getName() << "迴避了這次攻擊 <<<<<<<<<<\n\n";
		}
	}
	else
		Pokemon2::setHP(hp, *this, attack);

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Pidgeot::Pidgeot(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a6
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Pidgeot::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Pidgeot::setHP(double hp, Pokemon2& poke, bool attack)
{
	if (attack)
	{
		if (rand() % 5)
			Pokemon2::setHP(hp, *this, attack);
		else
		{
			setColor(11); // 迴避傷害
			cout << endl << "     >>>>>>>>>> " << this->getName() << "迴避了這次攻擊 <<<<<<<<<<\n\n";
		}
	}
	else
		Pokemon2::setHP(hp, *this, attack);

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Rattata::Rattata(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a0
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Rattata::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別建構子　調用父類別建構子
Raticate::Raticate(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a0
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Raticate::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別建構子　調用父類別建構子
Spearow::Spearow(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a7
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Spearow::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!(rand() % 5))
	{
		setColor(12); // 再次攻擊
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "發動了能力，進行兩次攻擊 <<<<<<<<<<\n\n";
		poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Fearow::Fearow(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a7
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Fearow::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!(rand() % 5))
	{
		setColor(12); // 再次攻擊
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "發動了能力，進行兩次攻擊 <<<<<<<<<<\n\n";
		poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Ekans::Ekans(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a8
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Ekans::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動劇毒
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "對" << poke.getName() << "發動了劇毒能力 <<<<<<<<<<\n\n";
		poke.setCount(0,0,0,2);
		poke.setPoison(1);
		setAbilityIsActivated(1);
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Arbok::Arbok(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a8
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Arbok::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動劇毒
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "對" << poke.getName() << "發動了劇毒能力 <<<<<<<<<<\n\n";
		poke.setCount(0,0,0,2);
		poke.setPoison(1);
		setAbilityIsActivated(1);
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Pikachu::Pikachu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a9
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Pikachu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(14); // 發動減速
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了速度弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(0, 0, 2, 0);
			poke.setLowerSpeed(1);
		}
	}
}

// 子類別建構子　調用父類別建構子
Raichu::Raichu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a9
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Raichu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{	
		setColor(14); // 發動減速
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了速度弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(0, 0, 2, 0);
			poke.setLowerSpeed(1);
		}
	}
}

// 子類別建構子　調用父類別建構子
Sandshrew::Sandshrew(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a10
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Sandshrew::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Sandshrew::setHP(double hp, Pokemon2& poke, bool attack)
{
	double currentHP = getHP();

	if (hp < getHP() && attack) // 發動減傷
	{
		Pokemon2::setHP(hp + 2, *this, 0);
		setColor(7);
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "發動了減傷能力 <<<<<<<<<<\n\n";
	}

	if (getHP() > currentHP)
		setHP(currentHP, *this, 0);

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Sandslash::Sandslash(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a10
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Sandslash::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害
}

// 子類別設定血量
void Sandslash::setHP(double hp, Pokemon2& poke, bool attack)
{
	double currentHP = getHP();

	if (hp < getHP() && attack) // 發動減傷
	{
		Pokemon2::setHP(hp + 2, *this, 0);
		setColor(7);
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "發動了減傷能力 <<<<<<<<<<\n\n";
	}

	if (getHP() > currentHP)
		setHP(currentHP, *this, 0);

	setColor(14);
}

// 子類別建構子　調用父類別建構子
NidoranMesu::NidoranMesu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a11
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void NidoranMesu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動減防
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了防禦弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(0, 2, 0, 0);
			poke.setLowerDefence(1);
		}
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Nidorina::Nidorina(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a11
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Nidorina::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動減防
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了防禦弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(0, 2, 0, 0);
			poke.setLowerDefence(1);
		}
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Nidoqueen::Nidoqueen(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a11
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Nidoqueen::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動減防
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了防禦弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(0, 2, 0, 0);
			poke.setLowerDefence(1);
		}
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
NidoranOsu::NidoranOsu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a12
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void NidoranOsu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動減攻
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了攻擊弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(2, 0, 0, 0);
			poke.setLowerAttack(1);
		}
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Nidorino::Nidorino(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a12
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Nidorino::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{
		setColor(13); // 發動減攻
		cout << endl << "     >>>>>>>>>> " << this->getName() << "對" << poke.getName() << "發動了攻擊弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(2, 0, 0, 0);
			poke.setLowerAttack(1);
		}
	}

	setColor(14);
}

// 子類別建構子　調用父類別建構子
Nidoking::Nidoking(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a12
	:Pokemon2(number, list, Rate)
{
}

// 子類別攻擊函式
void Nidoking::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // 攻擊傷害

	if (!getAbilityIsActivated())
	{	
		setColor(13); // 發動減攻
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "對" << poke.getName() << "發動了攻擊弱化能力 <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);
		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "不會受到數值弱化的效果 <<<<<<<<<<\n\n"; // 不受影響
			setColor(14);
		}
		else
		{
			poke.setCount(2, 0, 0, 0);
			poke.setLowerAttack(1);
		}
	}

	setColor(14);
}