// 玩家資料
#include <iostream>
#include <ctime>
#include "Player.h"
#include <cmath>
using namespace std;

vector< string > ability = {	"No	沒有能力",
								"Heal	每回合回復HP3",
								"Burning	隨機附加不受防禦影響的傷害1~3",
								"Counter Attack	反擊1 / 5所受傷害",
								"Immunology	免疫降低能力值的特殊能力",
								"Leech Life	每次攻擊吸收2~3HP",
								"Avoid	1 / 5機率迴避攻擊",
								"Double Attack	1 / 5機率兩次攻擊",
								"Poison	被攻擊的敵方中毒每回合 - 2HP",
								"Lower Speed	攻擊時降低敵方速度值2",
								"Rock Skin	每次受到的傷害 - 2",
								"Lower Defence	攻擊時降低敵方防禦力2",
								"Lower Attack	攻擊時降低敵方攻擊力2" };

// 輸入整數
int inputAnInteger(int begin, int end)
{
	string a;
	cin >> a; // 輸入整數

	if (a.size() == 1 && a[0] >= begin + 48 && a[0] <= end + 48)
		return a[0] - 48; // 回傳整數
	else if (a.size() == 2 && ((a[0] - 48) * 10 + a[1]) >= begin + 48 && ((a[0] - 48) * 10 + a[1]) <= end + 48)
		return ((a[0] - 48) * 10 + a[1]) - 48; // 回傳整數

	return -1; // 回傳錯誤
}

// 初始化玩家資料
Player::Player(string playerName, const vector< Pokemon2 > list, vector< vector< double > > Rate)
{
	name = playerName;// 設置姓名

	 // 初始化Pokemon
	for (int i(0); i < 34; i++)
	{
		Bulbasaur temp(1, list, Rate);
		bulbasaur.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Ivysaur temp(2, list, Rate);
		ivysaur.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Venusaur temp(3, list, Rate);
		venusaur.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Charmander temp(4, list, Rate);
		charmander.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Charmeleon temp(5, list, Rate);
		charmeleon.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Charizard temp(6, list, Rate);
		charizard.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Squirtle temp(7, list, Rate);
		squirtle.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Wartortle temp(8, list, Rate);
		wartortle.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Blastoise temp(9, list, Rate);
		blastoise.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Caterpie temp(10, list, Rate);
		caterpie.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Metapod temp(11, list, Rate);
		metapod.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Butterfree temp(12, list, Rate);
		butterfree.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Weedle temp(13, list, Rate);
		weedle.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Kakuna temp(14, list, Rate);
		kakuna.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Beedrill temp(15, list, Rate);
		beedrill.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Pidgey temp(16, list, Rate);
		pidgey.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Pidgeotto temp(17, list, Rate);
		pidgeotto.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Pidgeot temp(18, list, Rate);
		pidgeot.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Rattata temp(19, list, Rate);
		rattata.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Raticate temp(20, list, Rate);
		raticate.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Spearow temp(21, list, Rate);
		spearow.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Fearow temp(22, list, Rate);
		fearow.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Ekans temp(23, list, Rate);
		ekans.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Arbok temp(24, list, Rate);
		arbok.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Pikachu temp(25, list, Rate);
		pikachu.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Raichu temp(26, list, Rate);
		raichu.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Sandshrew temp(27, list, Rate);
		sandshrew.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Sandslash temp(28, list, Rate);
		sandslash.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		NidoranMesu temp(29, list, Rate);
		nidoranMesu.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Nidorina temp(30, list, Rate);
		nidorina.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Nidoqueen temp(31, list, Rate);
		nidoqueen.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		NidoranOsu temp(32, list, Rate);
		nidoranOsu.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Nidorino temp(33, list, Rate);
		nidorino.push_back(temp);
	}
	for (int i(0); i < 34; i++)
	{
		Nidoking temp(34, list, Rate);
		nidoking.push_back(temp);
	}
}

// 設置玩家名字
void Player::setName(string playeName)
{
	name = playeName;// 設置玩家名字
}

// 回傳玩家名字
string Player::getName()
{
	return name;// 回傳玩家名字
}

// 回傳當前神奇寶貝
Pokemon2* Player::getCurrentPokemon()
{
	if (pokemonBattleList.size() > 0) //如果還沒全滅 回傳當前神奇寶貝
			return pokemonBattleList[0];
	else // 如果全滅　回傳空指標
		return nullptr;
}

