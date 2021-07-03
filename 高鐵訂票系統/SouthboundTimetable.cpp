// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

#define leftS (southboundTimetable[k].getDepartureTimes(originStation))
#define right (departureTimes[departureTime]) 

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
	ifstream in("Southbound timetable.dat", ios::in | ios::binary);

	if (!in)
	{
		ofstream in("Southbound timetable.dat", ios::out | ios::binary);
		in.close();
	}
	else
	{
		Train temp;

		in.seekg(0, ios::end);
		int end = in.tellg();

		in.seekg(0, ios::beg);
		int times = end / sizeof(Train);

		for (int i(1); i <= times; i++)
		{
			in.read(reinterpret_cast<char*> (&temp), sizeof(Train));
			southboundTimetable.push_back(temp);
		}
		in.close();
	}
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
	bool available(0);

	for (int j(0), k(0); k < southboundTimetable.size(); k++)
		if (southboundTimetable[k].getDepartureTimes(originStation).length() > 1 && southboundTimetable[k].getDepartureTimes(destinationStation).length() > 1)
			if ((leftS[0] * 10 + leftS[1]) * 60 + (leftS[3] * 10 + leftS[4]) >= (right[0] * 10 + right[1]) * 60 + (right[3] * 10 + right[4]))
			{
				available = 1;
				break;
			}
		
	return available;
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
	vector< Train > departure;

	for (int j(0), k(0); j < 10 && k < southboundTimetable.size(); k++)
		if (southboundTimetable[k].getDepartureTimes(originStation).length() > 1 && southboundTimetable[k].getDepartureTimes(destinationStation).length() > 1)
			if ((leftS[0] * 10 + leftS[1]) * 60 + (leftS[3] * 10 + leftS[4]) >= (right[0] * 10 + right[1]) * 60 + (right[3] * 10 + right[4]))
			{
				departure.push_back(southboundTimetable[k]);
				j++;
			}

	for (int i(0); i < departure.size(); i++)
		std::cout << endl << setw(9) << departure[i].getTrainNumber()
		<< setw(11) << departure[i].getDepartureTimes(originStation)
		<< setw(9) << departure[i].getDepartureTimes(destinationStation);
}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}