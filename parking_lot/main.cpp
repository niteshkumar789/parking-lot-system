/*  Folder
    
        parking-lot/
        ├─ core/
        │   ├─ Vehicle.h
        │   ├─ ParkingSpot.h
        │   ├─ Ticket.h
        │   └─ RateCalculator.h
        ├─ service/
        │   ├─ DisplayBoard.h
        │   ├─ ParkingFloor.h
        │   ├─ ParkingLot.h
        │   └─ Gate.h
        └─ main.cpp
*/

/*  Use Case

                    +------------------+
                |     Driver       |
                +------------------+
                    ^   ^    ^   ^
                    |   |    |   |
            +------+   |    |   +--------------+
            |          |    |                  |
        +-----------+  +-------------+  +--------------------+
        |  Park     |  |  Pay Fee    |  |  Leave Parking    |
        | Vehicle   |  |  (Cash/Card)|  |  (get receipt)    |
        +-----------+  +-------------+  +--------------------+
                    \    (uses)     /
                    \             /
                    +-----------+
                    | Get Ticket|
                    +-----------+

        Secondary actors: **Parking Agent**, **Auto-Pay Machine**

*/

/*  Class Diagram

        +----------------+          +------------------+      +---------------+
        |  ParkingLot    |<>------->|  ParkingFloor    |<>--->| ParkingSpot   |
        |----------------|1      *  |------------------|1  *  |---------------|
        | - name         |          | - floorNo        |      | - id          |
        | - capacity=40k |          | - spotsByType    |      | - isFree      |
        | - floors       |          |------------------|      | +parkVehicle()|
        | - entrances    |          | +getFreeCount()  |      | +removeVeh()  |
        | - exits        |          +------------------+      +---------------+
        | - displayBoard |                                    ^  ^   ^   ^
        |----------------|                                    |  |   |   |
        | +park(vehicle) |                                    |  |   |   |
        | +leave(ticket) |                                    |  |   |   |
        +--------^-------+                                    |  |   |   |
                |                                           ... Spot sub-classes
        +--------+--------+  +----------------------+      (Handicapped, Compact,
        | EntranceGate    |  |      Ticket          |       Large, Motorcycle)
        |-----------------|  |----------------------|
        | +generateTicket |  | ticketId, spotId     |      +------------+
        +-----------------+  | entryTime, paid, amt |<>----|  Vehicle   |
                            +----------------------+      |------------|
                                                            | plate, type|
                                                            +------------+
*/

/*  Activity Diagram

        [Start]→(Arrive Gate)
        ↓
        [Display free counts]←─DisplayBoard.update()
        ↓
        (Scan / press button to get ticket)
        ↓
        [Assign nearest free spot (type OK?)]
        ↓
        (Create Ticket, mark spot occupied, update board)
        ↓
        <<Ticket printed>>
        ↓
        [Driver parks car]
        ↓
        [End]
*/

#include "service/ParkingLot.h"

int main(){
    ParkingLot lot;

    // Build one floor with a few spots
    ParkingFloor f0(0);
    for(int i=0;i<2;i++) f0.addSpot(SpotType::COMPACT);
    f0.addSpot(SpotType::LARGE);
    lot.addFloor(std::move(f0));

    lot.displayAvailability();

    Vehicle car("DL-3C-5555", VehicleType::CAR);
    Ticket t = lot.parkVehicle(car);

    lot.displayAvailability();

    double due = lot.leaveParking(t.id);
    std::cout<<"Pay Rs "<<due<<"\n";

    lot.displayAvailability();
    return 0;
}

// g++ -std=c++11 main.cpp -o parking_lot

