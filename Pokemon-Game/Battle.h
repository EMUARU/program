// 對戰系統
#pragma once
#include "Player.h"
#include "Exception_dead.h"
#include "rlutil.h"
using namespace rlutil;

// 戰鬥
class Battle
{
public:
	Battle(Player player, Player NPC, vector< vector< double > > Rate); // 建構子 生成戰鬥
	bool fighting(vector< vector< string > > list); // 執行戰鬥
	template < typename T, typename Ty >
	double getDamageRate(T atk, Ty def); // 傷害倍率
private:
	Player player; // 玩家
	Player NPC; // NPC
	vector< string > win; // 勝利訊息
	vector< string > lose; // 失敗訊息
	static vector< string > ability; // 能力訊息
	vector< vector< double > > damageRate; // 傷害倍率
};