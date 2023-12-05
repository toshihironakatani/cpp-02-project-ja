#include "simulator.h"
#include <fstream>
#include <sstream>

std::ifstream openFile(const std::string& filename);

Simulator::Simulator(int millisecondsDelay) : millisecondsDelay(millisecondsDelay) {}

void Simulator::initializeFromFile(const std::string& filename) {
    auto file { openFile(filename) };
    parseElevators(file);
    parsePassengers(file);
    parseInputs(file);
}

std::ifstream openFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Exception! Cannot open file!");
    }

    return file;
}

void Simulator::parseElevators(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss { line };

    int numberOfElevators {};
    int numberOfFloors {};
    int elevatorCapacity {};

    if (!(iss >> numberOfElevators >> numberOfFloors >> elevatorCapacity)) {
        throw std::runtime_error("Exception! Cannot parse the first line of the file!");
    }
}

void Simulator::parsePassengers(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss { line };

    int numberOfPassengers {};

    if (!(iss >> numberOfPassengers)) {
        throw std::runtime_error("Exception! Cannot parse the number of passengers!");
    }

    while (numberOfPassengers-- && std::getline(file, line)) {
        iss = std::istringstream { line };

        int id;
        int weight;

        if (!(iss >> id >> weight)) {
            throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
        }
    }
}

void Simulator::parseInputs(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        auto iss = std::istringstream { line };

        int time {};
        int id {};
        int pickUpFloor {};
        int dropOffFloor {};

        if (!(iss >> time >> id >> pickUpFloor >> dropOffFloor)) {
            throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
        }
    }
}

void Simulator::run() {}