// ���_�_����
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Pokemon2r.h"
#include "rlutil.h"

using namespace rlutil;
using namespace std;

// �ūغc�l
Pokemon2::Pokemon2()
{
}

// ��l�Ư��_�_��
Pokemon2::Pokemon2(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate)
{
	setID(list[number - 1].ID); // �]�mID
	setName(list[number - 1].Name); // �]�mName
	setType(list[number - 1].Type); // �]�mType
	setHP(list[number - 1].HP, *this, 0); // �]�mHP
	setATK(list[number - 1].ATK); // �]�mATK
	setDEF(list[number - 1].DEF); // �]�mDEF
	setSpeed(list[number - 1].Speed); // �]�mSpeed
	setMaxHP(list[number - 1].MaxHP); // �]�mMaxHP
	setInitialATK(list[number - 1].InitialATK); // �]�mInitialATK
	setInitialDEF(list[number - 1].InitialDEF); // �]�mInitialDEF
	setInitialSpeed(list[number - 1].InitialSpeed); // �]�mInitialSpeed
	setAbility(list[number - 1].Ability); // �]�mAbility

	damageRate = Rate; // �]�m�ˮ`���v
}

// �^��ID
int Pokemon2::getID() const
{
	return ID; // �^��ID
}

// �^��Name
string Pokemon2::getName() const
{
	return Name; // �^��Name
}

// �^��Type
string Pokemon2::getType() const
{
	return Type; // �^��Type
}

// �^��HP
double Pokemon2::getHP() const
{
	return HP; // �^��HP
}

// �^��MaxHP
double Pokemon2::getMaxHP() const
{
	return MaxHP; // �^��MaxHP
}

// �^��ATK
double Pokemon2::getATK() const
{
	return ATK; // �^��ATK
}

// �^��DEF
double Pokemon2::getDEF() const
{
	return DEF; // �^��DEF
}

// �^��Speed
double Pokemon2::getSpeed() const
{
	return Speed; // �^��Speed
}

// �^�ǯ�O
int Pokemon2::getAbility() const
{
	return Ability; // �^�ǯ�O
}

// �^�ǬO�_����𪬺A
bool Pokemon2::getLowerAttack() const
{
	return LowerAttack; // �^�ǬO�_����𪬺A
}

// �^�ǬO�_������A
bool Pokemon2::getLowerDefence() const
{
	return LowerDefence; // �^�ǬO�_������A
}

// �^�ǬO�_����t���A
bool Pokemon2::getLowerSpeed() const
{
	return LowerSpeed; // �^�ǬO�_����t���A
}

// �^�ǬO�_���@�r���A
bool Pokemon2::getPoison() const
{
	return Poison; // �^�ǬO�_���@�r���A
}

// �^�ǯ�O�O�_�w�o��
bool Pokemon2::getAbilityIsActivated() const
{
	return AbilityIsActivated; // �^�ǯ�O�O�_�w�o��
}

// �]�mID
void Pokemon2::setID(int id)
{
	ID = id; // �]�mID
}

// �]�mName
void Pokemon2::setName(string name)
{
	Name = name; // �]�mName
}

// �]�mType
void Pokemon2::setType(string type)
{
	Type = type; // �]�mType
}

// �]�mHP�@�@�@�@�@�@�shp�@�@�@�@�ֳy�����@�@�@�@�O�_�������y����
void Pokemon2::setHP(double hp, Pokemon2& poke, bool attack)
{
	HP = hp; // �]�mHP
}

// �]�mATK
void Pokemon2::setATK(double atk)
{
	ATK = atk; // �]�mATK
}

// �]�mDEF
void Pokemon2::setDEF(double def)
{
	DEF = def; // �]�mDEF
}

// �]�mSpeed
void Pokemon2::setSpeed(double speed)
{
	Speed = speed; // �]�mSpeed
}

// �]�mMaxHP
void Pokemon2::setMaxHP(double hp)
{
	HP = MaxHP = hp; // �]�mMaxHP
}

// �]�mInitialATK
void Pokemon2::setInitialATK(double atk)
{
	ATK = InitialATK = atk; // �]�mInitialATK
}

