// �D�{��
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

vector< Pokemon2 > list; // ���_�_���M��
vector< vector< string > > graphList; // ���_�_����
vector< vector< double > > damageRate; // �ݩʶˮ`���v

// Ū�J�a��
void readMap(string map[50], char realMap[][100])
{
	ifstream in("yzumap.txt", ifstream::in);

	for (int i(0); i < 31; i++) // Ū�J���a��
		getline(in, map[i]);

	for (int i(0); i < 31; i++) // Ū�J�u�a��
		for (int j(0); j < 91; j++)
			realMap[i][j] = map[i][j];
}

// Ū�J�Ҧ�Pokemon����
void readGraph()
{
	ifstream graphIn[35] = {}; // �}��
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

		for (int i(0); i < 30; i++) // Ū�J�@�i���_�_����
			getline(graphIn[num], graph[i]);

		graphList.push_back(graph); // �s�J�@�i���_�_����
	}
}

// Ū�J�Ҧ�Pokemon���ƾ�
void readPokemonList()
{
	ifstream in("pokemons.csv", ifstream::in);

	stringstream STRING1, STRING2;

	string str;

	Pokemon2 temp;

	int itemp;
	double dtemp;
	string stemp;
	
	// �N��Ƥ@���Ū�J
	while (getline(in, str, '\n'))
	{
		STRING1.str("");
		STRING1.clear();
		STRING1 << str;

		int n = 0;
		// �N��ƥγr�����}Ū�J
		while (getline(STRING1, str, ','))
		{
			STRING2.str("");
			STRING2.clear();
			STRING2 << str;

			// �N����ন���T����ƫ��A
			if (n == 0)
			{
				STRING2 >> itemp;
				temp.setID(itemp);// �]�mID
				n++;
			}
			else if (n == 1)
			{
				STRING2 >> stemp;
				temp.setName(stemp);// �]�m�W�r
				n++;
			}
			else if (n == 2)
			{
				STRING2 >> stemp;
				temp.setType(stemp);// �]�m�ݩ�
				n++;
			}
			else if (n == 3)
			{
				STRING2 >> dtemp;
				temp.setMaxHP(dtemp);// �]�mHP
				n++;
			}
			else if (n == 4)
			{
				STRING2 >> dtemp;
				temp.setInitialATK(dtemp);// �]�mATK
				n++;
			}
			else if (n == 5)
			{
				STRING2 >> dtemp;
				temp.setInitialDEF(dtemp);// �]�mDEF
				n++;
			}
			else if (n == 6)
			{
				STRING2 >> itemp;
				temp.setInitialSpeed(itemp);// �]�mSpeed
				n++;
			}
			else if (n == 7)
			{
				STRING2 >> itemp;
				temp.setAbility(itemp);// �]�m�ޯ�
				n++;
			}
		}
		list.push_back(temp);// �s�J�M��
	}
}

// Ū�J�ݩʶˮ`���v
void readDamageRate()
{
	ifstream in("type.csv", ifstream::in);

	stringstream STRING1, STRING2;

	string str;

	double dtemp;

	// �N��Ƥ@���Ū�J
	while (getline(in, str, '\n'))
	{
		vector< double > temp;

		STRING1.str("");
		STRING1.clear();
		STRING1 << str;

		// �N��ƥγr�����}Ū�J
		while (getline(STRING1, str, ','))
		{
			STRING2.str("");
			STRING2.clear();
			STRING2 << str;
			STRING2 >> dtemp;
			temp.push_back(dtemp); // �s�J���v
		}
		damageRate.push_back(temp); // �s�J�C��
	}
}

