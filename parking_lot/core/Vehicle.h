#ifndef VEHICLE_H
#define VEHICLE_H
#include <ctime>
#include <string>

enum class VehicleType { CAR, TRUCK, VAN, MOTORCYCLE };

class Vehicle {
    std::string plate;
    std::time_t entryTime;
    VehicleType type;
    
    public:
        Vehicle(std::string p, VehicleType t) : plate(std::move(p)), entryTime(std::time(nullptr)), type(t) {
            
        }

        VehicleType getType() const { 
            return type;  
        }

        std::time_t getEntry() const { 
            return entryTime; 
        }

        const std::string& getPlate() const { 
            return plate; 
        }
};

#endif