// �]�mInitialDEF
void Pokemon2::setInitialDEF(double def)
{
	DEF = InitialDEF = def; // �]�mInitialDEF
}

// �]�mInitialSpeed
void Pokemon2::setInitialSpeed(double speed)
{
	Speed = InitialSpeed = speed; // �]�mInitialSpeed
}

// �]�m
void Pokemon2::setAbility(int ability)
{
	Ability = ability; // �]�m��O
}

// �]�m�˼ƭp�ƾ�
void Pokemon2::setCount(int countATK, int countDEF, int countSpeed, int countPoison)
{ // �]�m�U�ح˼ƭp�ƾ�
	CountLowerAttack = countATK;
	CountLowerDefence = countDEF;
	CountLowerSpeed = countSpeed;
	CountPoison = countPoison;
}

// �]�m��𪬺A
void Pokemon2::setLowerAttack(bool lowerAttack)
{
	LowerAttack = lowerAttack; // �]�m��𪬺A
}

// �]�m����A
void Pokemon2::setLowerDefence(bool lowerDefence)
{
	LowerDefence = lowerDefence; // �]�m����A
}

// �]�m��t���A
void Pokemon2::setLowerSpeed(bool lowerSpeed)
{
	LowerSpeed = lowerSpeed; // �]�m��t���A
}

// �]�m�@�r���A
void Pokemon2::setPoison(bool poison)
{
	Poison = poison; // �]�m�@�r���A
}

// �]�m��O�o�ʪ��A
void Pokemon2::setAbilityIsActivated(bool abilityIsActivated)
{
	AbilityIsActivated = abilityIsActivated; // �]�m��O�o�ʪ��A
}

// ��X���_�_�����A
void Pokemon2::showStats() const
{ // ��X���_�_�����A
	std::cout << std::setw(10) << getName() << " ( " << std::setw(2) << (getHP() > 0 ? getHP() : 0) << " / " << std::setw(2) << getMaxHP() << " )" << std::endl;// ��X���A
}

// ���������禡
void Pokemon2::attack(Pokemon2& poke)
{
}

// �˼�
void Pokemon2::countdown()
{
	if (CountLowerAttack == 0) // �Y�˼��k���h�Ѱ����A
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
		if (getPoison()) // �ھڪ��A�խ��ƭ�
			setHP(getHP() - 2, *this, 0);
		if (getLowerSpeed() && CountLowerSpeed == 2)
			setSpeed(getSpeed() - 2);
		if (getLowerDefence() && CountLowerDefence == 2)
			setDEF(getDEF() - 2);
		if (getLowerAttack() && CountLowerAttack == 2)
			setATK(getATK() - 2);

		if (CountLowerAttack > 0) // �˼�
			--CountLowerAttack;
		if (CountLowerDefence > 0)
			--CountLowerDefence;
		if (CountLowerSpeed > 0)
			--CountLowerSpeed;
		if (CountPoison > 0)
			--CountPoison;
	}
}

// �^�Ƕˮ`���v
template < typename T, typename Ty >
double Pokemon2::getDamageRate(T atk, Ty def)
{
	Pokemon2 *pokemons[2] = {&atk, &def};
	int Type[2] = {0, 0};

	for (int i(0); i < 2; i++) // �ھ������ݩʨM�w�ˮ`���v
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
	return damageRate[Type[0]][Type[1]]; // �^�Ƕˮ`���v
}

// �^��InitialATK
double Pokemon2::getInitialATK() const
{
	return InitialATK; // �^��InitialATK
}

// �^��InitialDEF
double Pokemon2::getInitialDEF() const
{
	return InitialDEF; // �^��InitialDEF
}

// �^��InitialSpeed
double Pokemon2::getInitialSpeed() const
{
	return InitialSpeed; // �^��InitialSpeed
}

// �^�_��l���A
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

 // �l���O�غc�l�@�եΤ����O�غc�l
