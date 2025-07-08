#ifndef RATE_CALC_H
#define RATE_CALC_H
#include "ParkingSpot.h"

struct RateCalculator {
    static double hourlyRate(SpotType t) {
        switch(t){
            case SpotType::MOTORCYCLE:  return 10;
            case SpotType::COMPACT:     return 20;
            case SpotType::HANDICAPPED: return 15;
            case SpotType::LARGE:       return 30;
        }
        return 20;
    }
    static double computeFee(std::time_t start, std::time_t end, SpotType t) {
        double hours = (end - start) / 3600.0;
        if (hours < 1) hours = 1;
        return hourlyRate(t) * hours;
    }
};
#endif
