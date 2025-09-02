# parking-lot-system

🚗 A low level design of parking lot system (LLD in C++)

This project is a Low-Level Design (LLD) implementation of a Parking Lot system in C++.
It demonstrates Object-Oriented Design (OOD) principles like encapsulation, inheritance, and composition to model a real-world parking lot.

📂 Project Structure

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

📌 Features

    🅿️ Parking Spot Allocation based on vehicle type (Car, Motorcycle, etc.)
    🎫 Ticketing System for each parked vehicle
    💰 Rate Calculation based on duration & spot type
    📊 Display Board showing available spots by type
    🚪 Entrance & Exit Gates for issuing and closing tickets
    🏢 Multiple Floors Support in Parking Lot

🏗️ Design Overview

    ✅ Use Case
        . Primary Actor: Driver
        . Secondary Actors: Parking Agent, Auto-Pay Machine

    ✅ Class Diagram (simplified)
        . ParkingLot → ParkingFloor → ParkingSpot
        . ParkingLot → EntranceGate / ExitGate
        . ParkingLot → DisplayBoard
        . Ticket ↔ Vehicle

    ✅ Activity Flow
        . Driver arrives at Entrance Gate
        . DisplayBoard shows availability
        . Driver requests a ticket → nearest free spot assigned
        . Vehicle parks & spot marked occupied
        . On exit, driver pays fee → ticket closed
        . Spot marked free & DisplayBoard updated

🖥️ Example Run

    #include "service/ParkingLot.h"
    int main() {
        ParkingLot lot;

        // Build one floor with a few spots
        ParkingFloor f0(0);
        for(int i=0; i<2; i++) f0.addSpot(SpotType::COMPACT);
        f0.addSpot(SpotType::LARGE);
        lot.addFloor(std::move(f0));

        lot.displayAvailability();

        Vehicle car("DL-3C-5555", VehicleType::CAR);
        Ticket t = lot.parkVehicle(car);

        lot.displayAvailability();

        double due = lot.leaveParking(t.id);
        std::cout << "Pay Rs " << due << "\n";

        lot.displayAvailability();
        return 0;
    }

✅ Sample Output

    === Availability ===
    Handicapped: 0
    Compact    : 2
    Large      : 1
    Motorcycle : 0

    === Availability ===
    Handicapped: 0
    Compact    : 1
    Large      : 1
    Motorcycle : 0

    Pay Rs 20

    === Availability ===
    Handicapped: 0
    Compact    : 2
    Large      : 1
    Motorcycle : 0

📊 Sequence Diagram

    Here’s a PlantUML sequence diagram of the workflow:

    @startuml
    actor Driver
    Driver -> EntranceGate : requestTicket(vehicle)
    EntranceGate -> ParkingLot : assignSpot(vehicle)
    ParkingLot -> ParkingFloor : findSpot(vehicleType)
    ParkingFloor --> ParkingLot : free spot
    ParkingLot -> ParkingSpot : park()
    ParkingLot -> EntranceGate : issueTicket()
    EntranceGate --> Driver : Ticket

    == Exit Flow ==
    Driver -> ExitGate : presentTicket(ticketId)
    ExitGate -> ParkingLot : freeSpot(ticket.spotId)
    ParkingLot -> ParkingSpot : leave()
    ExitGate -> RateCalculator : computeFee(start, end, spotType)
    RateCalculator --> ExitGate : fee
    ExitGate --> Driver : amountDue
    @enduml

    You can visualize it by pasting the above code into:
    👉 PlantText UML Editor or any PlantUML-supported tool.


⚙️ Build & Run

    g++ -std=c++11 main.cpp -o parking_lot
    ./parking_lot

🚀 Future Enhancements

    Support for online payments / wallets
    Reservation system for advance bookings
    Integration with cameras & license plate recognition
    REST API for real-time parking availability

📜 License

    This project is open-source under the MIT License.

