// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n\n";
   }
   else
      cout << "\nSorry! No train is available!\n\n";
}

bool MakingReservation::chooseTrain()
{
	int number, departureTime;

	do
	{
		do{
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
			reservation.setOriginStation(number = inputAnInteger(1, 12));
		}while (number == -1);

		do
		{
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
			reservation.setDestinationStation(number = inputAnInteger(1, 12));
		} while (number == -1);

	} while (reservation.getOriginStation() == reservation.getDestinationStation());


	do
	{
		std::cout << "\nDeparture Time\n";
		for (int i(1); i < 37; i++)
			std::cout << setw(2) << i << ". " << departureTimes[i] << endl;
		std::cout << '?';
	} while ((departureTime = inputAnInteger(1, 37
	)) == -1);

	if (reservation.getOriginStation() < reservation.getDestinationStation())
		if (!southboundTimetable.trainsAvailable(departureTime, reservation.getOriginStation(), reservation.getDestinationStation())) 
			return false;


	if (reservation.getOriginStation() > reservation.getDestinationStation())
		if (!northboundTimetable.trainsAvailable(departureTime, reservation.getOriginStation(), reservation.getDestinationStation()))
			return false;
	
	string temp("");

	if (reservation.getOriginStation() < reservation.getDestinationStation())
		southboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());
	else
		northboundTimetable.displayComingTrains(departureTime, reservation.getOriginStation(), reservation.getDestinationStation());

	std::cout << "\n\nEnter Train Number: ";
	cin >> temp;
	reservation.setTrainNumber(temp);
	
	return true;
}	

void MakingReservation::inputReservationDetails()
{
	int car(0);

	if (reservation.getOriginStation() + reservation.getDestinationStation() == 3 || reservation.getOriginStation() + reservation.getDestinationStation() == 4 || (reservation.getOriginStation() == 2 && reservation.getDestinationStation() == 3) || (reservation.getOriginStation() == 3 && reservation.getDestinationStation() == 2))
	{
		do {
			   std::cout << "\nDestination  Station"
			   << "\n1. Standard Car"
			   << "\n?";
			   reservation.setCarClass(car = inputAnInteger(1, 1));
		} while (car == -1);
	}
	else
	{
		do {
			   std::cout << "\nDestination  Station"
			   << "\n1. Standard Car"
			   << "\n2. Business Car"
			   << "\n?";
			   reservation.setCarClass(car = inputAnInteger(1, 2));
		} while (car == -1);
	}
	   
   cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\n\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}