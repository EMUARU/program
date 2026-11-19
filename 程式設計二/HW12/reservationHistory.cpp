#include "ReservationHistory.h"

ReservationHistory::ReservationHistory()
	:Reservations(),
	changeReservation()
{
}

bool ReservationHistory::existReservation()
{
	char temp1[12] = {}, temp2[12] = {};

	cout << "\nEnter ID Number: ";
	cin >> temp1;

	cout << "\nEnter Reservation Number: ";
	cin >> temp2;

	for (int i(0); i < getReservationList().size(); i++)
	{
		if (!strcmp(getReservationList()[i].idNumber, temp1) && !strcmp(getReservationList()[i].reservationNumber, temp2))
		{
			changeReservation = getReservationList()[i];
			return false;
		}

		if (i == getReservationList().size() - 1)
		{
			cout << "\nReservation record not found.\n";
			return true;
		}
	}
}

void ReservationHistory::saveReservations()
{
	ofstream out("Reservation details.dat", ios::out | ios::binary);

	for (int i(0); i < getReservationList().size(); i++)
		out.write(reinterpret_cast<const char*>(&getReservationList()[i]), sizeof(Reservation));
	
	out.close();
}

void ReservationHistory::displayReservations()
{
	cout << "\nReservation Details\n\n";

	display(changeReservation, (changeReservation.originStation < changeReservation.destinationStation) ? 1 : 2);
}

void ReservationHistory::reduceSeats()
{
	int choice1, choice2;

	do cout << "\nHow many adult tickets to cancel¡H";
	while ((choice1 = inputAnInteger(0, changeReservation.adultTickets)) == -1);
	cout << endl;

	do cout << "\nHow many concession tickets to cancel¡H";
	while ((choice2 = inputAnInteger(0, changeReservation.concessionTickets)) == -1);
	cout << endl;

	changeReservation.adultTickets -= choice1;
	changeReservation.concessionTickets -= choice2;

	displayReservations();

	if(changeReservation.adultTickets + changeReservation.concessionTickets > 0)
		getReservationList().push_back(changeReservation);

	cout << "\nYou have successfully reduced the number of tickets!\n";
}

void ReservationHistory::reservationCancell()
{
	for (int i(0); i < getReservationList().size(); i++)
		if (!strcmp(getReservationList()[i].idNumber, changeReservation.idNumber) && !strcmp(getReservationList()[i].reservationNumber, changeReservation.reservationNumber))
		{
			changeReservation = getReservationList()[i];
			getReservationList().erase(getReservationList().begin() + i);
		}
}

void ReservationHistory::execute()
{
	while(existReservation());

	displayReservations();

	int choice;

	cout << "\nEnter Your Choice\n"
		<< "1. Cancellation\n"
		<< "2. Reduce\n"
		<< "3. End";

	do cout << "\n? ";
	while ((choice = inputAnInteger(1, 3)) == -1);
	cout << endl;

	switch (choice)
	{
	case 1:
		reservationCancell();
		cout << "\nReservation Cancelled!\n";
		break;
	case 2:
		reservationCancell();
		reduceSeats();
	}
	saveReservations();
}