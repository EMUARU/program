#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

class Account
{
	public:
		Account();
		Account(int, int, double, double);
		int getAccountNumber() const;
		int getPIN() const;
		double getAvailableBalance() const;
		double getTotalBalance() const;
		void setAvailableBalance(double);
		void setTotalBalance(double);
	private:
		int accountNumber;
		int PIN;
		double availableBalance;
		double totalBalance;
};

class ATM
{
	public:
		ATM();
		void run();
		int logIn();
		void viewBalance(const Account&);
		void withdrawCash(Account&);
		void depositFunds(Account&);
	private:
		int cash;
		Account account1;
		Account account2;
};