// �e��
void draw(char map[][100], int& x, int& y, Player& player, int& win)
{
	std::system("cls"); // �M�ù�

	for (int i(0); i < 31; i++) // �Τ��P�C���X���P�Ÿ�
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
	std::cout << "�ثePokemon�����ƶq : " << player.pokemonListSize();

	rlutil::locate(45, 36);
	std::cout << "�ثe��ӳ��� : " << win; // �i����ӳ���

	rlutil::locate(10, 38);
	std::cout << "Pokemon�����W����34���A�����ƶq�F��34���ɱN���|�b���W�J��Pokemon";

	if (player.pokemonListSize() > 0)
	{
		rlutil::locate(10, 40);
		std::cout << "�ثe����Pokemon :           ";
		player.showPokemons(); // �i�ܪ��a����Pokemon

		rlutil::locate(100, 3);
		rlutil::setColor(15);
		std::cout << ":+: �� �J �� �� �� �� �r �� �� �� �� �A �P �� �z �� �t �X �C :+:";
		
		rlutil::locate(100, 5);
		rlutil::setColor(12);
		std::cout << "�Y�Q�d�ݯ��_�_����T�A�Ы����� t";

		rlutil::locate(146, 5);
		rlutil::setColor(6);
		std::cout << "�Y�Q���񯫩_�_���A�Ы����� r";
	}

	rlutil::locate(x, y);
	rlutil::setColor(12);
	std::cout << "@"; // ��X���a��m

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);
}

// �ק缾�a��m
void drawAgain(char map[][100], int oldx, int oldy, int& x, int& y, Player& player)
{
	if (MAP == '*') // �_�쪱�a�쥻��m����X�r��
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
	std::cout << "@"; // �b�s��m��X���a

	rlutil::locate(10, 34);
	std::cout << "                                                       "; // �л\���ܰT��

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);
}

// ���쯫�_�_��
void catchPokemon(char realMap[][100], int &x, int &y, Player &player,int &win)
{
	srand(time(0)); // �H��

	std::system("cls"); // �M�ſù�
	
	if (realMap[y - 1][x - 1] == ';') // �̤��P�a�I�վ㮷�쭿�v�åB������
		player.catchPokemonGress();
	else if (realMap[y - 1][x - 1] == '~')
		player.catchPokemonWater();
	else
		player.catchPokemonGenerally();

	for (int i(0); i < 30; i++) // ��X�ݮ��쯫�_�_������
		std::cout << graphList[(double)player.lastPokemonType()->getID() - 1][i] << endl;

	rlutil::locate(50, 10); // ��X�ݮ��쯫�_�_����T
	rlutil::setColor(11);
	std::cout << "�X�{Pokemon���� : " << player.lastPokemonType()->getName() << endl << endl;
	
	rlutil::locate(50, 17);
	std::cout << "�X�{Pokemon�ݩ� : " << player.lastPokemonType()->getType() << endl << endl;

	rlutil::locate(1, 29);

	if(player.pokemonListSize() == 1) // ��X���a���������_�_��
		std::cout << "    ���a�ثe�S��Pokemon              ";
	else
	{
		std::cout << "    �ثe����Pokemon :                ";
		player.showPokemonsGET();
	}

	std::cout << "�п�ܬO�_����      \"�O\"�Ы�:y�@�@�@\"�_\"�Ы�:n          \n";
	while(1) // ��ܬO�_����@---  �ƹ�W�O������A�M�w�n���n����
		if (kbhit())
		{
			char k = getkey();
			if (k == 'y' || k == 'Y' || k == 'n' || k == 'N')
			{
				if (k == 'y' || k == 'Y') // ����
				{
					if (rand() % 2) // ���즨�\
					{
						std::cout << "\n                                     �w�����Pokemon\n";
						if (player.pokemonListSize() > 3)
						{
							std::cout << "\n                                     ����Pokemon�w�W�L3���A�i��ܬO�_�����~���쪺Pokemon\n";
							std::cout << "\n                                     �п�ܬO�_����    \"�O�d\"�Ы�:y�@�@�@\"����\"�Ы�:n          \n";

							while (1) // ��ܬO�_�O�d
								if (kbhit())
								{
									char k = getkey();
									if (k == 'y' || k == 'Y' || k == 'n' || k == 'N')
									{
										if (k == 'n' || k == 'N') // ����
										{
											player.freedPokemon(player.pokemonListSize());
											std::cout << "\n                                     �w�����Pokemon";
										}
										else if (k == 'y' || k == 'Y') // �O�d
											std::cout << "\n                                     �w�O�d��Pokemon";

										break;
									}
								}
						}
					}
					else
					{
						player.freedPokemon(player.pokemonListSize()); // ���쥢��
						std::cout << "\n                                     ��Pokemon���쥢��";
					}

				}
				else if (k == 'n' || k == 'N') // ��󮷧�
				{
					player.freedPokemon(player.pokemonListSize());
					std::cout << "\n                                     ��󮷧��Pokemon";
				}

				break;
			}
		}

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);

	std::cout << "\n\n                                     ";
	std::system("pause");

	draw(realMap, x, y, player, win); // �^��a��
}

