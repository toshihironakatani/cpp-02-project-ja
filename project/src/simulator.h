#pragma once

#include <string>

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
    int millisecondsDelay;
};