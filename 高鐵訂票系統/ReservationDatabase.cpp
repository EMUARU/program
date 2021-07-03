// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

extern int inputAnInteger(int begin, int end);

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
	ifstream in("Reservation details.dat", ios::in | ios::binary);

	if (!in)
	{
		ofstream in("Reservation details.dat", ios::out | ios::binary);
		in.close();
	}
	else
	{
		Reservation temp;

		in.seekg(0, ios::end);
		int end = in.tellg();

		in.seekg(0, ios::beg);
		int times = end / sizeof(Reservation);

		for (int i(1); i <= times; i++)
		{
			in.read(reinterpret_cast<char*> (&temp), sizeof(Reservation));
			reservations.push_back(temp);
		}
		in.close();
	}
}

void ReservationDatabase::storeReservations()
{
	ofstream out("Reservation details.dat", ios::out | ios::binary);

	for (int i(0); i < reservations.size(); i++)
		out.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));

	out.close();
}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "Reservation Cancelled.\n\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
	vector< Reservation >::iterator it = searchReservation(idNumber, reservationNumber);

	int choice1, choice2;

	do cout << "\nHow many adult tickets to cancel¡H";
	while ((choice1 = inputAnInteger(0, it->getAdultTickets())) == -1);
	cout << endl;

	do cout << "\nHow many concession tickets to cancel¡H";
	while ((choice2 = inputAnInteger(0, it->getConcessionTickets())) == -1);
	cout << endl;

	it->setAdultTickets(it->getAdultTickets() - choice1);
	it->setConcessionTickets(it->getConcessionTickets() - choice2);

	it->displayReservationDetails();

	if (it->getAdultTickets() + it->getConcessionTickets() == 0)
		reservations.erase(it);

	cout << "\nYou have successfully reduced the number of tickets!\n";
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}