// �^�ǭn�i��԰���NPC
Player& currentNPC(int x, int y, vector< Player >& NPCList)
{
	int number(0);

	// �̾ڪ��a�{�b��m�M�w�^�ǭ��@��NPC
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

// �԰�
void battle(char realMap[][100], int x, int y, Player &player, vector< Player >& NPCList, int& win)
{
	rlutil::setColor(10);

	player.askAboutBattleOptions(); // ��ܰѾԯ��_�_��

	std::system("cls"); // �M�ſù�

	Battle battle(player, currentNPC(x, y, NPCList), damageRate); // �ͦ��԰�

	if (battle.fighting(graphList)) // �i��԰�
		win++;

	if(win < 7) // �P�_�O�_�����C��
		draw(realMap, x, y, player, win); // �Y�������C���A�^��a��
}

// ����
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
					player.showPokemonDetail(100, 7, graphList); // �i�ܯ��_�_��
					draw(realMap, x, y, player, win);
				}
				else if (k == 'r' || k == 'R')
				{
					player.FreedPokemon(146, 7); // ���񯫩_�_��
					draw(realMap, x, y, player, win);
				}
				else
				{
					int oldx = x, oldy = y;
					if (k == 'a' || k == 'A') { --x; } // �̷ӫ��䲾�ʪ��a��m
					else if (k == 'd' || k == 'D') { ++x; }
					else if (k == 'w' || k == 'W') { --y; }
					else if (k == 's' || k == 'S') { ++y; }
					if (NOMOVE) // �P�_���ʬO�_�X�k
					{ // ���X�k���� -> �������
						x = oldx;
						y = oldy;
					}
					else // �X�k����
					{
						drawAgain(realMap, oldx, oldy, x, y, player); // ��X���a�s��m
						if (player.pokemonListSize() < 34 && realMap[y - 1][x - 1] != '#' && !(rand() % 10))
							catchPokemon(realMap, x, y, player, win); // ���쯫�_�_��
						if (realMap[y - 1][x - 1] == '#') // �i�J�D�]
						{
							if (player.pokemonListSize() < 3) // ���_�_�������A�L�k�i�J�԰�
							{
								rlutil::locate(10, 34);
								rlutil::setColor(6);
								std::cout << "���a����pokemon�ƶq����3���A�L�k��ԡA�Ю����hpokemon";
							}
							else // �i�J�԰�
								battle(realMap, x, y, player, NPCList, win);
						}
					}
				}
			}
			rlutil::locate(1, 1); // ���e���^�쳻��
			std::cout << " ";
		}

		if (win == 7) // �P�_�O�_�����C��
			return;
	}
}

// �]�m���a�m�W
void setPlayerName(Player &player)
{
	std::system("cls"); // �M�ſù�

	rlutil::setColor(11);

	std::cout << "\n   �w��C�����C��\n";

	bool again(1);

	string name; // ���a�m�W

	while (again)
	{
		std::cout << "\n   �п�J���a�m�W : ";

		std::fflush(stdout);
		rlutil::setCursorVisibility(0);

		cin.clear();
		name.clear();

		getline(cin, name); // ��J�m�W

		std::cout << "\n   �T�{���a�m�W : " << name;
		std::cout << "\n\n   �O�_��缾�a�m�W?   \"���A���\"�Ы�:y   \"���\"�Ы�:n   (����L�k��缾�a�m�W)";

		std::fflush(stdout);
		rlutil::setCursorVisibility(0);

		while (1) // �T�{�O�_��缾�a�m�W
			if (kbhit())
			{
				char k = getkey();
				if (k == 'y' || k == 'Y' || k == 'n' || k == 'N')
				{
					if (k == 'n' || k == 'N')
						std::system("cls");
					else if (k == 'y' || k == 'Y')
					{
						std::cout << "\n\n   �w�������a�m�W�]�w : " << name << "\n\n   ";
						again = 0;
						std::system("pause");
					}
					break;
				}
			}
	}

	if (name != "")
		player.setName(name); // �]�m���a�m�W
}

