// ��Ԩt��
#pragma once
#include "Player.h"
#include "Exception_dead.h"
#include "rlutil.h"
using namespace rlutil;

// �԰�
class Battle
{
public:
	Battle(Player player, Player NPC, vector< vector< double > > Rate); // �غc�l �ͦ��԰�
	bool fighting(vector< vector< string > > list); // ����԰�
	template < typename T, typename Ty >
	double getDamageRate(T atk, Ty def); // �ˮ`���v
private:
	Player player; // ���a
	Player NPC; // NPC
	vector< string > win; // �ӧQ�T��
	vector< string > lose; // ���ѰT��
	static vector< string > ability; // ��O�T��
	vector< vector< double > > damageRate; // �ˮ`���v
};