// 展示目前擁有的神奇寶貝
void Player::showPokemonsGET()
{
	for (int i(0); i < pokemonList.size() - 1; i++) // 不展示最後一隻神奇寶貝
	{
		cout << "pokemon" << i + 1 << " : ";
		pokemonList[i]->showStats();
		cout << endl;
		cout << "                                     ";
	}
}

// 展示目前擁有的神奇寶貝
void Player::showPokemons()
{
	for (int i(0); i < pokemonList.size(); i++) // 展示最後一隻神奇寶貝
	{
		cout << "pokemon" << i + 1 << " : ";
		pokemonList[i]->showStats();
		cout << endl;
		cout << "                                     ";
	}
}

// 展示存活的神奇寶貝
void Player::showAlivePokemon(int x, int y)
{
	for (int i(0); i < pokemonBattleList.size(); i++)
	{
		locate(x, (y += 2)); // 調整輸出位置
		cout << "pokemon" << i + 1 << " : ";
		pokemonBattleList[i]->showStats();// 展示存活的神奇寶貝
	}
}

// 展示神奇寶貝資訊
void Player::showPokemonDetail(int x, int y, vector< vector< string > > graphList)
{
	locate(146, 5);
	std::cout << "                                ";

	int number(-1);

	for (int i(0); i < pokemonList.size(); i++)
	{
		setColor(pokemonList[i]->getID() % 15 + 1);
		locate(x, (y += 2)); // 調整輸出位置
		cout << "pokemon" << i + 1 << " : ";
		pokemonList[i]->showStats();// 展示神奇寶貝
	}

	while (number < 1 || number > pokemonListSize()) // 選擇神奇寶貝
	{
		locate(x, (y + 4)); // 調整輸出位置
		std::cout << "                                                                                          ";
		setColor(12);
		locate(x, (y + 4)); // 調整輸出位置
		cout << "請輸入想查看的神奇寶貝編號(取消請輸入0): ";

		std::fflush(stdout);
		rlutil::setCursorVisibility(0);
		number = inputAnInteger(0, pokemonListSize());

		if (number == 0)
		{
			locate(x, (y + 6)); // 調整輸出位置
			cout << "已取消查看";
			locate(x, (y + 8));
			std::system("pause");
			break;
		}
		else if (number < 1 || number > pokemonListSize())
			continue;
		else
		{
			x = 146; 
			y = 5;
			for (int i(0); i < 30; i++) // 輸出玩家神奇寶貝圖像
			{
				locate(x, (y++));
				std::cout << graphList[(pokemonList[number - 1]->getID() - 1)][i];
			}
			setColor(pokemonList[number - 1]->getID() % 15 + 1);
			locate(x, (y += 2));
			std::cout << "神奇寶貝之種類 : " << pokemonList[number - 1]->getName(); // 輸出玩家神奇寶貝種類

			locate(x, (y += 2));
			std::cout << "神奇寶貝之屬性 : " << pokemonList[number - 1]->getType(); // 輸出玩家神奇寶貝屬性

			locate(x, (y += 2));
			std::cout << "神奇寶貝之攻擊力 : " << pokemonList[number - 1]->getInitialATK(); // 輸出玩家神奇寶貝攻擊

			locate(x, (y += 2));
			std::cout << "神奇寶貝之防禦力 : " << pokemonList[number - 1]->getInitialDEF(); // 輸出玩家神奇寶貝防禦

			locate(x, (y += 2));
			std::cout << "神奇寶貝之速度 : " << pokemonList[number - 1]->getInitialSpeed(); // 輸出玩家神奇寶貝速度

			locate(x, (y += 2));
			std::cout << "神奇寶貝之技能 : "; // 輸出玩家神奇寶貝技能
			locate(x, (y += 2));
			std::cout << ability[pokemonList[number - 1]->getAbility()];

			setColor(12);
			locate(x, (y += 2));
			std::system("pause");
			break;
		}
	}
}

