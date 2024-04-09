#pragma once

#include <string>
#include <vector>
#include <deque>

#include "building.hpp"
#include "passenger.hpp"

class Building;

struct CallPlan {
    int time;
    int id;
    int pick_up_floor;
    int drop_off_floor;
};

class Simulator {
public:
    Simulator(int millisecondsDelay);

public:
    void initializeFromFile(const std::string& filename);
    void run();
    void printResults() const;

private:
    void parseElevators(std::ifstream& file);
    void parsePassengers(std::ifstream& file);
    void parseInputs(std::ifstream& file);

private:
    int time = 0;
    int millisecondsDelay;
    Building* building;
    std::vector<Passenger*> passengers;
    std::deque<CallPlan> call_plans;
};
