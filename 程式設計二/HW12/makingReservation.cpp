#include "MakingReservation.h"

#define leftS (getSouthboundTimetable()[k].departureTimes[newReservation.originStation])
#define leftN (getNorthboundTimetable()[k].departureTimes[13 - newReservation.originStation])
#define right (getDepartureTimes(departureTime)) 
#define legalTimeS (getSouthboundTimetable()[k].departureTimes[newReservation.destinationStation][0] != '-' && getSouthboundTimetable()[k].departureTimes[newReservation.originStation][0] != '-')
#define legalTimeN (getNorthboundTimetable()[k].departureTimes[13 - newReservation.destinationStation][0] != '-' && getNorthboundTimetable()[k].departureTimes[13 - newReservation.originStation][0] != '-')

MakingReservation::MakingReservation()
	:Reservations(),
	newReservation()
{
}

void MakingReservation::inputReservationDetails()
{
	do
	{
		do
			std::cout << "\nOrigin Station"
				<< "\n1. Nangang"
				<< "\n2. Taipei"
				<< "\n3. Banqiao"
				<< "\n4. Taoyuan"
				<< "\n5. Hsinchu"
				<< "\n6. Miaoli"
				<< "\n7. Taichung"
				<< "\n8. Changhua"
				<< "\n9. Yunlin"
				<< "\n10. Chiayi"
				<< "\n11. Tainan"
				<< "\n12. Zuoying"
				<< "\n?";
		while ((newReservation.originStation = inputAnInteger(1, 12)) == -1);

		do
			std::cout << "\nDestination  Station"
				<< "\n1. Nangang"
				<< "\n2. Taipei"
				<< "\n3. Banqiao"
				<< "\n4. Taoyuan"
				<< "\n5. Hsinchu"
				<< "\n6. Miaoli"
				<< "\n7. Taichung"
				<< "\n8. Changhua"
				<< "\n9. Yunlin"
				<< "\n10. Chiayi"
				<< "\n11. Tainan"
				<< "\n12. Zuoying"
				<< "\n?";
		while ((newReservation.destinationStation = inputAnInteger(1, 12)) == -1);

	} while (newReservation.originStation == newReservation.destinationStation);

	int originStation = newReservation.originStation, destinationStation = newReservation.destinationStation;

	if (originStation + destinationStation == 3 || originStation + destinationStation == 4 || (originStation == 2 && destinationStation == 3) || (originStation == 3 && destinationStation == 2))
		do
			std::cout << "\nDestination  Station"
				<< "\n1. Standard Car"
				<< "\n?";
		while ((newReservation.carClass = inputAnInteger(1, 1)) == -1);
	else
		do
			std::cout << "\nDestination  Station"
				<< "\n1. Standard Car"
				<< "\n2. Business Car"
				<< "\n?";
		while ((newReservation.carClass = inputAnInteger(1, 2)) == -1);
		
	std::cout << "\nDeparture Date: ";
	cin >> newReservation.date;

	do
	{
		std::cout << "\nDeparture Time\n";
		for (int i(1); i < 35; i++)
			std::cout << setw(2) << i << ". " << getDepartureTimes(i) << endl;
		std::cout << '?';
	} while ((departureTime = inputAnInteger(1, 34)) == -1);

	do
	{
		do
			std::cout << "\nHow many adult tickets? ";
		while ((newReservation.adultTickets = inputAnInteger(0, 9999)) == -1);

		do
			std::cout << "\nHow many concession tickets? ";
		while ((newReservation.concessionTickets = inputAnInteger(0, 9999)) == -1);

	} while ((newReservation.adultTickets + newReservation.concessionTickets) == 0);
}

bool MakingReservation::selectSouthboundTrain()
{
	Train departure[11] = {};

	for (int j(0), k(0); j < 10 && k < getSouthboundTimetable().size(); k++)
		if ((leftS[0] * 10 + leftS[1]) * 60 + (leftS[3] * 10 + leftS[4]) >= (right[0] * 10 + right[1]) * 60 + (right[3] * 10 + right[4]) && legalTimeS)
		{
			departure[j] = getSouthboundTimetable()[k];
			j++;
		}

	if (departure[0].trainNumber[0] == 0)
		return 1;

	std::cout << "\nTrain No.  Departure  Arrival ";

	for (int i(0); i < 10; i++)
		std::cout << endl << setw(9) << departure[i].trainNumber
		<< setw(11) << departure[i].departureTimes[newReservation.originStation] 
		<< setw(9) << departure[i].departureTimes[newReservation.destinationStation];

	char temp[8] = {};

	do {
		std::cout << "\nEnter Train Number: ";

		for (int i(0); i < 8; i++)
			temp[i] = 0;
		cin >> temp;

		for (int i(0); i < 10; i++)
			if (!strcmp(temp, departure[i].trainNumber))
			{
				strcpy_s(newReservation.trainNumber, temp);
				break;
			}

	} while (!strcmp("", newReservation.trainNumber));

	std::cout << "\nTrip Details\n";

	display(newReservation, 1);

	return 0;
}

bool MakingReservation::selectNorthboundTrain()
{
	Train departure[11] = {};

	int j(0), k(0);

	for (; j < 10 && k < getNorthboundTimetable().size(); k++)
	{
		if ((leftN[0] * 10 + leftN[1]) * 60 + (leftN[3] * 10 + leftN[4]) >= (right[0] * 10 + right[1]) * 60 + (right[3] * 10 + right[4]) && legalTimeN)
		{
			departure[j] = getNorthboundTimetable()[k];
			j++;
		}
	}

	if (departure[0].trainNumber[0] == 0)
		return 1;

	cout << "Train No.  Departure  Arrival ";

	for (int i(0); i < 10; i++)
	{
		cout << endl << setw(9) << departure[i].trainNumber
			<< setw(11) << departure[i].departureTimes[13 - newReservation.originStation] 
			<< setw(9) << departure[i].departureTimes[13 - newReservation.destinationStation];
	}

	char temp[8] = {};

	do {
		std::cout << "\nEnter Train Number: ";

		for (int i(0); i < 8; i++)
			temp[i] = 0;
		cin >> temp;

		for (int i(0); i < 10; i++)
			if (!strcmp(temp, departure[i].trainNumber))
			{
				strcpy_s(newReservation.trainNumber, temp);
				break;
			}

	} while (!strcmp("", newReservation.trainNumber));

	std::cout << "\nTrip Details\n";

	display(newReservation, 2);

	return 0;
}

void MakingReservation::inputContactInfo()
{
	std::cout << "\nEnter Contact Person Information\n";

	std::cout << "\nID Number: ";
	cin >> newReservation.idNumber;

	std::cout << "\nPhone: ";
	cin >> newReservation.phone;

	std::cout << "\nReservation Number: ";

	for (int i(0); i < 8; i++)
		std::cout << (newReservation.reservationNumber[i] = (rand() % 10 + 48));

	std::cout << "\n\nReservation Completed!\n";
}

void MakingReservation::execute()
{
	bool noTrain(0);

	do{
		inputReservationDetails();

		if (newReservation.originStation < newReservation.destinationStation)
			noTrain = selectSouthboundTrain();
		else
			noTrain = selectNorthboundTrain();

		if (noTrain)
			cout << "\n沒有符合的班次，請重新輸入\n";

	} while (noTrain);

	inputContactInfo();
	saveReservation(newReservation);
}