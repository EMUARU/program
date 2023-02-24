// ��Ԩt��
#include "Battle.h"
#include <fstream>
#include <iomanip>

vector< string > Battle::ability = {
									"No	�S����O",
									"Heal	�C�^�X�^�_HP3",
									"Burning	�H�����[�������m�v�T���ˮ`1~3",
									"Counter Attack	����1 / 5�Ҩ��ˮ`",
									"Immunology	�K�̭��C��O�Ȫ��S���O",
									"Leech Life	�C�������l��2~3HP",
									"Avoid	1 / 5���v�j�ק���",
									"Double Attack	1 / 5���v�⦸����",
									"Poison	�Q�������Ĥ褤�r�C�^�X - 2HP",
									"Lower Speed	�����ɭ��C�Ĥ�t�׭�2",
									"Rock Skin	�C�����쪺�ˮ` - 2",
									"Lower Defence	�����ɭ��C�Ĥ訾�m�O2",
									"Lower Attack	�����ɭ��C�Ĥ�����O2" };

 // ��l�Ʀ���
Battle::Battle(Player player0, Player NPC0, vector< vector< double > > Rate)
	:player(player0),
	NPC(NPC0),
	damageRate(Rate)
{
	for (int i = 0; i < 3; i++) // �T�O��ԫe�����_�_������l���A�]�O�I�^
		NPC.getPokemonBattleList()[i]->reset();

	ifstream inW("�ӧQ.txt", ios::in); // Ū�J�ӧQ�T��
	ifstream inL("����.txt", ios::in); // Ū�J���ѰT��
	string temp;

	while (getline(inW, temp))
		win.push_back(temp);

	while (getline(inL, temp))
		lose.push_back(temp);
}

