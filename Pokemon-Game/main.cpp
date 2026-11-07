// 主程式
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include "rlutil.h"
#include "Pokemon2r.h"
#include "Player.h"
#include "Battle.h"

using namespace rlutil;
using namespace std;

#define NOMOVE (realMap[y - 1][x - 1] == '*'|| realMap[y - 1][x - 1] == '!'|| (realMap[y - 1][x - 1] > 48 && realMap[y - 1][x - 1] <= 57) || (realMap[y - 1][x - 1] >= 65 && realMap[y - 1][x - 1] <= 68))
#define REALKEY (k == 'a' || k == 'A'|| k == 'd' || k == 'D'|| k == 'w' || k == 'W' || k == 's' || k == 'S' || k == 'r'|| k == 'R'|| k == 't'|| k == 'T')
#define MAP (map[oldy - 1][oldx - 1])

vector< Pokemon2 > list; // 神奇寶貝清單
vector< vector< string > > graphList; // 神奇寶貝圖
vector< vector< double > > damageRate; // 屬性傷害倍率

// 讀入地圖
void readMap(string map[50], char realMap[][100])
{
	ifstream in("yzumap.txt", ifstream::in);

	for (int i(0); i < 31; i++) // 讀入假地圖
		getline(in, map[i]);

	for (int i(0); i < 31; i++) // 讀入真地圖
		for (int j(0); j < 91; j++)
			realMap[i][j] = map[i][j];
}

// 讀入所有Pokemon的圖
void readGraph()
{
	ifstream graphIn[35] = {}; // 開檔
	 graphIn[1].open("001.txt", ifstream::in);
	 graphIn[2].open("002.txt", ifstream::in);
	 graphIn[3].open("003.txt", ifstream::in);
	 graphIn[4].open("004.txt", ifstream::in);
	 graphIn[5].open("005.txt", ifstream::in);
	 graphIn[6].open("006.txt", ifstream::in);
	 graphIn[7].open("007.txt", ifstream::in);
	 graphIn[8].open("008.txt", ifstream::in);
	 graphIn[9].open("009.txt", ifstream::in);
	 graphIn[10].open("010.txt", ifstream::in);
	 graphIn[11].open("011.txt", ifstream::in);
	 graphIn[12].open("012.txt", ifstream::in);
	 graphIn[13].open("013.txt", ifstream::in);
	 graphIn[14].open("014.txt", ifstream::in);
	 graphIn[15].open("015.txt", ifstream::in);
	 graphIn[16].open("016.txt", ifstream::in);
	 graphIn[17].open("017.txt", ifstream::in);
	 graphIn[18].open("018.txt", ifstream::in);
	 graphIn[19].open("019.txt", ifstream::in);
	 graphIn[20].open("020.txt", ifstream::in);
	 graphIn[21].open("021.txt", ifstream::in);
	 graphIn[22].open("022.txt", ifstream::in);
	 graphIn[23].open("023.txt", ifstream::in);
	 graphIn[24].open("024.txt", ifstream::in);
	 graphIn[25].open("025.txt", ifstream::in);
	 graphIn[26].open("026.txt", ifstream::in);
	 graphIn[27].open("027.txt", ifstream::in);
	 graphIn[28].open("028.txt", ifstream::in);
	 graphIn[29].open("029.txt", ifstream::in);
	 graphIn[30].open("030.txt", ifstream::in);
	 graphIn[31].open("031.txt", ifstream::in);
	 graphIn[32].open("032.txt", ifstream::in);
	 graphIn[33].open("032.txt", ifstream::in);
	 graphIn[34].open("032.txt", ifstream::in);

	for (int num(1); num < 35; num++)
	{
		vector< string > graph(30);

		for (int i(0); i < 30; i++) // 讀入一張神奇寶貝圖
			getline(graphIn[num], graph[i]);

		graphList.push_back(graph); // 存入一張神奇寶貝圖
	}
}

