// 神奇寶貝
#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 父類別 Pokemon2
class Pokemon2
{
public:
	Pokemon2(); // 空建構子
	Pokemon2(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 真建構子
	int getID() const; // 回傳ID
	string getName() const; // 回傳Name
	string getType() const; // 回傳屬性
	double getHP() const; // 回傳HP
	double getMaxHP() const; // 回傳MaxHP
	double getATK() const; // 回傳ATK
	double getInitialATK() const; // 回傳InitialATK
	double getDEF() const; // 回傳DEF
	double getInitialDEF() const; // 回傳InitialDEF
	double getSpeed() const; // 回傳Speed
	double getInitialSpeed() const; // 回傳InitialSpeed
	int getAbility() const; // 回傳Ability
	bool getLowerAttack() const; // 回傳減攻狀態
	bool getLowerDefence() const; // 回傳減防狀態
	bool getLowerSpeed() const; // 回傳減速狀態
	bool getPoison() const; // 回傳劇毒狀態
	bool getAbilityIsActivated() const; // 回傳能力是否已發動
	void setID(int id); // 設置ID
	void setName(string name); // 設置Name
	void setType(string type); // 設置屬性
	virtual void setHP(double hp, Pokemon2& poke, bool attack); // 設置HP
	virtual void setATK(double atk); // 設置ATK
	virtual void setDEF(double def); // DEF
	virtual void setSpeed(double speed); // 設置Speed
	void setMaxHP(double hp); // 設置MaxHP
	void setInitialATK(double atk); // 設置InitialATK
	void setInitialDEF(double def); // 設置InitialDEF
	void setInitialSpeed(double speed); // 設置InitialSpeed
	void setAbility(int ability); // 設置Ability
	void setCount(int countATK, int countDEF, int countSpeed, int countPoison); // 設置倒數
	void setLowerAttack(bool lowerAttack); // 設置減攻狀態
	void setLowerDefence(bool lowerDefence); // 設置減防狀態
	void setLowerSpeed(bool lowerSpeed); // 設置減速狀態
	void setPoison(bool poison); // 設置劇毒狀態
	void setAbilityIsActivated(bool abilityIsActivated); // 設置能力是否已發動
	void showStats() const; // 展示神奇寶貝狀態
	virtual void attack(Pokemon2& poke); // 攻擊
	void countdown(); // 倒數
	template < typename T, typename Ty >
	double getDamageRate(T atk, Ty def); // 回傳傷害倍率
	void reset(); // 重置神奇寶貝狀態
private:
	int ID = 0; // 紀錄編號
	string Name = ""; // 紀錄名字
	string Type = ""; // 紀錄屬性
	double HP = 0; // 紀錄血量
	double MaxHP = 0; // 紀錄最大血量
	double ATK = 0; // 紀錄攻擊力
	double InitialATK = 0; // 紀錄初始攻擊力
	double DEF = 0; // 紀錄防禦力
	double InitialDEF = 0; // 紀錄初始防禦力
	double Speed = 0; // 紀錄速度
	double InitialSpeed = 0; // 紀錄初始速度
	int Ability = 0; // 紀錄能力
	int CountLowerAttack = 0; // 紀錄減攻倒數
	int CountLowerDefence = 0; // 紀錄減防倒數
	int CountLowerSpeed = 0; // 紀錄減速倒數
	int CountPoison; // 紀錄劇毒倒數
	bool LowerAttack = 0; // 紀錄減攻狀態
	bool LowerDefence = 0; // 紀錄減防狀態
	bool LowerSpeed = 0; // 紀錄減速狀態
	bool Poison = 0; // 紀錄劇毒狀態
	bool AbilityIsActivated = 0; // 紀錄能力是否已發動
	vector< vector< double > > damageRate; // 傷害倍率
};

// 子類別 Bulbasaur
class Bulbasaur : public Pokemon2 // a1
{
public:
	Bulbasaur(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Ivysaur
class Ivysaur : public Pokemon2 // a1
{
public:
	Ivysaur(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Venusaur
class Venusaur : public Pokemon2 // a1
{
public:
	Venusaur(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Charmander
class Charmander : public Pokemon2 // a2
{
public:
	Charmander(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Charmeleon
class Charmeleon : public Pokemon2 // a2
{
public:
	Charmeleon(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Charizard
class Charizard : public Pokemon2 // a2
{
public:
	Charizard(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Squirtle
class Squirtle : public Pokemon2 // a3
{
public:
	Squirtle(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Wartortle
class Wartortle : public Pokemon2 // a3
{
public:
	Wartortle(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Blastoise
class Blastoise : public Pokemon2 // a3
{
public:
	Blastoise(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Caterpie
class Caterpie : public Pokemon2 // a4
{
public:
	Caterpie(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Metapod
class Metapod : public Pokemon2 // a4
{
public:
	Metapod(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Butterfree
class Butterfree : public Pokemon2 // a4
{
public:
	Butterfree(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Weedle
class Weedle : public Pokemon2 // a5
{
public:
	Weedle(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Kakuna
class Kakuna : public Pokemon2 // a5
{
public:
	Kakuna(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Beedrill
class Beedrill : public Pokemon2 // a5
{
public:
	Beedrill(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Pidgey
class Pidgey : public Pokemon2 // a6
{
public:
	Pidgey(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Pidgeotto
class Pidgeotto : public Pokemon2 // a6
{
public:
	Pidgeotto(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Pidgeot
class Pidgeot : public Pokemon2 // a6
{
public:
	Pidgeot(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Rattata
class Rattata : public Pokemon2 // a0
{
public:
	Rattata(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Raticate
class Raticate : public Pokemon2 // a0
{
public:
	Raticate(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Spearow
class Spearow : public Pokemon2 // a7
{
public:
	Spearow(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Fearow
class Fearow : public Pokemon2 // a7
{
public:
	Fearow(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Ekans
class Ekans : public Pokemon2 // a8
{
public:
	Ekans(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Arbok
class Arbok : public Pokemon2 // a8
{
public:
	Arbok(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Pikachu
class Pikachu : public Pokemon2 // a9
{
public:
	Pikachu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Raichu
class Raichu : public Pokemon2 // a9
{
public:
	Raichu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Sandshrew
class Sandshrew : public Pokemon2 // a10
{
public:
	Sandshrew(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 Sandslash
class Sandslash : public Pokemon2 // a10
{
public:
	Sandslash(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
	void setHP(double hp, Pokemon2& poke, bool attack); // 子類別設置血量
};

// 子類別 NidoranMesu
class NidoranMesu : public Pokemon2 // a11
{
public:
	NidoranMesu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Nidorina
class Nidorina : public Pokemon2 // a11
{
public:
	Nidorina(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Nidoqueen
class Nidoqueen : public Pokemon2 // a11
{
public:
	Nidoqueen(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 NidoranOsu
class NidoranOsu : public Pokemon2 // a12
{
public:
	NidoranOsu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Nidorino
class Nidorino : public Pokemon2 // a12
{
public:
	Nidorino(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};

// 子類別 Nidoking
class Nidoking : public Pokemon2 // a12
{
public:
	Nidoking(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // 建構子
	void attack(Pokemon2& poke); // 子類別攻擊模式
};