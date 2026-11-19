#include "MakingReservation.h"
#include "ReservationHistory.h"

int inputAnInteger(int begin, int end)
{
	/*string String;
	stringstream STRING;
	int number;
	getline(cin, String);
	STRING << String;
	STRING >> number;
	if (number >= begin && number <= end)
		return number;
	return -1;*/
	string String;

	cin >> String;

	if (String.size() == 1 && String[0] >= begin + 48 && String[0] <= end + 48)
		return String[0] - 48;
	if (String.size() == 2 && (String[0] - 48) * 10 + String[1] >= begin + 48 && (String[0] - 48) * 10 + String[1] <= end + 48)
		return (String[0] - 48) * 10 + String[1] - 48;
	if (String.size() == 3 && (String[0] - 48) * 100 + (String[1] - 48) * 10 + String[2] >= begin + 48 && (String[0] - 48) * 100 + (String[1] - 48) * 10 + String[2] <= end + 48)
		return (String[0] - 48) * 100 + (String[1] - 48) * 10 + String[2] - 48;
	if (String.size() == 4 && (String[0] - 48) * 1000 + (String[1] - 48) * 100 + (String[2] - 48) * 10 + String[3] >= begin + 48 && (String[0] - 48) * 1000 + (String[1] - 48) * 100 + (String[2] - 48) * 10 + String[3] <= end + 48)
		return (String[0] - 48) * 1000 + (String[1] - 48) * 100 + (String[2] - 48) * 10 + String[3] - 48;

	return -1;
}

void makingReservation()
{
	MakingReservation making_Reservation;
	making_Reservation.execute();
}

void reservationHistory()
{
	ReservationHistory reservation_History;
	reservation_History.execute();
}

int main()
{
	cout << "Taiwan High Speed Rail Booking System\n";
	srand(static_cast<unsigned int>(time(0)));

	int choice; 

	while (true)
	{
		cout << "\nEnter Your Choice\n"
			<< "1. Booking\n"
			<< "2. Booking History\n"
			<< "3. End Program";

		do cout << "\n? ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		if (choice == 1)
			makingReservation();
		else if (choice == 2)
			reservationHistory();
		else if (choice == 3)
		{
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;
		}
		else
			cerr << "Incorrect Choice!\n";
	}

	system("pause");
}