// 展示釋放的神奇寶貝
void Player::FreedPokemon(int x, int y)
{
	locate(100, 5);
	std::cout << "                                ";

	int choice(-1);

	for (int i(0); i < pokemonList.size(); i++)
	{
		setColor(16 - (pokemonList[i]->getID() % 15 + 1));
		locate(x, (y += 2)); // 調整輸出位置
		cout << "pokemon" << i + 1 << " : ";
		pokemonList[i]->showStats();// 展示釋放的神奇寶貝
	}
	

	while (choice < 1 || choice > pokemonListSize()) // 選擇釋放的神奇寶貝
	{
		locate(x, (y + 4));
		std::cout << "                                            ";
		setColor(6);
		locate(x, (y + 4)); // 調整輸出位置
		cout << "請輸入想釋放的神奇寶貝編號(取消請輸入0): ";

		std::fflush(stdout);
		rlutil::setCursorVisibility(0);
		choice = inputAnInteger(0, pokemonListSize());

		if (choice == 0)
		{
			locate(x, (y + 6)); // 調整輸出位置
			cout << "已取消釋放";
			locate(x, (y + 8));
			std::system("pause");
			break;
		}
		else if (choice < 1 || choice > pokemonListSize())
			continue;
		else
		{
			freedPokemon(choice);
			locate(x, (y + 6)); // 調整輸出位置
			cout << "已釋放指定神奇寶貝";
			locate(x, (y + 8));
			std::system("pause");
			break;
		}
	}
}

// 一般抓神奇寶貝
void Player::catchPokemonGenerally()
{
	static int times(0);

	srand(time(0));

	int rd = abs((rand() * (++times)) % 32 /*34*/); // 每一種機率平等
	
	switch (rd)
	{
	case 0:
		pokemonList.push_back(&bulbasaur[pokemonList.size()]);
		break;
	case 1:
		pokemonList.push_back(&ivysaur[pokemonList.size()]);
		break;
	case 2:
		pokemonList.push_back(&venusaur[pokemonList.size()]);
		break;
	case 3:
		pokemonList.push_back(&charmander[pokemonList.size()]);
		break;
	case 4:
		pokemonList.push_back(&charmeleon[pokemonList.size()]);
		break;
	case 5:
		pokemonList.push_back(&charizard[pokemonList.size()]);
		break;
	case 6:
		pokemonList.push_back(&squirtle[pokemonList.size()]);
		break;
	case 7:
		pokemonList.push_back(&wartortle[pokemonList.size()]);
		break;
	case 8:
		pokemonList.push_back(&blastoise[pokemonList.size()]);
		break;
	case 9:
		pokemonList.push_back(&caterpie[pokemonList.size()]);
		break;
	case 10:
		pokemonList.push_back(&metapod[pokemonList.size()]);
		break;
	case 11:
		pokemonList.push_back(&butterfree[pokemonList.size()]);
		break;
	case 12:
		pokemonList.push_back(&weedle[pokemonList.size()]);
		break;
	case 13:
		pokemonList.push_back(&kakuna[pokemonList.size()]);
		break;
	case 14:
		pokemonList.push_back(&beedrill[pokemonList.size()]);
		break;
	case 15:
		pokemonList.push_back(&pidgey[pokemonList.size()]);
		break;
	case 16:
		pokemonList.push_back(&pidgeotto[pokemonList.size()]);
		break;
	case 17:
		pokemonList.push_back(&pidgeot[pokemonList.size()]);
		break;
	case 18:
		pokemonList.push_back(&rattata[pokemonList.size()]);
		break;
	case 19:
		pokemonList.push_back(&raticate[pokemonList.size()]);
		break;
	case 20:
		pokemonList.push_back(&spearow[pokemonList.size()]);
		break;
	case 21:
		pokemonList.push_back(&fearow[pokemonList.size()]);
		break;
	case 22:
		pokemonList.push_back(&ekans[pokemonList.size()]);
		break;
	case 23:
		pokemonList.push_back(&arbok[pokemonList.size()]);
		break;
	case 24:
		pokemonList.push_back(&pikachu[pokemonList.size()]);
		break;
	case 25:
		pokemonList.push_back(&raichu[pokemonList.size()]);
		break;
	case 26:
		pokemonList.push_back(&sandshrew[pokemonList.size()]);
		break;
	case 27:
		pokemonList.push_back(&sandslash[pokemonList.size()]);
		break;
	case 28:
		pokemonList.push_back(&nidoranMesu[pokemonList.size()]);
		break;
	case 29:
		pokemonList.push_back(&nidorina[pokemonList.size()]);
		break;
	case 30:
		pokemonList.push_back(&nidoqueen[pokemonList.size()]);
		break;
	case 31:
		pokemonList.push_back(&nidoranOsu[pokemonList.size()]);
		break;
	case 32:
		pokemonList.push_back(&nidorino[pokemonList.size()]);
		break;
	case 33:
		pokemonList.push_back(&nidoking[pokemonList.size()]);
		break;
	}
}

