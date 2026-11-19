#include<iomanip>
#include <iostream>
#include"BalanceInquiry.h"

BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account >& atmAccounts)
	:accounts(atmAccounts),
	accountNumber(userAccountNumber)
{
}

void BalanceInquiry::execute()
{
	cout << "\nBalance Information:"
		<< "\n - Available balance : $" << fixed << setprecision(2) << getAccount(accountNumber, accounts)->getAvailableBalance()
		<< "\n - Total balance :     $" << fixed << setprecision(2) << getAccount(accountNumber, accounts)->getTotalBalance() << endl;
}

Account* BalanceInquiry::getAccount(int accountNumber, vector< Account >& accounts)
{
	Account* p = 0;

	for (int i(0); i < accounts.size(); i++)
		if (accounts[i].getAccountNumber() == accountNumber)
			p = &accounts[i];

	return p;
}