// 讀入所有Pokemon的數據
void readPokemonList()
{
	ifstream in("pokemons.csv", ifstream::in);

	stringstream STRING1, STRING2;

	string str;

	Pokemon2 temp;

	int itemp;
	double dtemp;
	string stemp;
	
	// 將資料一行行讀入
	while (getline(in, str, '\n'))
	{
		STRING1.str("");
		STRING1.clear();
		STRING1 << str;

		int n = 0;
		// 將資料用逗號分開讀入
		while (getline(STRING1, str, ','))
		{
			STRING2.str("");
			STRING2.clear();
			STRING2 << str;

			// 將資料轉成正確的資料型態
			if (n == 0)
			{
				STRING2 >> itemp;
				temp.setID(itemp);// 設置ID
				n++;
			}
			else if (n == 1)
			{
				STRING2 >> stemp;
				temp.setName(stemp);// 設置名字
				n++;
			}
			else if (n == 2)
			{
				STRING2 >> stemp;
				temp.setType(stemp);// 設置屬性
				n++;
			}
			else if (n == 3)
			{
				STRING2 >> dtemp;
				temp.setMaxHP(dtemp);// 設置HP
				n++;
			}
			else if (n == 4)
			{
				STRING2 >> dtemp;
				temp.setInitialATK(dtemp);// 設置ATK
				n++;
			}
			else if (n == 5)
			{
				STRING2 >> dtemp;
				temp.setInitialDEF(dtemp);// 設置DEF
				n++;
			}
			else if (n == 6)
			{
				STRING2 >> itemp;
				temp.setInitialSpeed(itemp);// 設置Speed
				n++;
			}
			else if (n == 7)
			{
				STRING2 >> itemp;
				temp.setAbility(itemp);// 設置技能
				n++;
			}
		}
		list.push_back(temp);// 存入清單
	}
}

// 讀入屬性傷害倍率
void readDamageRate()
{
	ifstream in("type.csv", ifstream::in);

	stringstream STRING1, STRING2;

	string str;

	double dtemp;

	// 將資料一行行讀入
	while (getline(in, str, '\n'))
	{
		vector< double > temp;

		STRING1.str("");
		STRING1.clear();
		STRING1 << str;

		// 將資料用逗號分開讀入
		while (getline(STRING1, str, ','))
		{
			STRING2.str("");
			STRING2.clear();
			STRING2 << str;
			STRING2 >> dtemp;
			temp.push_back(dtemp); // 存入倍率
		}
		damageRate.push_back(temp); // 存入列表
	}
}

// 畫圖
void draw(char map[][100], int& x, int& y, Player& player, int& win)
{
	std::system("cls"); // 清螢幕

	for (int i(0); i < 31; i++) // 用不同顏色輸出不同符號
	{
		for (int j(0); j < 91; j++)
		{
			if (map[i][j] == '*')
				rlutil::setColor(11);
			else if (map[i][j] == ';')
				rlutil::setColor(10);
			else if (map[i][j] == '!')
				rlutil::setColor(6);
			else if (map[i][j] > 48 && map[i][j] <= 57)
				rlutil::setColor(7);
			else if (map[i][j] >= 65 && map[i][j] <= 68)
				rlutil::setColor(7);
			else if (map[i][j] == '~')
				rlutil::setColor(9);
			else if (map[i][j] == '#')
				rlutil::setColor(14);

			std::cout << map[i][j];
		}
		std::cout<< endl;
	}

	rlutil::locate(10, 36);
	rlutil::setColor(14);
	std::cout << "目前Pokemon持有數量 : " << player.pokemonListSize();

	rlutil::locate(45, 36);
	std::cout << "目前獲勝場數 : " << win; // 展示獲勝場數

	rlutil::locate(10, 38);
	std::cout << "Pokemon持有上限為34隻，持有數量達到34隻時將不會在路上遇到Pokemon";

	if (player.pokemonListSize() > 0)
	{
		rlutil::locate(10, 40);
		std::cout << "目前持有Pokemon :           ";
		player.showPokemons(); // 展示玩家持有Pokemon

		rlutil::locate(100, 3);
		rlutil::setColor(15);
		std::cout << ":+: 輸 入 選 項 之 文 字 請 勿 跨 行 ， 感 謝 您 的 配 合 。 :+:";
		
		rlutil::locate(100, 5);
		rlutil::setColor(12);
		std::cout << "若想查看神奇寶貝資訊，請按按鍵 t";

		rlutil::locate(146, 5);
		rlutil::setColor(6);
		std::cout << "若想釋放神奇寶貝，請按按鍵 r";
	}

	rlutil::locate(x, y);
	rlutil::setColor(12);
	std::cout << "@"; // 輸出玩家位置

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);
}

