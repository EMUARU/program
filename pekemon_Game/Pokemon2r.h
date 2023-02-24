// ���_�_��
#pragma once
#include <iostream>
#include <vector>
using namespace std;

// �����O Pokemon2
class Pokemon2
{
public:
	Pokemon2(); // �ūغc�l
	Pokemon2(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �u�غc�l
	int getID() const; // �^��ID
	string getName() const; // �^��Name
	string getType() const; // �^���ݩ�
	double getHP() const; // �^��HP
	double getMaxHP() const; // �^��MaxHP
	double getATK() const; // �^��ATK
	double getInitialATK() const; // �^��InitialATK
	double getDEF() const; // �^��DEF
	double getInitialDEF() const; // �^��InitialDEF
	double getSpeed() const; // �^��Speed
	double getInitialSpeed() const; // �^��InitialSpeed
	int getAbility() const; // �^��Ability
	bool getLowerAttack() const; // �^�Ǵ�𪬺A
	bool getLowerDefence() const; // �^�Ǵ���A
	bool getLowerSpeed() const; // �^�Ǵ�t���A
	bool getPoison() const; // �^�Ǽ@�r���A
	bool getAbilityIsActivated() const; // �^�ǯ�O�O�_�w�o��
	void setID(int id); // �]�mID
	void setName(string name); // �]�mName
	void setType(string type); // �]�m�ݩ�
	virtual void setHP(double hp, Pokemon2& poke, bool attack); // �]�mHP
	virtual void setATK(double atk); // �]�mATK
	virtual void setDEF(double def); // DEF
	virtual void setSpeed(double speed); // �]�mSpeed
	void setMaxHP(double hp); // �]�mMaxHP
	void setInitialATK(double atk); // �]�mInitialATK
	void setInitialDEF(double def); // �]�mInitialDEF
	void setInitialSpeed(double speed); // �]�mInitialSpeed
	void setAbility(int ability); // �]�mAbility
	void setCount(int countATK, int countDEF, int countSpeed, int countPoison); // �]�m�˼�
	void setLowerAttack(bool lowerAttack); // �]�m��𪬺A
	void setLowerDefence(bool lowerDefence); // �]�m����A
	void setLowerSpeed(bool lowerSpeed); // �]�m��t���A
	void setPoison(bool poison); // �]�m�@�r���A
	void setAbilityIsActivated(bool abilityIsActivated); // �]�m��O�O�_�w�o��
	void showStats() const; // �i�ܯ��_�_�����A
	virtual void attack(Pokemon2& poke); // ����
	void countdown(); // �˼�
	template < typename T, typename Ty >
	double getDamageRate(T atk, Ty def); // �^�Ƕˮ`���v
	void reset(); // ���m���_�_�����A
private:
	int ID = 0; // �����s��
	string Name = ""; // �����W�r
	string Type = ""; // �����ݩ�
	double HP = 0; // ������q
	double MaxHP = 0; // �����̤j��q
	double ATK = 0; // ���������O
	double InitialATK = 0; // ������l�����O
	double DEF = 0; // �������m�O
	double InitialDEF = 0; // ������l���m�O
	double Speed = 0; // �����t��
	double InitialSpeed = 0; // ������l�t��
	int Ability = 0; // ������O
	int CountLowerAttack = 0; // �������˼�
	int CountLowerDefence = 0; // ������˼�
	int CountLowerSpeed = 0; // ������t�˼�
	int CountPoison; // �����@�r�˼�
	bool LowerAttack = 0; // ������𪬺A
	bool LowerDefence = 0; // ��������A
	bool LowerSpeed = 0; // ������t���A
	bool Poison = 0; // �����@�r���A
	bool AbilityIsActivated = 0; // ������O�O�_�w�o��
	vector< vector< double > > damageRate; // �ˮ`���v
};

// �l���O Bulbasaur
class Bulbasaur : public Pokemon2 // a1
{
public:
	Bulbasaur(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Ivysaur
class Ivysaur : public Pokemon2 // a1
{
public:
	Ivysaur(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Venusaur
class Venusaur : public Pokemon2 // a1
{
public:
	Venusaur(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Charmander
class Charmander : public Pokemon2 // a2
{
public:
	Charmander(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Charmeleon
class Charmeleon : public Pokemon2 // a2
{
public:
	Charmeleon(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Charizard
class Charizard : public Pokemon2 // a2
{
public:
	Charizard(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Squirtle
class Squirtle : public Pokemon2 // a3
{
public:
	Squirtle(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Wartortle
class Wartortle : public Pokemon2 // a3
{
public:
	Wartortle(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Blastoise
class Blastoise : public Pokemon2 // a3
{
public:
	Blastoise(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Caterpie
class Caterpie : public Pokemon2 // a4
{
public:
	Caterpie(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Metapod
class Metapod : public Pokemon2 // a4
{
public:
	Metapod(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Butterfree
class Butterfree : public Pokemon2 // a4
{
public:
	Butterfree(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Weedle
class Weedle : public Pokemon2 // a5
{
public:
	Weedle(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Kakuna
class Kakuna : public Pokemon2 // a5
{
public:
	Kakuna(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Beedrill
class Beedrill : public Pokemon2 // a5
{
public:
	Beedrill(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Pidgey
class Pidgey : public Pokemon2 // a6
{
public:
	Pidgey(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Pidgeotto
class Pidgeotto : public Pokemon2 // a6
{
public:
	Pidgeotto(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Pidgeot
class Pidgeot : public Pokemon2 // a6
{
public:
	Pidgeot(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Rattata
class Rattata : public Pokemon2 // a0
{
public:
	Rattata(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Raticate
class Raticate : public Pokemon2 // a0
{
public:
	Raticate(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Spearow
class Spearow : public Pokemon2 // a7
{
public:
	Spearow(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Fearow
class Fearow : public Pokemon2 // a7
{
public:
	Fearow(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Ekans
class Ekans : public Pokemon2 // a8
{
public:
	Ekans(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Arbok
class Arbok : public Pokemon2 // a8
{
public:
	Arbok(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Pikachu
class Pikachu : public Pokemon2 // a9
{
public:
	Pikachu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Raichu
class Raichu : public Pokemon2 // a9
{
public:
	Raichu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Sandshrew
class Sandshrew : public Pokemon2 // a10
{
public:
	Sandshrew(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O Sandslash
class Sandslash : public Pokemon2 // a10
{
public:
	Sandslash(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
	void setHP(double hp, Pokemon2& poke, bool attack); // �l���O�]�m��q
};

// �l���O NidoranMesu
class NidoranMesu : public Pokemon2 // a11
{
public:
	NidoranMesu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Nidorina
class Nidorina : public Pokemon2 // a11
{
public:
	Nidorina(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Nidoqueen
class Nidoqueen : public Pokemon2 // a11
{
public:
	Nidoqueen(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O NidoranOsu
class NidoranOsu : public Pokemon2 // a12
{
public:
	NidoranOsu(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Nidorino
class Nidorino : public Pokemon2 // a12
{
public:
	Nidorino(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};

// �l���O Nidoking
class Nidoking : public Pokemon2 // a12
{
public:
	Nidoking(int type, const vector< Pokemon2 > list, vector< vector< double > > Rate); // �غc�l
	void attack(Pokemon2& poke); // �l���O�����Ҧ�
};