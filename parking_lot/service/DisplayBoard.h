#ifndef DISPLAY_H
#define DISPLAY_H

#include "../core/ParkingSpot.h"
#include <array>
#include <iostream>

class DisplayBoard {
    // idx order == SpotType enum order
    std::array<int,4> freeCount;
public:
    DisplayBoard() { freeCount.fill(0); }
    void setFree(SpotType t, int n){ freeCount[(int)t] = n; }

    void show() const {
        std::cout<<"=== Availability ===\n";
        std::cout<<"Handicapped: "<<freeCount[0]<<"\n"
                 <<"Compact    : "<<freeCount[1]<<"\n"
                 <<"Large      : "<<freeCount[2]<<"\n"
                 <<"Motorcycle : "<<freeCount[3]<<"\n";
    }
};
#endif
