#ifndef LOT_H
#define LOT_H
#include <vector>
#include <memory>
#include "../core/Vehicle.h"
#include "../core/ParkingSpot.h"
#include "ParkingFloor.h"
#include "DisplayBoard.h"
#include "Gate.h"

class EntranceGate : public Gate {
    int nextTicket=1;
public:
    Ticket issueTicket(int spotId){
        Ticket t{nextTicket++, spotId, std::time(nullptr)};
        openTickets[t.id]=t;
        return t;
    }
};

class ExitGate : public Gate {
public:
    double closeTicket(int id, std::time_t outTime, SpotType st){
        Ticket &t = openTickets.at(id);
        t.amount = RateCalculator::computeFee(t.inTime,outTime,st);
        t.paid   = true;
        return t.amount;
    }
};

class ParkingLot {
    int capacity;
    std::vector<ParkingFloor> floors;
    DisplayBoard board;
    EntranceGate entrance;
    ExitGate exit;
public:
    explicit ParkingLot(int cap=40000):capacity(cap){}
    void addFloor(ParkingFloor f){ floors.push_back(std::move(f)); refreshBoard(); }

    // === main workflow ===
    Ticket parkVehicle(Vehicle &v){
        for(auto &f: floors){
            if(auto *s=f.findSpot(v.getType())){
                s->park();
                refreshBoard();
                return entrance.issueTicket(s->getId());
            }
        }
        throw std::runtime_error("Lot Full");
    }
    double leaveParking(int ticketId){
        Ticket &t = entrance.getTicket(ticketId); // same map shared
        ParkingSpot *spot = findSpotById(t.spotId);
        spot->leave();
        refreshBoard();
        return exit.closeTicket(ticketId,std::time(nullptr),spot->type);
    }
    void displayAvailability() const { board.show(); }

private:
    void refreshBoard(){
        std::array<int,4> counts{0,0,0,0};
        for(auto &f:floors) f.allFreeCounts(counts);
        for(int i=0;i<4;++i) board.setFree((SpotType)i, counts[i]);
    }
    ParkingSpot* findSpotById(int id){
        for(auto &f:floors)
            for(auto &s:const_cast<std::vector<ParkingSpot>&>(reinterpret_cast<const ParkingFloor&>(f).spots))
                if(s.getId()==id) return &s;
        return nullptr;
    }
};
#endif
