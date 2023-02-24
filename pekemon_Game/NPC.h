#pragma once
#include "Player.h"

class NPC
{
public:
	NPC(vector< Pokemon2 > list);
	Player currentNPC(int x, int y);
private:
	vector< Player > NPCList;
};