// �i��԰�
bool Battle::fighting(vector< vector< string > > list)
{
	bool win(1);

	srand(time(0));

	int rd; // ���w����
	int cnt = 1; // ��ܦ^�X��

	while (player.getCurrentPokemon() != nullptr && NPC.getCurrentPokemon() != nullptr) // ��Ԫ���@�誺Pokemon����
	{

		player.getCurrentPokemon()->countdown(); // �^�X�}�l�ɨ��
		NPC.getCurrentPokemon()->countdown();

		setColor(15);
		locate(120, 5);
		std::cout << "���诫�_�_���^�X�}�l�ɤ��ƭ� : ";

		setColor(10);
		locate(120, 9);
		std::cout << "�ڤ诫�_�_���������O : (" << player.getCurrentPokemon()->getATK() << " / " << player.getCurrentPokemon()->getInitialATK() << ')';

		locate(120, 11);
		std::cout << "�ڤ诫�_�_�������m�O : (" << player.getCurrentPokemon()->getDEF() << " / " << player.getCurrentPokemon()->getInitialDEF() << ')';

		locate(120, 13);
		std::cout << "�ڤ诫�_�_�����t�� : (" << player.getCurrentPokemon()->getSpeed() << " / " << player.getCurrentPokemon()->getInitialSpeed() << ')';

		locate(120, 15);
		std::cout << "�ڤ诫�_�_�����ޯ� : ";
		locate(120, 17); 
		std::cout << ability[player.getCurrentPokemon()->getAbility()];


		setColor(4);
		locate(120, 20);
		std::cout << "�Ĥ诫�_�_���������O : (" << NPC.getCurrentPokemon()->getATK() << " / " << NPC.getCurrentPokemon()->getInitialATK() << ')';

		locate(120, 22);
		std::cout << "�Ĥ诫�_�_�������m�O : (" << NPC.getCurrentPokemon()->getDEF() << " / " << NPC.getCurrentPokemon()->getInitialDEF() << ')';

		locate(120, 24);
		std::cout << "�Ĥ诫�_�_�����t�� : (" << NPC.getCurrentPokemon()->getSpeed() << " / " << NPC.getCurrentPokemon()->getInitialSpeed() << ')';

		locate(120, 26);
		std::cout << "�Ĥ诫�_�_�����ޯ� : ";
		locate(120, 28);
		std::cout << ability[NPC.getCurrentPokemon()->getAbility()];

		setColor(15);
		locate(120, 32);
		std::cout << "�ˮ`���v : ";

		locate(120, 34);
		std::cout << "�ڤ赹���ˮ`�� " << getDamageRate(*player.getCurrentPokemon(), *NPC.getCurrentPokemon());
		locate(120, 36);
		std::cout << "�Ĥ赹���ˮ`�� " << getDamageRate(*NPC.getCurrentPokemon(), *player.getCurrentPokemon());


		try
		{
			rd = (player.getCurrentPokemon()->getSpeed() > NPC.getCurrentPokemon()->getSpeed()) ? 1 : 0;
			// �t�רM�w����A�t�׬۵����H������
			if (player.getCurrentPokemon()->getSpeed() == NPC.getCurrentPokemon()->getSpeed())
				rd = rand() % 2;

			int x(60), y(0);

			locate(1, 1);
			for (int i(0); i < 30; i++) // ��X���a���_�_���Ϲ�
				std::cout << list[(double)player.getCurrentPokemon()->getID() - 1][i] << endl;

			for (int i(0); i < 30; i++) // ��XNPC���_�_���Ϲ�
			{
				locate(x, ++y);
				std::cout << list[(double)NPC.getCurrentPokemon()->getID() - 1][i];
			}

			setColor(14);
			locate(6, 26); // ��X���a���_�_����T
			cout << "���aPokemon�W�� : " << setw(10) << player.getCurrentPokemon()->getName();
			locate(6, 28);
			cout << "���aPokemon�ݩ� : " << setw(10) << player.getCurrentPokemon()->getType();

			locate(65, 26); // ��XNPC���_�_����T
			cout << "�Ĥ�Pokemon�W�� : " << setw(10) << NPC.getCurrentPokemon()->getName();
			locate(65, 28);
			cout << "�Ĥ�Pokemon�ݩ� : " << setw(10) << NPC.getCurrentPokemon()->getType();

			locate(6, 30); // ��X���a�������_�_��
			std::cout << "���a�ثe����Pokemon :           ";
			player.showAlivePokemon(6, 30);

			locate(65, 30); // ��XNPC�������_�_��
			std::cout << "�Ĥ�ثe����Pokemon :           ";
			NPC.showAlivePokemon(65, 30);

			locate(6, 37);

			std::cout << "\n     ============================================================================================";

			if (rd) {
				std::cout << "\n\n     Round " << cnt << "  "; // ��X�^�X��
				std::cout << "     " << player.getName() << "����" << std::endl; // ��X����

				player.getCurrentPokemon()->attack(*NPC.getCurrentPokemon()); // ���۶ˮ`
				cout << "\n     " << player.getName() << "��" << player.getCurrentPokemon()->getName() << "��" 
					<< NPC.getName() << "��" << NPC.getCurrentPokemon()->getName() << "�o�ʧ���   "
					<< NPC.getName() << "����Ԥ�Pokemon�Ѿl��q : ";
				NPC.getCurrentPokemon()->showStats(); // ��ܦ�q

				if (NPC.getCurrentPokemon()->getHP() <= 0) // ��@��Pokemon���`�A��ԼȰ�
					throw Dead(NPC, player); // �Y�X���`�ҥ~

				NPC.getCurrentPokemon()->attack(*player.getCurrentPokemon()); // ���۶ˮ`
				cout << "\n     " << NPC.getName() << "��" << NPC.getCurrentPokemon()->getName() << "��"
					<< player.getName() << "��" << player.getCurrentPokemon()->getName() << "�o�ʧ���   "
					<< player.getName() << "����Ԥ�Pokemon�Ѿl��q : ";
				player.getCurrentPokemon()->showStats(); // ��ܦ�q

				if (player.getCurrentPokemon()->getHP() <= 0) // ��@��Pokemon���`�A��ԼȰ�
					throw Dead(player, NPC); // �Y�X���`�ҥ~

				std::cout << "\n     ============================================================================================";
				cnt++; // �^�X�ƼW�[
			}
			else
			{
				std::cout << "\n\n     " << "Round " << cnt << "  "; // ��X�^�X��
				std::cout << "     " << NPC.getName() << "����" << std::endl; // ��X����

				NPC.getCurrentPokemon()->attack(*player.getCurrentPokemon()); // ���۶ˮ`
				cout << "\n     " << NPC.getName() << "��" << NPC.getCurrentPokemon()->getName() << "��"
					<< player.getName() << "��" << player.getCurrentPokemon()->getName() << "�o�ʧ���   "
					<< player.getName() << "����Ԥ�Pokemon�Ѿl��q : ";
				player.getCurrentPokemon()->showStats(); // ��ܦ�q

				if (player.getCurrentPokemon()->getHP() <= 0) // ��@��Pokemon���`�A��ԼȰ�
					throw Dead(player, NPC); // �Y�X���`�ҥ~

				player.getCurrentPokemon()->attack(*NPC.getCurrentPokemon()); // ���۶ˮ`
				cout << "\n     " << player.getName() << "��" << player.getCurrentPokemon()->getName() << "��"
					<< NPC.getName() << "��" << NPC.getCurrentPokemon()->getName() << "�o�ʧ���   "
					<< NPC.getName() << "����Ԥ�Pokemon�Ѿl��q : ";
				NPC.getCurrentPokemon()->showStats(); // ��ܦ�q

				if (NPC.getCurrentPokemon()->getHP() <= 0) // ��@��Pokemon���`�A��ԼȰ�
					throw Dead(NPC, player); // �Y�X���`�ҥ~

				std::cout << "\n     ============================================================================================" ;
				cnt++; // �^�X�ƼW�[
			}
			cout << "     ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			std::system("pause"); 
			system("cls"); // �M�ſù�
		}
		
		catch (Dead& dead)
		{
			dead.outputMessage(); // ��X�T��

			std::cout << "\n     ============================================================================================";
			cnt++; // �^�X�ƼW�[

			player.deadPokemon(); // �P�_���`
			NPC.deadPokemon(); // �P�_���`

			cout << "     ";
			std::fflush(stdout);
			rlutil::setCursorVisibility(0);
			std::system("pause");
			system("cls"); // �M�ſù�
		}

		// ��@��Pokemon�����A��Ե���
		if (player.getCurrentPokemon() == nullptr || NPC.getCurrentPokemon() == nullptr)
		{
			string winner(player.getName());
			if (player.getCurrentPokemon() == nullptr) // �T�{Ĺ�a�m�W
			{
				winner = NPC.getName();
				win = 0;
			}
			// ��X�T��
			std::cout << endl << "     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" << endl;
			locate((105 - winner.length()) / 2, 5);
			std::cout << winner << " ���\n\n";
			std::cout << endl << "     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" << endl;
			
			if(winner == player.getName())
				for (int i = 0; i < Battle::win.size(); i++)
					cout << Battle::win[i] << endl; // ��X�ӧQ�T��
			else
				for (int i = 0; i < Battle::lose.size(); i++)
					cout << Battle::lose[i] << endl; // ��X���ѰT��
		}
	}

	std::cout << "\n\n\n                                            ";
	// �_�쯫�_�_�����A
	for (int i = 0; i < player.getPokemonBattleList().size(); i++)
		player.getPokemonBattleList()[i]->reset();
	for (int i = 0; i < NPC.getPokemonBattleList().size(); i++)
		NPC.getPokemonBattleList()[i]->reset();

	std::fflush(stdout);

	rlutil::setCursorVisibility(0);

	std::system("pause");

	return win; // �^�ǬO�_���
}

// �^�Ƕˮ`���v
template < typename T, typename Ty >
double Battle::getDamageRate(T atk, Ty def)
{
	Pokemon2* pokemons[2] = { &atk, &def };
	int Type[2] = { 0, 0 };

	for (int i(0); i < 2; i++) // �ھ������ݩʨM�w�ˮ`���v
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
	return damageRate[Type[0]][Type[1]]; // �^�Ƕˮ`���v
}