Bulbasaur::Bulbasaur(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a1
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Bulbasaur::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	int oldHP(getHP());

	int newHP(getHP() + 3 > getMaxHP() ? getMaxHP() : getHP() + 3);

	setHP(newHP, *this, 0); // �^�_�ͩR

	if (getHP() - oldHP > 0) // ���ܰT��
	{
		setColor(10);
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "�w�^�_" << newHP - oldHP << "�I�ͩR <<<<<<<<<<\n\n";
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Ivysaur::Ivysaur(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a1
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Ivysaur::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	int oldHP(getHP());

	int newHP(getHP() + 3 > getMaxHP() ? getMaxHP() : getHP() + 3);

	setHP(newHP, *this, 0); // �^�_�ͩR

	if (getHP() - oldHP > 0) // ���ܰT��
	{
		setColor(10);
		cout << endl << "     >>>>>>>>>> " << this->getName() << "�w�^�_" << newHP - oldHP << "�I�ͩR <<<<<<<<<<\n\n";
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Venusaur::Venusaur(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a1
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Venusaur::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	int oldHP(getHP());

	int newHP(getHP() + 3 > getMaxHP() ? getMaxHP() : getHP() + 3);

	setHP(newHP, *this, 0); // �^�_�ͩR

	if (getHP() - oldHP > 0) // ���ܰT��
	{
		setColor(10);
		cout << endl << "     >>>>>>>>>> " << this->getName() << "�w�^�_" << newHP - oldHP << "�I�ͩR <<<<<<<<<<\n\n";
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Charmander::Charmander(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a2
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Charmander::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	srand(time(0));

	double damage(0);

	setColor(4); // ���ܰT��
	cout << endl << "     >>>>>>>>>> "  << this->getName() << "��" << poke.getName() << "�y��" << (damage = rand() % 3 + 1.0) << "�I���[�ˮ` <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - damage, *this, 0); // ���[�ˮ`

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Charmeleon::Charmeleon(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a2
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Charmeleon::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	double damage(0);

	setColor(4); // ���ܰT��
	cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�y��" << (damage = rand() % 3 + 1.0) << "�I���[�ˮ` <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - damage, *this, 0); // ���[�ˮ`

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Charizard::Charizard(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a2
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Charizard::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	double damage(0);

	setColor(4); // ���ܰT��
	cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�y��" << (damage = rand() % 3 + 1.0) << "�I���[�ˮ` <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - damage, *this, 0); // ���[�ˮ`

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Squirtle::Squirtle(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a3
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Squirtle::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Squirtle::setHP(double hp, Pokemon2& poke, bool attack)
{
	double damage((getHP() - hp) / 5);

	Pokemon2::setHP(hp, *this, attack);

	if (damage > 0)
	{
		setColor(1); // ���ܰT��
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "��" << poke.getName() << "�y��" << damage << "�I�����ˮ` <<<<<<<<<<\n\n";
	}

	if (attack && &poke != this)
		poke.setHP(poke.getHP() - damage, *this, 0); // �����ˮ`

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Wartortle::Wartortle(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a3
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Wartortle::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Wartortle::setHP(double hp, Pokemon2& poke, bool attack)
{
	double damage((getHP() - hp) / 5);

	Pokemon2::setHP(hp, *this, attack);

	if (damage > 0)
	{
		setColor(1); // ���ܰT��
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�y��" << damage << "�I�����ˮ` <<<<<<<<<<\n\n";
	}

	if (attack && &poke != this)
		poke.setHP(poke.getHP() - damage, *this, 0); // �����ˮ`

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Blastoise::Blastoise(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a3
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Blastoise::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Blastoise::setHP(double hp, Pokemon2& poke, bool attack)
{
	double damage((getHP() - hp) / 5);

	Pokemon2::setHP(hp, *this, attack);

	if (damage > 0)
	{
		setColor(1); // ���ܰT��
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�y��" << damage << "�I�����ˮ` <<<<<<<<<<\n\n";
	}

	if (attack && &poke != this)
		poke.setHP(poke.getHP() - damage, *this, 0); // �����ˮ`

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Caterpie::Caterpie(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a4
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Caterpie::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�غc�l�@�եΤ����O�غc�l
Metapod::Metapod(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a4
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Metapod::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�غc�l�@�եΤ����O�غc�l
Butterfree::Butterfree(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a4
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Butterfree::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�غc�l�@�եΤ����O�غc�l
Weedle::Weedle(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a5
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Weedle::attack(Pokemon2& poke)
{
	setColor(15);

	int damage = rand() % 2 + 2.0;

	cout << endl << "     >>>>>>>>>> "  << this->getName() << "�q" << poke.getName() << "�l���F" << damage << "�I�ͩR <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke) - damage, *this, 1); // �����ˮ`

	setHP(getHP() + (damage), *this, 0); // �l���ͩR

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Kakuna::Kakuna(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a5
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Kakuna::attack(Pokemon2& poke)
{
	setColor(15);

	int damage = rand() % 2 + 2.0;

	cout << endl << "     >>>>>>>>>> "  << this->getName() << "�q" << poke.getName() << "�l���F" << damage << "�I�ͩR <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke) - damage, *this, 1); // �����ˮ`

	setHP(getHP() + (damage), *this, 0); // �l���ͩR

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Beedrill::Beedrill(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a5
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Beedrill::attack(Pokemon2& poke)
{
	setColor(15);

	int damage = rand() % 2 + 2.0;

	cout << endl << "     >>>>>>>>>> "  << this->getName() << "�q" << poke.getName() << "�l���F" << damage << "�I�ͩR <<<<<<<<<<\n\n";

	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke) - damage, *this, 1); // �����ˮ`

	setHP(getHP() + (damage), *this, 0); // �l���ͩR

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Pidgey::Pidgey(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a6
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Pidgey::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Pidgey::setHP(double hp, Pokemon2& poke, bool attack)
{
	if (attack)
	{
		if (rand() % 5)
			Pokemon2::setHP(hp, *this, attack);
		else
		{
			setColor(11); // �j�׶ˮ`
			cout << endl << "     >>>>>>>>>> "  << this->getName() << "�j�פF�o������ <<<<<<<<<<\n\n";
		}
	}
	else
		Pokemon2::setHP(hp, *this, attack);

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Pidgeotto::Pidgeotto(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a6
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Pidgeotto::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Pidgeotto::setHP(double hp, Pokemon2& poke, bool attack)
{
	if (attack)
	{
		if (rand() % 5)
			Pokemon2::setHP(hp, *this, attack);
		else
		{
			setColor(11); // �j�׶ˮ`
			cout << endl << "     >>>>>>>>>> " << this->getName() << "�j�פF�o������ <<<<<<<<<<\n\n";
		}
	}
	else
		Pokemon2::setHP(hp, *this, attack);

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Pidgeot::Pidgeot(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a6
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Pidgeot::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Pidgeot::setHP(double hp, Pokemon2& poke, bool attack)
{
	if (attack)
	{
		if (rand() % 5)
			Pokemon2::setHP(hp, *this, attack);
		else
		{
			setColor(11); // �j�׶ˮ`
			cout << endl << "     >>>>>>>>>> " << this->getName() << "�j�פF�o������ <<<<<<<<<<\n\n";
		}
	}
	else
		Pokemon2::setHP(hp, *this, attack);

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Rattata::Rattata(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a0
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Rattata::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�غc�l�@�եΤ����O�غc�l
Raticate::Raticate(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a0
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Raticate::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�غc�l�@�եΤ����O�غc�l
Spearow::Spearow(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a7
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Spearow::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!(rand() % 5))
	{
		setColor(12); // �A������
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "�o�ʤF��O�A�i��⦸���� <<<<<<<<<<\n\n";
		poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Fearow::Fearow(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a7
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Fearow::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!(rand() % 5))
	{
		setColor(12); // �A������
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "�o�ʤF��O�A�i��⦸���� <<<<<<<<<<\n\n";
		poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Ekans::Ekans(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a8
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Ekans::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʼ@�r
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "��" << poke.getName() << "�o�ʤF�@�r��O <<<<<<<<<<\n\n";
		poke.setCount(0,0,0,2);
		poke.setPoison(1);
		setAbilityIsActivated(1);
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Arbok::Arbok(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a8
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Arbok::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʼ@�r
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "��" << poke.getName() << "�o�ʤF�@�r��O <<<<<<<<<<\n\n";
		poke.setCount(0,0,0,2);
		poke.setPoison(1);
		setAbilityIsActivated(1);
	}

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Pikachu::Pikachu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a9
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Pikachu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(14); // �o�ʴ�t
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF�t�׮z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
			setColor(14);
		}
		else
		{
			poke.setCount(0, 0, 2, 0);
			poke.setLowerSpeed(1);
		}
	}
}

// �l���O�غc�l�@�եΤ����O�غc�l
Raichu::Raichu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a9
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Raichu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{	
		setColor(14); // �o�ʴ�t
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF�t�׮z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
			setColor(14);
		}
		else
		{
			poke.setCount(0, 0, 2, 0);
			poke.setLowerSpeed(1);
		}
	}
}

// �l���O�غc�l�@�եΤ����O�غc�l
Sandshrew::Sandshrew(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a10
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Sandshrew::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Sandshrew::setHP(double hp, Pokemon2& poke, bool attack)
{
	double currentHP = getHP();

	if (hp < getHP() && attack) // �o�ʴ��
	{
		Pokemon2::setHP(hp + 2, *this, 0);
		setColor(7);
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "�o�ʤF��˯�O <<<<<<<<<<\n\n";
	}

	if (getHP() > currentHP)
		setHP(currentHP, *this, 0);

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
Sandslash::Sandslash(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a10
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Sandslash::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`
}

// �l���O�]�w��q
void Sandslash::setHP(double hp, Pokemon2& poke, bool attack)
{
	double currentHP = getHP();

	if (hp < getHP() && attack) // �o�ʴ��
	{
		Pokemon2::setHP(hp + 2, *this, 0);
		setColor(7);
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "�o�ʤF��˯�O <<<<<<<<<<\n\n";
	}

	if (getHP() > currentHP)
		setHP(currentHP, *this, 0);

	setColor(14);
}

// �l���O�غc�l�@�եΤ����O�غc�l
NidoranMesu::NidoranMesu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a11
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void NidoranMesu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʴ
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF���m�z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
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

// �l���O�غc�l�@�եΤ����O�غc�l
Nidorina::Nidorina(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a11
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Nidorina::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʴ
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF���m�z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
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

// �l���O�غc�l�@�եΤ����O�غc�l
Nidoqueen::Nidoqueen(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a11
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Nidoqueen::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʴ
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF���m�z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
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

// �l���O�غc�l�@�եΤ����O�غc�l
NidoranOsu::NidoranOsu(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a12
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void NidoranOsu::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʴ��
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF�����z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
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

// �l���O�غc�l�@�եΤ����O�غc�l
Nidorino::Nidorino(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a12
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Nidorino::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{
		setColor(13); // �o�ʴ��
		cout << endl << "     >>>>>>>>>> " << this->getName() << "��" << poke.getName() << "�o�ʤF�����z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);

		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
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

// �l���O�غc�l�@�եΤ����O�غc�l
Nidoking::Nidoking(int number, const vector< Pokemon2 > list, vector< vector< double > > Rate) // a12
	:Pokemon2(number, list, Rate)
{
}

// �l���O�����禡
void Nidoking::attack(Pokemon2& poke)
{
	poke.setHP(poke.getHP() - (getATK() - poke.getDEF()) * getDamageRate(*this, poke), *this, 1); // �����ˮ`

	if (!getAbilityIsActivated())
	{	
		setColor(13); // �o�ʴ��
		cout << endl << "     >>>>>>>>>> "  << this->getName() << "��" << poke.getName() << "�o�ʤF�����z�Ư�O <<<<<<<<<<\n\n";
		setAbilityIsActivated(1);
		if (poke.getAbility() == 4)
		{
			setColor(6);
			cout << endl << "     >>>>>>>>>> " << poke.getName() << "���|����ƭȮz�ƪ��ĪG <<<<<<<<<<\n\n"; // �����v�T
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