// �]�mNPC
void setNPC(vector< Player >& NPCList)
{ // ��l��NPC
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

// ���k����
void howToPlay()
{
	rlutil::setColor(14);

	std::cout << "\n   ���k����\n\n" // ��X�T��
		<< "       ���a�i�H�ϥ� w s a d ����b�a�Ϥ��ۥѲ��ʡA���ʹL�{���|�H���P���_�_���۹J�C\n\n"
		<< "       �P���_�_���۹J�ɡA�����|���A���_�_���A�æb�D�]�M��L���_�_���԰��C\n\n"
		<< "       ���a�̦h�i�P�ɫ���34�����_�_���C\n\n"
		<< "       �d�ݯ��_�_���ɡA�|�̧���� ���� (�ثe�ͩR�� / �̤j�ͩR��)�C\n\n"
		<< "       ���a�֦������_�_���ƶq��F3���H�W�ɡA�i�H�i�J�D�]�PNPC��ԡC\n\n"
		<< "       �@12�ӹD�]�A�C�ӹD�]���@��NPC�A����3�����_�_���C\n\n"
		<< "       (�Ƶ� : �D�]�J�f�� #  ���a�ϥܬ� @)\n\n\n"
		<< "   ��ԳW�h\n\n"
		<< "       �i�J�D�]��A���a�����̥X�Զ��ǿ�ܭn�i��԰���3�����_�_��\n\n"
		<< "       ��ܧ�����A�t�η|�۰ʶ}�l��ԡA�䤤�@�誺��Ԥ����_�_�����ͩR���k�s�ɡA�ƧǬ��U�@�������_�_���|�۰ʥX�ԡA\n\n"
		<< "       ����䤤�@�誺3�����_�_�������A�t�~�@����o�ӧQ�C\n\n"
		<< "       ��Ե�����A���_�_���|�^�_����l���A�C\n\n"
		<< "       ���a��Ӧ��ƹF��C���ɡA�C�������C\n\n";

	std::fflush(stdout);
	rlutil::setCursorVisibility(0);
}

// �����C��
void endGame()
{
	system("cls"); // �M�ſù�

	locate(3, 3);
	setColor(14);
	std::cout << "�z�w��o7�ӡA�C�������C\n\n  "; // ��X�T��
	std::cout << "�w��A���C�����C��\n\n  ";

	system("pause");
}

// �D�禡
int main()
{
	readPokemonList(); // Ū�J�Ҧ�Pokemon���ƾ�

	readGraph(); // Ū�J�Ҧ�Pokemon����

	readDamageRate(); // Ū�J�Ҧ�Pokemon���ˮ`���v

	string map[50] = {}; // �Ȧs�a��

	char realMap[50][100] = {}; // �u�a��

	readMap(map, realMap); // Ū�J�a��

	int x(20), y(30), win(0); // �y�ЩM�ӧQ����
	
	Player player("���a", list, damageRate); // �ͦ����a

	howToPlay(); // ���k����

	srand(time(0));

	vector< Player > NPCList; // NPC�C��

	setNPC(NPCList); // �ͦ�NPC

	std::cout << "\n       ";

	std::fflush(stdout);
	rlutil::setCursorVisibility(0);

	std::system("pause");

	setPlayerName(player); // �]�m���a�m�W

	draw(realMap, x, y, player, win); // �e�X�a��

	moveMap(realMap, x, y, player, NPCList, win); // ����

	endGame(); // �����C��
}