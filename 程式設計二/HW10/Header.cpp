#include"Header.h"

Account::Account()
	: accountNumber(),
	PIN(),
	availableBalance(),
	totalBalance()
{
}

Account::Account(int accNum, int pin, double avaBal, double totBal)
	: accountNumber(accNum),
	PIN(pin),
	availableBalance(avaBal),
	totalBalance(totBal)
{
}

int Account::getAccountNumber() const
{
	return accountNumber;
}

int Account::getPIN() const
{
	return PIN;
}

double Account::getAvailableBalance() const
{
	return availableBalance;
}

double Account::getTotalBalance() const
{
	return totalBalance;
}

void Account::setAvailableBalance(double newBalance)
{
	availableBalance = newBalance;
}

void Account::setTotalBalance(double newBalance)
{
	totalBalance = newBalance;
}


ATM::ATM()
{
	Account account01(12345, 54321, 1000, 1200), account02(98765, 56789, 200, 200);
	account1 = account01;
	account2 = account02;
	cash = 500;// 500±i20¤¸
}

void ATM::run()
{
	Account* ap = nullptr;

	while (1)
	{
		int selectAccount = logIn(), choice(0);

		if (selectAccount == 1)
			ap = &account1;
		else if (selectAccount == 2)
			ap = &account2;
		else
			cout << endl << "Account number or password is wrong, please try again." << endl << endl;

		if (ap != nullptr)
		{
			while (1)
			{
				cout << "\nMain menu:"
					 << "\n1 - View my balance"
					 << "\n2 - Withdraw cash"
					 << "\n3 - Deposit funds"
					 << "\n4 - Exit\n"
					 << "\nEnter a choice: ";

				do {
					cin >> choice;
					if (choice > 4 || choice < 1)
						cout << endl << "Input error, please try again." << endl << endl << "Enter a choice : ";
				} while (choice > 4 || choice < 1);

				switch (choice)
				{
					case 1:
						viewBalance(*ap);
						break;
					case 2:
						withdrawCash(*ap);
						break;
					case 3:
						depositFunds(*ap);
						break;
					case 4:
						cout << "\nExiting the system...\n"
							 << "\nThank you!Goodbye!\n\n";
				}

				if (choice == 4)
					break;
			}
		}
		ap = nullptr;
	}
}

int ATM::logIn()
{
	cout << "Welcome!" << endl;

	int inputAccNum, inputPIN;

	cout << endl << "Please enter your account number: ";

	cin >> inputAccNum;

	cout << endl << "Enter your PIN: ";

	cin >> inputPIN;

	if (inputAccNum == account1.getAccountNumber() && inputPIN == account1.getPIN())
		return 1;
	else if (inputAccNum == account2.getAccountNumber() && inputPIN == account2.getPIN())
		return 2;
	else
		return 0;
}

void ATM::viewBalance(const Account& account)
{
	cout << "\nBalance Information:"
		 << "\n - Available balance : $" << fixed << setprecision(2) << account.getAvailableBalance()
		 << "\n - Total balance :     $" << fixed << setprecision(2) << account.getTotalBalance() << endl;
}

void ATM::withdrawCash(Account& account)
{
	int choice(0), amount(0);

	while (1)
	{
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
			return;

		switch (choice)
		{
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

		if (amount > account.getAvailableBalance())
		{
			cout << "\nSorry, the amount you entered is greater than the balance in your account, please enter a smaller amount.\n";
			continue;
		}
		else if (amount > cash * 20)
		{
			cout << "\nSorry, the amount you entered is greater than the cash stock in the cash machine, please enter a smaller amount.\n";
			continue;
		}
		else
			break;
	}
	
	account.setAvailableBalance(account.getAvailableBalance() - amount);
	account.setTotalBalance(account.getTotalBalance() - amount);
	cash -= (amount / 20);

	cout << "\nPlease take your cash from the cash dispenser.\n";
}

void ATM::depositFunds(Account& account)
{
	cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";

	double amount(0);

	cin >> amount;

	if (amount == 0)
		return;

	account.setTotalBalance(account.getTotalBalance() + (amount / 100));

	cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << (amount / 100) << " in the deposit slot.\n";

	cout << "\nYour envelope has been received."
		 << "\nNOTE: The money deposited will not be available until we"
		 << "\nverify the amount of any enclosed cash, and any enclosed checks clear\n";
}