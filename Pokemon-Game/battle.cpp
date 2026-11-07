// 對戰系統
#include "Battle.h"
#include <fstream>
#include <iomanip>

vector< string > Battle::ability = {
									"No	沒有能力",
									"Heal	每回合回復HP3",
									"Burning	隨機附加不受防禦影響的傷害1~3",
									"Counter Attack	反擊1 / 5所受傷害",
									"Immunology	免疫降低能力值的特殊能力",
									"Leech Life	每次攻擊吸收2~3HP",
									"Avoid	1 / 5機率迴避攻擊",
									"Double Attack	1 / 5機率兩次攻擊",
									"Poison	被攻擊的敵方中毒每回合 - 2HP",
									"Lower Speed	攻擊時降低敵方速度值2",
									"Rock Skin	每次受到的傷害 - 2",
									"Lower Defence	攻擊時降低敵方防禦力2",
									"Lower Attack	攻擊時降低敵方攻擊力2" };

 // 初始化成員
Battle::Battle(Player player0, Player NPC0, vector< vector< double > > Rate)
	:player(player0),
	NPC(NPC0),
	damageRate(Rate)
{
	for (int i = 0; i < 3; i++) // 確保對戰前的神奇寶貝為初始狀態（保險）
		NPC.getPokemonBattleList()[i]->reset();

	ifstream inW("勝利.txt", ios::in); // 讀入勝利訊息
	ifstream inL("失敗.txt", ios::in); // 讀入失敗訊息
	string temp;

	while (getline(inW, temp))
		win.push_back(temp);

	while (getline(inL, temp))
		lose.push_back(temp);
}

