#include "NPC.h"
#include <ctime>

NPC::NPC(vector< Pokemon2 > list)
{
	srand(time(0));

	for (int i(1); i < 13; i++)
	{
		Player player("NPC", list);

		switch (i)
		{
		case 1:
			player.setName("NPC 1");
			break;
		case 2:
			player.setName("NPC 2");
			break;
		case 3:
			player.setName("NPC 3");
			break;
		case 4:
			player.setName("NPC 5");
			break;
		case 5:
			player.setName("NPC 6");
			break;
		case 6:
			player.setName("NPC7");
			break;
		case 7:
			player.setName("NPC 8");
			break;
		case 8:
			player.setName("NPC 9");
			break;
		case 9:
			player.setName("NPC A");
			break;
		case 10:
			player.setName("NPC B");
			break;
		case 11:
			player.setName("NPC C");
			break;
		case 12:
			player.setName("NPC D");
		}

		for(int j(0); j < 3; j++)
			player.catchPokemonGenerally();
		for (int j(0); j < 3; j++)
			player.choicePokemonBattleList(j);

		NPCList.push_back(player);
	}
}

Player NPC::currentNPC(int x, int y)
{
	int number(0);

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

	Player temp(NPCList[number]);

	return temp;
}