// 修改玩家位置
void drawAgain(char map[][100], int oldx, int oldy, int& x, int& y, Player& player)
{
	if (MAP == '*') // 復原玩家原本位置的輸出字元
		rlutil::setColor(11);
	else if (MAP == ';')
		rlutil::setColor(10);
	else if (MAP == '!')
		rlutil::setColor(6);
	else if (MAP > 48 && MAP <= 57)
		rlutil::setColor(7);
	else if (MAP >= 65 && MAP <= 68)
		rlutil::setColor(7);
	else if (MAP == '~')
		rlutil::setColor(9);
	else if (MAP == '#')
		rlutil::setColor(14);

	rlutil::locate(oldx, oldy);
	std::cout << MAP;

	rlutil::locate(x, y);
	rlutil::setColor(12);
	std::cout << "@"; // 在新位置輸出玩家

	rlutil::locate(10, 34);
	std::cout << "                                                       "; // 覆蓋提示訊息

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);
}

// 捕抓神奇寶貝
void catchPokemon(char realMap[][100], int &x, int &y, Player &player,int &win)
{
	srand(time(0)); // 隨機

	std::system("cls"); // 清空螢幕
	
	if (realMap[y - 1][x - 1] == ';') // 依不同地點調整捕抓倍率並且先捕抓
		player.catchPokemonGress();
	else if (realMap[y - 1][x - 1] == '~')
		player.catchPokemonWater();
	else
		player.catchPokemonGenerally();

	for (int i(0); i < 30; i++) // 輸出待捕抓神奇寶貝長相
		std::cout << graphList[(double)player.lastPokemonType()->getID() - 1][i] << endl;

	rlutil::locate(50, 10); // 輸出待捕抓神奇寶貝資訊
	rlutil::setColor(11);
	std::cout << "出現Pokemon種類 : " << player.lastPokemonType()->getName() << endl << endl;
	
	rlutil::locate(50, 17);
	std::cout << "出現Pokemon屬性 : " << player.lastPokemonType()->getType() << endl << endl;

	rlutil::locate(1, 29);

	if(player.pokemonListSize() == 1) // 輸出玩家持有的神奇寶貝
		std::cout << "    玩家目前沒有Pokemon              ";
	else
	{
		std::cout << "    目前持有Pokemon :                ";
		player.showPokemonsGET();
	}

	std::cout << "請選擇是否捕抓      \"是\"請按:y　　　\"否\"請按:n          \n";
	while(1) // 選擇是否捕抓　---  事實上是先捕抓再決定要不要釋放
		if (kbhit())
		{
			char k = getkey();
			if (k == 'y' || k == 'Y' || k == 'n' || k == 'N')
			{
				if (k == 'y' || k == 'Y') // 捕抓
				{
					if (rand() % 2) // 捕抓成功
					{
						std::cout << "\n                                     已捕抓該Pokemon\n";
						if (player.pokemonListSize() > 3)
						{
							std::cout << "\n                                     持有Pokemon已超過3隻，可選擇是否釋放剛才捕抓的Pokemon\n";
							std::cout << "\n                                     請選擇是否釋放    \"保留\"請按:y　　　\"釋放\"請按:n          \n";

							while (1) // 選擇是否保留
								if (kbhit())
								{
									char k = getkey();
									if (k == 'y' || k == 'Y' || k == 'n' || k == 'N')
									{
										if (k == 'n' || k == 'N') // 釋放
										{
											player.freedPokemon(player.pokemonListSize());
											std::cout << "\n                                     已釋放該Pokemon";
										}
										else if (k == 'y' || k == 'Y') // 保留
											std::cout << "\n                                     已保留該Pokemon";

										break;
									}
								}
						}
					}
					else
					{
						player.freedPokemon(player.pokemonListSize()); // 捕抓失敗
						std::cout << "\n                                     該Pokemon捕抓失敗";
					}

				}
				else if (k == 'n' || k == 'N') // 放棄捕抓
				{
					player.freedPokemon(player.pokemonListSize());
					std::cout << "\n                                     放棄捕抓該Pokemon";
				}

				break;
			}
		}

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);

	std::cout << "\n\n                                     ";
	std::system("pause");

	draw(realMap, x, y, player, win); // 回到地圖
}

// 回傳要進行戰鬥的NPC
Player& currentNPC(int x, int y, vector< Player >& NPCList)
{
	int number(0);

	// 依據玩家現在位置決定回傳哪一個NPC
	if (x == 14 && y == 18)
		number = 0;
	else if (x == 35 && y == 7)
		number = 1;
	else if (x == 31 && y == 15)
		number = 2;
	else if (x == 18 && y == 7)
		number = 3;
	else if (x == 10 && y == 11)
		number = 4;
	else if (x == 41 && y == 14)
		number = 5;
	else if (x == 76 && y == 9)
		number = 6;
	else if (x == 77 && y == 12)
		number = 7;
	else if (x == 75 && y == 4)
		number = 8;
	else if (x == 84 && y == 7)
		number = 9;
	else if (x == 76 && y == 7)
		number = 10;
	else if (x == 86 && y == 10)
		number = 11;

	return NPCList[number];
}