// 進行戰鬥
bool Battle::fighting(vector< vector< string > > list)
{
	bool win(1);

	srand(time(0));

	int rd; // 指定先攻
	int cnt = 1; // 顯示回合數

	while (player.getCurrentPokemon() != nullptr && NPC.getCurrentPokemon() != nullptr) // 對戰直到一方的Pokemon全滅
	{

		player.getCurrentPokemon()->countdown(); // 回合開始時到數
		NPC.getCurrentPokemon()->countdown();

		setColor(15);
		locate(120, 5);
		std::cout << "雙方神奇寶貝回合開始時之數值 : ";

		setColor(10);
		locate(120, 9);
		std::cout << "我方神奇寶貝之攻擊力 : (" << player.getCurrentPokemon()->getATK() << " / " << player.getCurrentPokemon()->getInitialATK() << ')';

		locate(120, 11);
		std::cout << "我方神奇寶貝之防禦力 : (" << player.getCurrentPokemon()->getDEF() << " / " << player.getCurrentPokemon()->getInitialDEF() << ')';

		locate(120, 13);
		std::cout << "我方神奇寶貝之速度 : (" << player.getCurrentPokemon()->getSpeed() << " / " << player.getCurrentPokemon()->getInitialSpeed() << ')';

		locate(120, 15);
		std::cout << "我方神奇寶貝之技能 : ";
		locate(120, 17); 
		std::cout << ability[player.getCurrentPokemon()->getAbility()];


		setColor(4);
		locate(120, 20);
		std::cout << "敵方神奇寶貝之攻擊力 : (" << NPC.getCurrentPokemon()->getATK() << " / " << NPC.getCurrentPokemon()->getInitialATK() << ')';

		locate(120, 22);
		std::cout << "敵方神奇寶貝之防禦力 : (" << NPC.getCurrentPokemon()->getDEF() << " / " << NPC.getCurrentPokemon()->getInitialDEF() << ')';

		locate(120, 24);
		std::cout << "敵方神奇寶貝之速度 : (" << NPC.getCurrentPokemon()->getSpeed() << " / " << NPC.getCurrentPokemon()->getInitialSpeed() << ')';

		locate(120, 26);
		std::cout << "敵方神奇寶貝之技能 : ";
		locate(120, 28);
		std::cout << ability[NPC.getCurrentPokemon()->getAbility()];

		setColor(15);
		locate(120, 32);
		std::cout << "傷害倍率 : ";

		locate(120, 34);
		std::cout << "我方給予傷害乘 " << getDamageRate(*player.getCurrentPokemon(), *NPC.getCurrentPokemon());
		locate(120, 36);
		std::cout << "敵方給予傷害乘 " << getDamageRate(*NPC.getCurrentPokemon(), *player.getCurrentPokemon());


		try
		{
			rd = (player.getCurrentPokemon()->getSpeed() > NPC.getCurrentPokemon()->getSpeed()) ? 1 : 0;
			// 速度決定先攻，速度相等時隨機先攻
			if (player.getCurrentPokemon()->getSpeed() == NPC.getCurrentPokemon()->getSpeed())
				rd = rand() % 2;

			int x(60), y(0);

			locate(1, 1);
			for (int i(0); i < 30; i++) // 輸出玩家神奇寶貝圖像
				std::cout << list[(double)player.getCurrentPokemon()->getID() - 1][i] << endl;

			for (int i(0); i < 30; i++) // 輸出NPC神奇寶貝圖像
			{
				locate(x, ++y);
				std::cout << list[(double)NPC.getCurrentPokemon()->getID() - 1][i];
			}

			setColor(14);
			locate(6, 26); // 輸出玩家神奇寶貝資訊
			cout << "玩家Pokemon名稱 : " << setw(10) << player.getCurrentPokemon()->getName();
			locate(6, 28);
			cout << "玩家Pokemon屬性 : " << setw(10) << player.getCurrentPokemon()->getType();

			locate(65, 26); // 輸出NPC神奇寶貝資訊
			cout << "敵方Pokemon名稱 : " << setw(10) << NPC.getCurrentPokemon()->getName();
			locate(65, 28);
			cout << "敵方Pokemon屬性 : " << setw(10) << NPC.getCurrentPokemon()->getType();

			locate(6, 30); // 輸出玩家持有神奇寶貝
			std::cout << "玩家目前持有Pokemon :           ";
			player.showAlivePokemon(6, 30);

			locate(65, 30); // 輸出NPC持有神奇寶貝
			std::cout << "敵方目前持有Pokemon :           ";
			NPC.showAlivePokemon(65, 30);

			locate(6, 37);

			std::cout << "\n     ============================================================================================";

			if (rd) {
				std::cout << "\n\n     Round " << cnt << "  "; // 輸出回合數
				std::cout << "     " << player.getName() << "先攻" << std::endl; // 輸出先攻

				player.getCurrentPokemon()->attack(*NPC.getCurrentPokemon()); // 互相傷害
				cout << "\n     " << player.getName() << "的" << player.getCurrentPokemon()->getName() << "對" 
					<< NPC.getName() << "的" << NPC.getCurrentPokemon()->getName() << "發動攻擊   "
					<< NPC.getName() << "的對戰中Pokemon剩餘血量 : ";
				NPC.getCurrentPokemon()->showStats(); // 顯示血量

				if (NPC.getCurrentPokemon()->getHP() <= 0) // 當一方Pokemon死亡，對戰暫停
					throw Dead(NPC, player); // 擲出死亡例外

				NPC.getCurrentPokemon()->attack(*player.getCurrentPokemon()); // 互相傷害
				cout << "\n     " << NPC.getName() << "的" << NPC.getCurrentPokemon()->getName() << "對"
					<< player.getName() << "的" << player.getCurrentPokemon()->getName() << "發動攻擊   "
					<< player.getName() << "的對戰中Pokemon剩餘血量 : ";
				player.getCurrentPokemon()->showStats(); // 顯示血量

				if (player.getCurrentPokemon()->getHP() <= 0) // 當一方Pokemon死亡，對戰暫停
					throw Dead(player, NPC); // 擲出死亡例外

				std::cout << "\n     ============================================================================================";
				cnt++; // 回合數增加
			}
			else
			{
				std::cout << "\n\n     " << "Round " << cnt << "  "; // 輸出回合數
				std::cout << "     " << NPC.getName() << "先攻" << std::endl; // 輸出先攻

				NPC.getCurrentPokemon()->attack(*player.getCurrentPokemon()); // 互相傷害
				cout << "\n     " << NPC.getName() << "的" << NPC.getCurrentPokemon()->getName() << "對"
					<< player.getName() << "的" << player.getCurrentPokemon()->getName() << "發動攻擊   "
					<< player.getName() << "的對戰中Pokemon剩餘血量 : ";
				player.getCurrentPokemon()->showStats(); // 顯示血量

				if (player.getCurrentPokemon()->getHP() <= 0) // 當一方Pokemon死亡，對戰暫停
					throw Dead(player, NPC); // 擲出死亡例外

				player.getCurrentPokemon()->attack(*NPC.getCurrentPokemon()); // 互相傷害
				cout << "\n     " << player.getName() << "的" << player.getCurrentPokemon()->getName() << "對"
					<< NPC.getName() << "的" << NPC.getCurrentPokemon()->getName() << "發動攻擊   "
					<< NPC.getName() << "的對戰中Pokemon剩餘血量 : ";
				NPC.getCurrentPokemon()->showStats(); // 顯示血量

				if (NPC.getCurrentPokemon()->getHP() <= 0) // 當一方Pokemon死亡，對戰暫停
					throw Dead(NPC, player); // 擲出死亡例外

				std::cout << "\n     ============================================================================================" ;
				cnt++; // 回合數增加
			}
			cout << "     ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			std::system("pause"); 
			system("cls"); // 清空螢幕
		}
		
		catch (Dead& dead)
		{
			dead.outputMessage(); // 輸出訊息

			std::cout << "\n     ============================================================================================";
			cnt++; // 回合數增加

			player.deadPokemon(); // 判斷死亡
			NPC.deadPokemon(); // 判斷死亡

			cout << "     ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			std::system("pause");
			system("cls"); // 清空螢幕
		}

		// 當一方Pokemon全滅，對戰結束
		if (player.getCurrentPokemon() == nullptr || NPC.getCurrentPokemon() == nullptr)
		{
			string winner(player.getName());
			if (player.getCurrentPokemon() == nullptr) // 確認贏家姓名
			{
				winner = NPC.getName();
				win = 0;
			}
			// 輸出訊息
			std::cout << endl << "     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" << endl;
			locate((105 - winner.length()) / 2, 5);
			std::cout << winner << " 獲勝\n\n";
			std::cout << endl << "     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" << endl;
			
			if(winner == player.getName())
				for (int i = 0; i < Battle::win.size(); i++)
					cout << Battle::win[i] << endl; // 輸出勝利訊息
			else
				for (int i = 0; i < Battle::lose.size(); i++)
					cout << Battle::lose[i] << endl; // 輸出失敗訊息
		}
	}

	std::cout << "\n\n\n                                            ";
	// 復原神奇寶貝狀態
	for (int i = 0; i < player.getPokemonBattleList().size(); i++)
		player.getPokemonBattleList()[i]->reset();
	for (int i = 0; i < NPC.getPokemonBattleList().size(); i++)
		NPC.getPokemonBattleList()[i]->reset();

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);

	std::system("pause");

	return win; // 回傳是否獲勝
}

