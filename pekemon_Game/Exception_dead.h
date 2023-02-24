// 例外處理
#pragma once
#include <iostream>
#include <exception>
#include "Player.h"
#include "rlutil.h"

using namespace rlutil;
using namespace std;

// 戰鬥中死亡意外
class Dead
{
public:
	Dead(Player &player01, Player &player02); // 建構子
	void outputMessage(); // 輸出訊息
private:
	Player& player1; // 玩家一
	Player& player2; // 玩家二
};