// 草地抓神奇寶貝
void Player::catchPokemonGress()
{
	static int times(0);
	srand(time(0));
	int rd = abs((rand() * (++times)) % 4972 /*5270*/) + 1;// 草系機率提高40%

	// gress 的機率為原本的 3/34 變成 3/34 * 14/10 = (217*3)/(217*3 + 149*31) = 651/5270
	if(rd > 0 && rd <= 217)
		pokemonList.push_back(&bulbasaur[pokemonList.size()]);
	else if (rd > 217 && rd <= 434)
		pokemonList.push_back(&ivysaur[pokemonList.size()]);
	else if (rd > 434 && rd <= 651)
		pokemonList.push_back(&venusaur[pokemonList.size()]);
	else if (rd > 651 && rd <= 800)
		pokemonList.push_back(&charmander[pokemonList.size()]);
	else if (rd > 800 && rd <= 949)
		pokemonList.push_back(&charmeleon[pokemonList.size()]);
	else if (rd > 949 && rd <= 1098)
		pokemonList.push_back(&charizard[pokemonList.size()]);
	else if (rd > 1098 && rd <= 1247)
		pokemonList.push_back(&squirtle[pokemonList.size()]);
	else if (rd > 1247 && rd <= 1396)
		pokemonList.push_back(&wartortle[pokemonList.size()]);
	else if (rd > 1396 && rd <= 1545)
		pokemonList.push_back(&blastoise[pokemonList.size()]);
	else if (rd > 1545 && rd <= 1694)
		pokemonList.push_back(&caterpie[pokemonList.size()]);
	else if (rd > 1694 && rd <= 1843)
		pokemonList.push_back(&metapod[pokemonList.size()]);
	else if (rd > 1843 && rd <= 1992)
		pokemonList.push_back(&butterfree[pokemonList.size()]);
	else if (rd > 1992 && rd <= 2141)
		pokemonList.push_back(&weedle[pokemonList.size()]);
	else if (rd > 2141 && rd <= 2290)
		pokemonList.push_back(&kakuna[pokemonList.size()]);
	else if (rd > 2290 && rd <= 2439)
		pokemonList.push_back(&beedrill[pokemonList.size()]);
	else if (rd > 2439 && rd <= 2588)
		pokemonList.push_back(&pidgey[pokemonList.size()]);
	else if (rd > 2588 && rd <= 2737)
		pokemonList.push_back(&pidgeotto[pokemonList.size()]);
	else if (rd > 2737 && rd <= 2886)
		pokemonList.push_back(&pidgeot[pokemonList.size()]);
	else if (rd > 2886 && rd <= 3035)
		pokemonList.push_back(&rattata[pokemonList.size()]);
	else if (rd > 3035 && rd <= 3184)
		pokemonList.push_back(&raticate[pokemonList.size()]);
	else if (rd > 3184 && rd <= 3333)
		pokemonList.push_back(&spearow[pokemonList.size()]);
	else if (rd > 3333 && rd <= 3482)
		pokemonList.push_back(&fearow[pokemonList.size()]);
	else if (rd > 3482 && rd <= 3631)
		pokemonList.push_back(&ekans[pokemonList.size()]);
	else if (rd > 3631 && rd <= 3780)
		pokemonList.push_back(&arbok[pokemonList.size()]);
	else if (rd > 3780 && rd <= 3929)
		pokemonList.push_back(&pikachu[pokemonList.size()]);
	else if (rd > 3929 && rd <= 4078)
		pokemonList.push_back(&raichu[pokemonList.size()]);
	else if (rd > 4078 && rd <= 4227)
		pokemonList.push_back(&sandshrew[pokemonList.size()]);
	else if (rd > 4227 && rd <= 4376)
		pokemonList.push_back(&sandslash[pokemonList.size()]);
	else if (rd > 4376 && rd <= 4525)
		pokemonList.push_back(&nidoranMesu[pokemonList.size()]);
	else if (rd > 4525 && rd <= 4674)
		pokemonList.push_back(&nidorina[pokemonList.size()]);
	else if (rd > 4674 && rd <= 4823)
		pokemonList.push_back(&nidoqueen[pokemonList.size()]);
	else if (rd > 4823 && rd <= 4972)
		pokemonList.push_back(&nidoranOsu[pokemonList.size()]);
	else if (rd > 4972 && rd <= 5121)
		pokemonList.push_back(&nidorino[pokemonList.size()]);
	else if (rd > 5121 && rd <= 5270)
		pokemonList.push_back(&nidoking[pokemonList.size()]);
}

