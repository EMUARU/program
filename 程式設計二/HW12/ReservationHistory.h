#pragma once
#include "Reservation.h"

class ReservationHistory : public Reservations
{
public:
	ReservationHistory();
	bool existReservation();
	void saveReservations();
	void displayReservations();
	void reduceSeats();
	void reservationCancell();
	void execute();
private:
	Reservation changeReservation = {};
};
