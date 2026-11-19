#include<iostream>
#include<iomanip>
#include"Withdrawal.h"

Withdrawal::Withdrawal(int userAccountNumber, vector< Account >& atmAccounts, int& atmRemainingBills)
	:accounts(atmAccounts),
	remainingBills(atmRemainingBills),
	accountNumber(userAccountNumber),
	amount()
{
}

void Withdrawal::execute()
{
	switch (displayMenuOfAmounts())
	{
	case 0:
		return;
	case 1:
		amount = 20;
		break;
	case 2:
		amount = 40;
		break;
	case 3:
		amount = 60;
		break;
	case 4:
		amount = 100;
		break;
	case 5:
		amount = 200;
	}

	if (amount > getAccount(accountNumber, accounts)->getAvailableBalance())
	{
		cout << "\nSorry, the amount you entered is greater than the balance in your account, please enter a smaller amount.\n";
		return;
	}
	else if (amount > remainingBills * 20)
	{
		cout << "\nSorry, the amount you entered is greater than the cash stock in the cash machine, please enter a smaller amount.\n";
		return;
	}

	getAccount(accountNumber, accounts)->debit(amount);
	remainingBills -= (amount / 20);

	cout << "\nPlease take your cash from the cash dispenser.\n";
}

Account* Withdrawal::getAccount(int accountNumber, vector< Account >& accounts)
{
	Account* p = 0;

	for (int i(0); i < accounts.size(); i++)
		if (accounts[i].getAccountNumber() == accountNumber)
			p = &accounts[i];

	return p;
}

int Withdrawal::displayMenuOfAmounts() const
{
	int choice(0);

	cout << "\nWithdrawal options:"
		<< "\n1 - $20"
		<< "\n2 - $40"
		<< "\n3 - $60"
		<< "\n4 - $100"
		<< "\n5 - $200"
		<< "\n6 - Cancel transaction\n"
		<< "\nChoose a withdrawal option(1 - 6) : ";

	do {
		cin >> choice;
		if (choice > 6 || choice < 1)
			cout << endl << "Input error, please try again." << endl << endl << "Enter a choice : ";
	} while (choice > 6 || choice < 1);

	if (choice == 6)
		return 0;

	return choice;
}