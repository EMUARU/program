// �ҥ~�B�z
#pragma once
#include <iostream>
#include <exception>
#include "Player.h"
#include "rlutil.h"

using namespace rlutil;
using namespace std;

// �԰������`�N�~
class Dead
{
public:
	Dead(Player &player01, Player &player02); // �غc�l
	void outputMessage(); // ��X�T��
private:
	Player& player1; // ���a�@
	Player& player2; // ���a�G
};