// 戰鬥
void battle(char realMap[][100], int x, int y, Player &player, vector< Player >& NPCList, int& win)
{
	rlutil::setColor(10);

	player.askAboutBattleOptions(); // 選擇參戰神奇寶貝

	std::system("cls"); // 清空螢幕

	Battle battle(player, currentNPC(x, y, NPCList), damageRate); // 生成戰鬥

	if (battle.fighting(graphList)) // 進行戰鬥
		win++;

	if(win < 7) // 判斷是否結束遊戲
		draw(realMap, x, y, player, win); // 若未結束遊戲，回到地圖
}

// 移動
void moveMap(char realMap[][100], int& x, int& y, Player& player, vector< Player >& NPCList, int& win)
{
	while (1)
	{
		if (kbhit())
		{
			char k = getkey();
			if (REALKEY)
			{
				if (k == 't' || k == 'T')
				{
					player.showPokemonDetail(100, 7, graphList); // 展示神奇寶貝
					draw(realMap, x, y, player, win);
				}
				else if (k == 'r' || k == 'R')
				{
					player.FreedPokemon(146, 7); // 釋放神奇寶貝
					draw(realMap, x, y, player, win);
				}
				else
				{
					int oldx = x, oldy = y;
					if (k == 'a' || k == 'A') { --x; } // 依照按鍵移動玩家位置
					else if (k == 'd' || k == 'D') { ++x; }
					else if (k == 'w' || k == 'W') { --y; }
					else if (k == 's' || k == 'S') { ++y; }
					if (NOMOVE) // 判斷移動是否合法
					{ // 不合法移動 -> 維持原位
						x = oldx;
						y = oldy;
					}
					else // 合法移動
					{
						drawAgain(realMap, oldx, oldy, x, y, player); // 輸出玩家新位置
						if (player.pokemonListSize() < 34 && realMap[y - 1][x - 1] != '#' && !(rand() % 10))
							catchPokemon(realMap, x, y, player, win); // 捕抓神奇寶貝
						if (realMap[y - 1][x - 1] == '#') // 進入道館
						{
							if (player.pokemonListSize() < 3) // 神奇寶貝不足，無法進入戰鬥
							{
								rlutil::locate(10, 34);
								rlutil::setColor(6);
								std::cout << "玩家持有pokemon數量不足3隻，無法對戰，請捕抓更多pokemon";
							}
							else // 進入戰鬥
								battle(realMap, x, y, player, NPCList, win);
						}
					}
				}
			}
			rlutil::locate(1, 1); // 讓畫面回到頂端
			std::cout << " ";
		}

		if (win == 7) // 判斷是否結束遊戲
			return;
	}
}

// 設置玩家姓名
void setPlayerName(Player &player)
{
	std::system("cls"); // 清空螢幕

	rlutil::setColor(11);

	std::cout << "\n   歡迎遊玩本遊戲\n";

	bool again(1);

	string name; // 玩家姓名

	while (again)
	{
		std::cout << "\n   請輸入玩家姓名 : ";

		std::fflush(stdout);
		rlutil::setCursorVisibility(0);

		cin.clear();
		name.clear();

		getline(cin, name); // 輸入姓名

		std::cout << "\n   確認玩家姓名 : " << name;
		std::cout << "\n\n   是否更改玩家姓名?   \"不再更改\"請按:y   \"更改\"請按:n   (之後無法更改玩家姓名)";

		std::fflush(stdout);
		rlutil::setCursorVisibility(0);

		while (1) // 確認是否更改玩家姓名
			if (kbhit())
			{
				char k = getkey();
				if (k == 'y' || k == 'Y' || k == 'n' || k == 'N')
				{
					if (k == 'n' || k == 'N')
						std::system("cls");
					else if (k == 'y' || k == 'Y')
					{
						std::cout << "\n\n   已完成玩家姓名設定 : " << name << "\n\n   ";
						again = 0;
						std::system("pause");
					}
					break;
				}
			}
	}

	if (name != "")
		player.setName(name); // 設置玩家姓名
}

