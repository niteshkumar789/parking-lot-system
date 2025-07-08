#ifndef PARKING_SPOT_H
#define PARKING_SPOT_H
#include "Vehicle.h"

enum class SpotType { 
    HANDICAPPED, COMPACT, LARGE, MOTORCYCLE 
};

class ParkingSpot {
    protected:
        int id; bool free;
    public:
        SpotType type;
        explicit ParkingSpot(int i, SpotType t) : id(i), free(true), type(t) {}
        bool isFree() const { return free; }
        int  getId()  const { return id;   }

        bool canFit(VehicleType vt) const {
            if (type == SpotType::MOTORCYCLE)  return vt == VehicleType::MOTORCYCLE;
            if (type == SpotType::COMPACT)     return vt == VehicleType::CAR;
            if (type == SpotType::HANDICAPPED) return vt == VehicleType::CAR;
            return true; // LARGE fits all
        }
        bool park()   { if (!free) return false; free=false; return true; }
        void leave()  { free=true; }
};

#endif
