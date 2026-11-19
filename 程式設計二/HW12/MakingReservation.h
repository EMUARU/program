#pragma once
#include "Reservation.h"

class MakingReservation : public Reservations
{
public:
	MakingReservation();
	void inputReservationDetails();
	bool selectSouthboundTrain();
	bool selectNorthboundTrain();
	void inputContactInfo();
	void execute();
private:
	Reservation newReservation = {};
	int departureTime = 0;
};