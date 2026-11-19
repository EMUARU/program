#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstring>
using namespace std;

class Reservations
{
public:
	struct Train
	{
		char trainNumber[8] = {};          // used to identify a train  車次號碼
		char departureTimes[13][8] = {}; // the departure time of a train for each station,  火車在各站的離站時間
	};                             // departureTimes[0] is not used   departureTimes[0]未使用
	struct Reservation
	{
		char reservationNumber[12] = {}; // used to identify a reservation  訂位代號
		char trainNumber[8] = {};  // used to identify a train  車次號碼
		char idNumber[12] = {};    // the id number of the contact person  取票人的身分證字號
		char phone[12] = {};       // the (local or mobile) phone number of the contact person  取票人的聯絡電話
		char date[12] = {};        // outbound date  搭乘日期
		int originStation = 0;      // the origin station code  起程站代碼
		int destinationStation = 0; // the destination station code  到達站代碼
		int carClass = 0;           // the car class code; 1:standard car, 2:business car  車廂種類; 1:標準車廂, 2:商務車廂
		int adultTickets = 0;       // the number of adult tickets  全票張數
		int concessionTickets = 0;  // the number of concession tickets  優待票張數
	};
	Reservations();
	void loadSouthboundTimetable();
	void loadNorthboundTimetable();
	void loadReservationList();
	void saveReservation(Reservation reservation);
	void display(Reservation reservation, int trainTimetable);
	int inputAnInteger(int begin, int end);
	vector< Train > getSouthboundTimetable();
	vector< Train > getNorthboundTimetable();
	vector< Reservation >& getReservationList();
	const int getAdultTicketPrice(int x, int y);
	const char* getDepartureTimes(int x);
	const char* getStations(int x);
	const char* getCarClass(int x);
	virtual void execute() = 0;
private:
	vector< Train > southboundTimetable = {};
	vector< Train > northboundTimetable = {};
	vector< Reservation > reservationList = {};
	static int adultTicketPrice[13][13];
	static char departureTimes[37][8];
	static char stations[13][12];
	static char carClass[3][12];
};