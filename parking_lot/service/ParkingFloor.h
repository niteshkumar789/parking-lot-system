#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include "../core/ParkingSpot.h"

class ParkingFloor {
    int floorNo;
    std::vector<ParkingSpot> spots;
public:
    explicit ParkingFloor(int num=0):floorNo(num){}
    void addSpot(SpotType t){ spots.emplace_back(spots.size()+1,t); }
    ParkingSpot* findSpot(VehicleType vt){
        for(auto &s:spots) if(s.isFree() && s.canFit(vt)) return &s;
        return nullptr;
    }
    int freeCount(SpotType t) const{
        int c=0; for(auto &s:spots) if(s.type==t && s.isFree()) ++c;
        return c;
    }
    void allFreeCounts(std::array<int,4>& acc) const{
        for(auto &s:spots) if(s.isFree()) acc[(int)s.type]++;
    }
};
#endif
