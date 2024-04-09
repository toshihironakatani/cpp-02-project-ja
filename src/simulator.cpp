#include "simulator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <deque>

#include "building.hpp"
#include "elevator.hpp"
#include "passenger.hpp"

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
    static std::vector<Elevator*> elevators;
    elevators.push_back(new Elevator());
    static Building building(numberOfFloors, elevatorCapacity, elevators);
    this->building = &building;
}

void Simulator::parsePassengers(std::ifstream& file) {
    std::string line;
    std::getline(file, line);
    std::istringstream iss { line };

    int numberOfPassengers {};

    if (!(iss >> numberOfPassengers)) {
        throw std::runtime_error("Exception! Cannot parse the number of passengers!");
    }

    static std::vector<Passenger*> passengers;

    while (numberOfPassengers-- && std::getline(file, line)) {
        iss = std::istringstream { line };

        int id;
        int weight;

        if (!(iss >> id >> weight)) {
            throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
        }
        passengers.push_back(new Passenger(id, weight));
    }
    this->passengers = passengers;
}

void Simulator::parseInputs(std::ifstream& file) {
    std::string line;

    static std::deque<CallPlan> call_plans;

    while (std::getline(file, line)) {
        auto iss = std::istringstream { line };

        int time {};
        int id {};
        int pickUpFloor {};
        int dropOffFloor {};

        if (!(iss >> time >> id >> pickUpFloor >> dropOffFloor)) {
            throw std::runtime_error("Exception! Cannot parse the remaining lines of the file!");
        }
        call_plans.push_back(CallPlan{time, id, pickUpFloor, dropOffFloor});
    }
    this->call_plans = call_plans;
}

void Simulator::run() {
    while(true){
        // inputファイルに従ってエレベータを呼ぶ
        if(call_plans[0].time == time) {
            auto c = call_plans[0];
            Call* call = new Call{c.id, c.pick_up_floor, c.drop_off_floor};
            building->add_call(call); //呼び出し情報を追加
            building->call_elevator(0, c.pick_up_floor); //エレベータの目的地にピックアップ階を追加
            this->passengers[c.id]->set_target(c.drop_off_floor); //人の目的階を設定
            call_plans.erase(call_plans.begin());
            std::cout << "** Call - id: " << c.id << ", floor: " << c.pick_up_floor << " **" << std::endl;
        }

        building->move_elevators(); //全エレベータを移動

        printResults();

        if(building->elevators[0]->get_destinations().size() >= 1){
            building->pick_up(building->elevators[0], passengers); //現在の階に人が待っていればピックアップ
            building->drop_off(building->elevators[0]); //現在の階で降りる人がいれば降ろす
        }

        if((call_plans.size() == 0) && (building->get_elevator(0)->get_destinations().size() == 0) && (building->get_calls().size() == 0)){
            break;
        }

        time++;
    }
}

void Simulator::printResults() const {
    std::cout << "<t=" << time << "> ";
    std::cout << "elevator: " << building->get_elevator_floor(0) << ", ";
    std::cout << " destination: ";
    for(auto e: building->get_elevator(0)->destinations) {
        std::cout << e << " ";
    }

    std::cout << "passenger: ";
    for(auto e: building->get_elevator(0)->get_passengers()) {
        std::cout << e->get_id() << " ";
    }
    std::cout << ", ";

    std::cout << "weight: " << building->get_elevator(0)->get_total_weight() << ", ";

    std::cout << std::endl;
}
