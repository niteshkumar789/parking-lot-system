#ifndef GATE_H
#define GATE_H
#include <map>
#include "../core/Ticket.h"
#include "../core/Vehicle.h"
#include "../core/RateCalculator.h"

class Gate {
protected:
    std::map<int, Ticket> openTickets;
public:
    Ticket& getTicket(int id){ return openTickets.at(id);}
};
#endif