// 回傳傷害倍率
template < typename T, typename Ty >
double Battle::getDamageRate(T atk, Ty def)
{
	Pokemon2* pokemons[2] = { &atk, &def };
	int Type[2] = { 0, 0 };

	for (int i(0); i < 2; i++) // 根據雙方屬性決定傷害倍率
	{
		if (pokemons[i]->getType() == "Fire")
			Type[i] = 1;
		else if (pokemons[i]->getType() == "Water")
			Type[i] = 2;
		else if (pokemons[i]->getType() == "Electric")
			Type[i] = 3;
		else if (pokemons[i]->getType() == "Grass")
			Type[i] = 4;
		else if (pokemons[i]->getType() == "Ice")
			Type[i] = 5;
		else if (pokemons[i]->getType() == "Fighting")
			Type[i] = 6;
		else if (pokemons[i]->getType() == "Poison")
			Type[i] = 7;
		else if (pokemons[i]->getType() == "Ground")
			Type[i] = 8;
		else if (pokemons[i]->getType() == "Flying")
			Type[i] = 9;
		else if (pokemons[i]->getType() == "Psychic")
			Type[i] = 10;
		else if (pokemons[i]->getType() == "Bug")
			Type[i] = 11;
		else if (pokemons[i]->getType() == "Rock")
			Type[i] = 12;
		else if (pokemons[i]->getType() == "Ghost")
			Type[i] = 13;
		else if (pokemons[i]->getType() == "Dragon")
			Type[i] = 14;
		else if (pokemons[i]->getType() == "Dark")
			Type[i] = 15;
		else if (pokemons[i]->getType() == "Steel")
			Type[i] = 16;
		else if (pokemons[i]->getType() == "Fairy")
			Type[i] = 17;
	}
	return damageRate[Type[0]][Type[1]]; // 回傳傷害倍率
}