#include "Reservation.h"
#include <cmath>
// top-right: ticket fares for business car, bottom-left: ticket fares for standard car
int Reservations::adultTicketPrice[13][13] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char Reservations::departureTimes[37][8] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "", "" };

char Reservations::stations[13][12] = { "Nangang", "Taipei", "Banqiao", "Tauyuan", "Hsinchu", "Miaoli",
						                "Taichung", "Changhua", "Yunlin", "Chiayi", "Tainan", "Zuoying" };

char Reservations::carClass[3][12] = { "Standard", "Business" };

Reservations::Reservations()
{
	loadSouthboundTimetable();
	loadNorthboundTimetable();
	loadReservationList();
}

void Reservations::loadSouthboundTimetable()
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
	

void Reservations::loadNorthboundTimetable()
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

void Reservations::loadReservationList()
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
			reservationList.push_back(temp);
		}
		in.close();
	}
}

void Reservations::saveReservation(Reservation reservation)
{
	ofstream out("Reservation details.dat", ios::app | ios::binary);

	out.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));

	out.close();
}

void Reservations::display(Reservation reservation, int trainTimetable)
{
	vector< Reservations::Train > TrainTimetable;

	if(trainTimetable == 1)
		TrainTimetable = getSouthboundTimetable();
	else
		TrainTimetable = getNorthboundTimetable();

	int cost, number, train(0);

	int OriginStation, DestinationStation;

	if (reservation.originStation > reservation.destinationStation)
		(OriginStation = reservation.originStation, DestinationStation = reservation.destinationStation, number = 13);
	else
		(DestinationStation = reservation.originStation, OriginStation = reservation.destinationStation, number = 0);

	if (number == 13)
	{
		for (int i(0); i < getNorthboundTimetable().size(); i++)
			if (!strcmp(getNorthboundTimetable()[i].trainNumber, reservation.trainNumber))
			{
				train = i;
				break;
			}
	}
	else
	{
		for (int i(0); i < getSouthboundTimetable().size(); i++)
			if (!strcmp(getSouthboundTimetable()[i].trainNumber, reservation.trainNumber))
			{
				train = i;
				break;
			}
	}
	
	std::cout << "      Date  Train No.      From        To  Departure  Arrival   Adult  Concession    Fare     Class" << endl

		<< right << setw(10) << reservation.date << setw(11) << reservation.trainNumber << setw(10) << stations[reservation.originStation - 1]

		<< setw(10) << stations[reservation.destinationStation - 1] << setw(11) << TrainTimetable[train].departureTimes[abs(number - reservation.originStation)]

		<< setw(9) << TrainTimetable[train].departureTimes[abs(number - reservation.destinationStation)] << "   "

		<< (cost = (reservation.carClass == 1) ? adultTicketPrice[OriginStation][DestinationStation] : adultTicketPrice[DestinationStation][OriginStation])

		<< '*' << reservation.adultTickets << "       " << cost / 2 << '*' << reservation.concessionTickets << "  "

		<< setw(6) << cost * reservation.adultTickets + cost / 2 * reservation.concessionTickets

		<< setw(10) << carClass[reservation.carClass - 1];
}

int Reservations::inputAnInteger(int begin, int end)
{
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

vector< Reservations::Train > Reservations::getSouthboundTimetable()
{
	return southboundTimetable;
}

vector< Reservations::Train > Reservations::getNorthboundTimetable()
{
	return northboundTimetable;
}

vector< Reservations::Reservation >& Reservations::getReservationList()
{
	return reservationList;
}

const int Reservations::getAdultTicketPrice(int x, int y)
{
	return adultTicketPrice[x][y];
}

const char* Reservations::getDepartureTimes(int x)
{
	return departureTimes[x];
}

const char* Reservations::getStations(int x)
{
	return stations[x];
}

const char* Reservations::getCarClass(int x)
{
	return carClass[x];
}