// 設置NPC
void setNPC(vector< Player >& NPCList)
{ // 初始化NPC
	Player npc1("NPC 1", list, damageRate);
	Player npc2("NPC 2", list, damageRate);
	Player npc3("NPC 3", list, damageRate);
	Player npc5("NPC 5", list, damageRate);
	Player npc6("NPC 6", list, damageRate);
	Player npc7("NPC 7", list, damageRate);
	Player npc8("NPC 8", list, damageRate);
	Player npc9("NPC 9", list, damageRate);
	Player npcA("NPC A", list, damageRate);
	Player npcB("NPC B", list, damageRate);
	Player npcC("NPC C", list, damageRate);
	Player npcD("NPC D", list, damageRate);

	NPCList.push_back(npc1);
	NPCList.push_back(npc2);
	NPCList.push_back(npc3);
	NPCList.push_back(npc5);
	NPCList.push_back(npc6);
	NPCList.push_back(npc7);
	NPCList.push_back(npc8);
	NPCList.push_back(npc9);
	NPCList.push_back(npcA);
	NPCList.push_back(npcB);
	NPCList.push_back(npcC);
	NPCList.push_back(npcD);

	for (int i(0); i < 12; i++)
		for (int j(0); j < 3; j++)
		{
			NPCList[i].catchPokemonGenerally();
			NPCList[i].choicePokemonBattleList(j);
		}
}

// 玩法說明
void howToPlay()
{
	rlutil::setColor(14);

	std::cout << "\n   玩法說明\n\n" // 輸出訊息
		<< "       玩家可以使用 w s a d 按鍵在地圖中自由移動，移動過程中會隨機與神奇寶貝相遇。\n\n"
		<< "       與神奇寶貝相遇時，有機會收服神奇寶貝，並在道館和其他神奇寶貝戰鬥。\n\n"
		<< "       玩家最多可同時持有34隻神奇寶貝。\n\n"
		<< "       查看神奇寶貝時，會依序顯示 種類 (目前生命值 / 最大生命值)。\n\n"
		<< "       當玩家擁有的神奇寶貝數量到達3隻以上時，可以進入道館與NPC對戰。\n\n"
		<< "       共12個道館，每個道館有一位NPC，持有3隻神奇寶貝。\n\n"
		<< "       (備註 : 道館入口為 #  玩家圖示為 @)\n\n\n"
		<< "   對戰規則\n\n"
		<< "       進入道館後，玩家必須依出戰順序選擇要進行戰鬥的3隻神奇寶貝\n\n"
		<< "       選擇完畢後，系統會自動開始對戰，其中一方的對戰中神奇寶貝的生命值歸零時，排序為下一隻的神奇寶貝會自動出戰，\n\n"
		<< "       直到其中一方的3隻神奇寶貝全滅，另外一方獲得勝利。\n\n"
		<< "       對戰結束後，神奇寶貝會回復成初始狀態。\n\n"
		<< "       當玩家獲勝次數達到七場時，遊戲結束。\n\n";

	std::fflush(stdout);
	rlutil::setCursorVisibility(0);
}

// 結束遊戲
void endGame()
{
	system("cls"); // 清空螢幕

	locate(3, 3);
	setColor(14);
	std::cout << "您已獲得7勝，遊戲結束。\n\n  "; // 輸出訊息
	std::cout << "歡迎再次遊玩本遊戲\n\n  ";

	system("pause");
}

// 主函式
int main()
{
	readPokemonList(); // 讀入所有Pokemon的數據

	readGraph(); // 讀入所有Pokemon的圖

	readDamageRate(); // 讀入所有Pokemon的傷害倍率

	string map[50] = {}; // 暫存地圖

	char realMap[50][100] = {}; // 真地圖

	readMap(map, realMap); // 讀入地圖

	int x(20), y(30), win(0); // 座標和勝利次數
	
	Player player("玩家", list, damageRate); // 生成玩家

	howToPlay(); // 玩法說明

	srand(time(0));

	vector< Player > NPCList; // NPC列表

	setNPC(NPCList); // 生成NPC

	std::cout << "\n       ";

	std::fflush(stdout);
	rlutil::setCursorVisibility(0);

	std::system("pause");

	setPlayerName(player); // 設置玩家姓名

	draw(realMap, x, y, player, win); // 畫出地圖

	moveMap(realMap, x, y, player, NPCList, win); // 移動

	endGame(); // 結束遊戲
}