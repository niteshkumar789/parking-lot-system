#ifndef TICKET_H
#define TICKET_H
#include <ctime>

struct Ticket {
    int id, spotId;
    std::time_t inTime;
    double amount{0};
    bool paid{false};
};

#endif
