// 玩家資料
#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <vector>
#include"Pokemon2r.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

// 玩家
class Player
{
public:
	Player(string, vector< Pokemon2 >, vector< vector< double > > Rate); // 建構子
	void setName(string playeName); // 設置玩家名字 預設為  玩家
	string getName(); // 回傳玩家名字
	Pokemon2* getCurrentPokemon(); // 回傳當前對戰神奇寶貝
	void showPokemonsGET(); // 展示持有神奇寶貝
	void showPokemons(); // 展示持有神奇寶貝
	void showAlivePokemon(int x, int y); // 展示存活神奇寶貝
	void showPokemonDetail(int x, int y, vector< vector< string > > graphList); // 展示神奇寶貝資訊
	void FreedPokemon(int x, int y); // 展示釋放神奇寶貝
	void catchPokemonGenerally(); // 一般抓神奇寶貝
	void catchPokemonGress(); // 草地抓神奇寶貝
	void catchPokemonWater(); // 水池抓神奇寶貝
	void freedPokemon(int number); // 釋放神奇寶貝
	int pokemonListSize(); // 回傳持有神奇寶貝數量
	Pokemon2* lastPokemonType(); // 回傳最後一隻神奇寶貝屬性
	void choicePokemonBattleList(int number); // 將神奇寶貝放入對戰清單
	void askAboutBattleOptions(); // 選擇參加對戰的神奇寶貝
	vector< Pokemon2* >& getPokemonBattleList(); // 回傳對戰清單
	void deadPokemon(); // 刪除死亡神奇寶貝
private:
	string name; // 玩家名字

	 // 每一種神奇寶貝都有自己存放的空間
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

	vector< Pokemon2* > pokemonBattleList; // 對戰神奇寶貝清單
	vector< Pokemon2* > pokemonList; // 持有神奇寶貝
};
#endif // PLAYER