// �ҥ~�B�z
#include "Exception_dead.h"

 // �B�z�԰������`�N�~
Dead::Dead(Player &player01, Player &player02) // ��l�Ʀ���
	:player1(player01),
	player2(player02)
{
}

// ��X�T��
void Dead::outputMessage()
{
	setColor(4); // ��X���`�T��
	std::cout << "\n     " << ">>> " << player1.getName() << " �� " << player1.getCurrentPokemon()->getName() << " ���`, " << player2.getName() << " �� " << player2.getCurrentPokemon()->getName() << " �Ʀs! <<<\n" << std::endl;
	setColor(14);
	cout << "     " << player2.getName() << "���ƦsPokemon�Ѿl��q : "; // ��X�Ʀs�T��
	player2.getCurrentPokemon()->showStats();
}