// 水池抓神奇寶貝
void Player::catchPokemonWater()
{
	static int times(0);
	srand(time(0));
	int rd = abs((rand() * (++times)) % 4972 /*5270*/) + 1;// 水系機率提高40%

	// water 的機率為原本的 3/34 變成 3/34 * 14/10 = (217*3)/(217*3 + 149*31) = 651/5270
	if (rd > 0 && rd <= 217)
		pokemonList.push_back(&squirtle[pokemonList.size()]);
	else if (rd > 217 && rd <= 434)
		pokemonList.push_back(&wartortle[pokemonList.size()]);
	else if (rd > 434 && rd <= 651)
		pokemonList.push_back(&blastoise[pokemonList.size()]);
	else if (rd > 651 && rd <= 800)
		pokemonList.push_back(&charmander[pokemonList.size()]);
	else if (rd > 800 && rd <= 949)
		pokemonList.push_back(&charmeleon[pokemonList.size()]);
	else if (rd > 949 && rd <= 1098)
		pokemonList.push_back(&charizard[pokemonList.size()]);
	else if (rd > 1098 && rd <= 1247)
		pokemonList.push_back(&bulbasaur[pokemonList.size()]);
	else if (rd > 1247 && rd <= 1396)
		pokemonList.push_back(&ivysaur[pokemonList.size()]);
	else if (rd > 1396 && rd <= 1545)
		pokemonList.push_back(&venusaur[pokemonList.size()]);
	else if (rd > 1545 && rd <= 1694)
		pokemonList.push_back(&caterpie[pokemonList.size()]);
	else if (rd > 1694 && rd <= 1843)
		pokemonList.push_back(&metapod[pokemonList.size()]);
	else if (rd > 1843 && rd <= 1992)
		pokemonList.push_back(&butterfree[pokemonList.size()]);
	else if (rd > 1992 && rd <= 2141)
		pokemonList.push_back(&weedle[pokemonList.size()]);
	else if (rd > 2141 && rd <= 2290)
		pokemonList.push_back(&kakuna[pokemonList.size()]);
	else if (rd > 2290 && rd <= 2439)
		pokemonList.push_back(&beedrill[pokemonList.size()]);
	else if (rd > 2439 && rd <= 2588)
		pokemonList.push_back(&pidgey[pokemonList.size()]);
	else if (rd > 2588 && rd <= 2737)
		pokemonList.push_back(&pidgeotto[pokemonList.size()]);
	else if (rd > 2737 && rd <= 2886)
		pokemonList.push_back(&pidgeot[pokemonList.size()]);
	else if (rd > 2886 && rd <= 3035)
		pokemonList.push_back(&rattata[pokemonList.size()]);
	else if (rd > 3035 && rd <= 3184)
		pokemonList.push_back(&raticate[pokemonList.size()]);
	else if (rd > 3184 && rd <= 3333)
		pokemonList.push_back(&spearow[pokemonList.size()]);
	else if (rd > 3333 && rd <= 3482)
		pokemonList.push_back(&fearow[pokemonList.size()]);
	else if (rd > 3482 && rd <= 3631)
		pokemonList.push_back(&ekans[pokemonList.size()]);
	else if (rd > 3631 && rd <= 3780)
		pokemonList.push_back(&arbok[pokemonList.size()]);
	else if (rd > 3780 && rd <= 3929)
		pokemonList.push_back(&pikachu[pokemonList.size()]);
	else if (rd > 3929 && rd <= 4078)
		pokemonList.push_back(&raichu[pokemonList.size()]);
	else if (rd > 4078 && rd <= 4227)
		pokemonList.push_back(&sandshrew[pokemonList.size()]);
	else if (rd > 4227 && rd <= 4376)
		pokemonList.push_back(&sandslash[pokemonList.size()]);
	else if (rd > 4376 && rd <= 4525)
		pokemonList.push_back(&nidoranMesu[pokemonList.size()]);
	else if (rd > 4525 && rd <= 4674)
		pokemonList.push_back(&nidorina[pokemonList.size()]);
	else if (rd > 4674 && rd <= 4823)
		pokemonList.push_back(&nidoqueen[pokemonList.size()]);
	else if (rd > 4823 && rd <= 4972)
		pokemonList.push_back(&nidoranOsu[pokemonList.size()]);
	else if (rd > 4972 && rd <= 5121)
		pokemonList.push_back(&nidorino[pokemonList.size()]);
	else if (rd > 5121 && rd <= 5270)
		pokemonList.push_back(&nidoking[pokemonList.size()]);
}

