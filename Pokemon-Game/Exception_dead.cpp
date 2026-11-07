// 例外處理
#include "Exception_dead.h"

 // 處理戰鬥中死亡意外
Dead::Dead(Player &player01, Player &player02) // 初始化成員
	:player1(player01),
	player2(player02)
{
}

// 輸出訊息
void Dead::outputMessage()
{
	setColor(4); // 輸出死亡訊息
	std::cout << "\n     " << ">>> " << player1.getName() << " 的 " << player1.getCurrentPokemon()->getName() << " 死亡, " << player2.getName() << " 的 " << player2.getCurrentPokemon()->getName() << " 倖存! <<<\n" << std::endl;
	setColor(14);
	cout << "     " << player2.getName() << "的倖存Pokemon剩餘血量 : "; // 輸出倖存訊息
	player2.getCurrentPokemon()->showStats();
}