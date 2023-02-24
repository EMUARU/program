// ���a���
#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <vector>
#include"Pokemon2r.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

// ���a
class Player
{
public:
	Player(string, vector< Pokemon2 >, vector< vector< double > > Rate); // �غc�l
	void setName(string playeName); // �]�m���a�W�r �w�]��  ���a
	string getName(); // �^�Ǫ��a�W�r
	Pokemon2* getCurrentPokemon(); // �^�Ƿ�e��ԯ��_�_��
	void showPokemonsGET(); // �i�ܫ������_�_��
	void showPokemons(); // �i�ܫ������_�_��
	void showAlivePokemon(int x, int y); // �i�ܦs�����_�_��
	void showPokemonDetail(int x, int y, vector< vector< string > > graphList); // �i�ܯ��_�_����T
	void FreedPokemon(int x, int y); // �i�����񯫩_�_��
	void catchPokemonGenerally(); // �@��쯫�_�_��
	void catchPokemonGress(); // ��a�쯫�_�_��
	void catchPokemonWater(); // �����쯫�_�_��
	void freedPokemon(int number); // ���񯫩_�_��
	int pokemonListSize(); // �^�ǫ������_�_���ƶq
	Pokemon2* lastPokemonType(); // �^�ǳ̫�@�����_�_���ݩ�
	void choicePokemonBattleList(int number); // �N���_�_����J��ԲM��
	void askAboutBattleOptions(); // ��ܰѥ[��Ԫ����_�_��
	vector< Pokemon2* >& getPokemonBattleList(); // �^�ǹ�ԲM��
	void deadPokemon(); // �R�����`���_�_��
private:
	string name; // ���a�W�r

	 // �C�@�د��_�_�������ۤv�s�񪺪Ŷ�
	vector< Bulbasaur >bulbasaur;
	vector< Ivysaur >ivysaur;
	vector< Venusaur >venusaur;
	vector< Charmander >charmander;
	vector< Charmeleon >charmeleon;
	vector< Charizard >charizard;
	vector< Squirtle >squirtle;
	vector< Wartortle >wartortle;
	vector< Blastoise >blastoise;
	vector< Caterpie >caterpie;
	vector< Metapod >metapod;
	vector< Butterfree >butterfree;
	vector< Weedle >weedle;
	vector< Kakuna >kakuna;
	vector< Beedrill >beedrill;
	vector< Pidgey >pidgey;
	vector< Pidgeotto >pidgeotto;
	vector< Pidgeot >pidgeot;
	vector< Rattata >rattata;
	vector< Raticate >raticate;
	vector< Spearow >spearow;
	vector< Fearow >fearow;
	vector< Ekans >ekans;
	vector< Arbok >arbok;
	vector< Pikachu >pikachu;
	vector< Raichu >raichu;
	vector< Sandshrew >sandshrew;
	vector< Sandslash >sandslash;
	vector< NidoranMesu >nidoranMesu;
	vector< Nidorina >nidorina;
	vector< Nidoqueen >nidoqueen;
	vector< NidoranOsu >nidoranOsu;
	vector< Nidorino >nidorino;
	vector< Nidoking >nidoking;

	vector< Pokemon2* > pokemonBattleList; // ��ԯ��_�_���M��
	vector< Pokemon2* > pokemonList; // �������_�_��
};
#endif // PLAYER