// 釋放神奇寶貝
void Player::freedPokemon(int number)
{
	if(number >= 1 && number <= pokemonList.size())
		pokemonList.erase(pokemonList.begin() + number - 1); // 移除指定神奇寶貝
}

// 回傳持有神奇寶貝數量
int Player::pokemonListSize()
{
	return pokemonList.size(); // 回傳持有神奇寶貝數量
}

// 回傳最後一隻神奇寶貝屬性
Pokemon2* Player::lastPokemonType()
{
	return pokemonList[pokemonList.size() - 1]; // 回傳最後一隻神奇寶貝屬性
}

// 將神奇寶貝放入對戰清單
void Player::choicePokemonBattleList(int number)
{
	if(number >= 0 && number < pokemonList.size())
		pokemonBattleList.push_back(pokemonList[number]); // 將神奇寶貝放入對戰清單
}

// 選擇要放入對戰清單的神奇寶貝
void Player::askAboutBattleOptions()
{
	pokemonBattleList.clear(); // 清空對戰清單

	int number1(100), number2(100), number3(100);

	if (pokemonListSize() >= 3)
	{
		system("cls");
		locate(10, 2);
		std::cout << "目前持有Pokemon :           "; // 展示玩家持有的神奇寶貝
		showPokemons();
		std::cout << "\n\n          請選擇要參加戰鬥的三隻pokemon(依選擇順序出場 不可重複)";

		while (number1 < 1 || number1 > pokemonListSize()) // 選擇第一隻出場的神奇寶貝
		{
			locate(11, 12 + (pokemonListSize() - 3) * 2 + 1);
			std::cout << "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       ";
			locate(11, 12 + (pokemonListSize() - 3) * 2);
			std::cout << "\n          請輸入第一隻出場的pokemon編號 : ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			number1 = inputAnInteger(1, pokemonListSize());
		}

		while (number2 < 1 || number2 > pokemonListSize() || number2 == number1) // 選擇第二隻出場的神奇寶貝
		{
			locate(11, 14 + (pokemonListSize() - 3) * 2 + 1);
			std::cout << "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       ";
			locate(11, 14 + (pokemonListSize() - 3) * 2);
			std::cout << "\n          請輸入第二隻出場的pokemon編號 : ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			number2 = inputAnInteger(1, pokemonListSize());
		}

		while (number3 < 1 || number3 > pokemonListSize() || number3 == number1 || number3 == number2) // 選擇第三隻出場的神奇寶貝
		{
			locate(11, 16 + (pokemonListSize() - 3) * 2 + 1);
			std::cout << "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       ";
			locate(11, 16 + (pokemonListSize() - 3) * 2);
			std::cout << "\n          請輸入第三隻出場的pokemon編號 : ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			number3 = inputAnInteger(1, pokemonListSize());
		}

		// 將神奇寶貝依序放入對戰清單
		pokemonBattleList.push_back(pokemonList[number1-1]);
		pokemonBattleList.push_back(pokemonList[number2-1]);
		pokemonBattleList.push_back(pokemonList[number3-1]);
	}
}

// 回傳對戰清單
vector< Pokemon2* >& Player::getPokemonBattleList()
{
	return pokemonBattleList; // 回傳對戰清單
}

// 刪除死亡神奇寶貝
void Player::deadPokemon()
{
	if (pokemonBattleList.size() > 0 )
		if(pokemonBattleList[0]->getHP() <= 0) // 如果血量小於等於零
		{
			pokemonBattleList[0]->reset(); // 將那隻神奇寶貝回復初始狀態
			pokemonBattleList.erase(pokemonBattleList.begin()); // 並且移出對戰清單
		}
}