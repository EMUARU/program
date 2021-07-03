// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

#define leftN (northboundTimetable[k].getDepartureTimes(13 - originStation))
#define right (departureTimes[departureTime])

extern string departureTimes[ 37 ];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
	ifstream in("Northbound timetable.dat", ios::in | ios::binary);

	if (!in)
	{
		ofstream in("Northbound timetable.dat", ios::out | ios::binary);
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
			northboundTimetable.push_back(temp);
		}
		in.close();
	}
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
	bool available(0);

	for (int j(0), k(0); j < 10 && k < northboundTimetable.size(); k++)
		if (northboundTimetable[k].getDepartureTimes(13 - originStation).length() > 1 && northboundTimetable[k].getDepartureTimes(13 - destinationStation).length() > 1)
			if ((leftN[0] * 10 + leftN[1]) * 60 + (leftN[3] * 10 + leftN[4]) >= (right[0] * 10 + right[1]) * 60 + (right[3] * 10 + right[4]))
			{
				available = 1;
				break;
			}

	return available;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
	vector< Train > departure;

	for (int j(0), k(0); j < 10 && k < northboundTimetable.size(); k++)
		if (northboundTimetable[k].getDepartureTimes(13 - originStation).length() > 1 && northboundTimetable[k].getDepartureTimes(13 - destinationStation).length() > 1)
			if ((leftN[0] * 10 + leftN[1]) * 60 + (leftN[3] * 10 + leftN[4]) >= (right[0] * 10 + right[1]) * 60 + (right[3] * 10 + right[4]))
			{
				departure.push_back(northboundTimetable[k]);
				j++;
			}

	for (int i(0); i < departure.size(); i++)
		std::cout << endl << setw(9) << departure[i].getTrainNumber()
		<< setw(11) << departure[i].getDepartureTimes(13 - originStation)
		<< setw(9) << departure[i].getDepartureTimes(13 - destinationStation);
}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}