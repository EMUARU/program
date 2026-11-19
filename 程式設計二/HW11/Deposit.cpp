#include<iostream>
#include<iomanip>
#include"Deposit.h"

Deposit::Deposit(int userAccountNumber, vector< Account >& atmAccounts)
	:accounts(atmAccounts),
	accountNumber(userAccountNumber),
	amount()
{
}

void Deposit::execute()
{
	amount = promptForDepositAmount();

	if (amount == 0)
		return;

	getAccount(accountNumber, accounts)->credit(amount / 100);

	cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << (amount / 100) << " in the deposit slot.\n";

	cout << "\nYour envelope has been received."
		<< "\nNOTE: The money deposited will not be available until we"
		<< "\nverify the amount of any enclosed cash, and any enclosed checks clear\n";
}

Account* Deposit::getAccount(int accountNumber, vector< Account >& accounts)
{
	Account* p = 0;

	for (int i(0); i < accounts.size(); i++)
		if (accounts[i].getAccountNumber() == accountNumber)
			p = &accounts[i];

	return p;
}

double Deposit::promptForDepositAmount() const
{
	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";

	double amount(0);
	cin >> amount;

	return amount;
}