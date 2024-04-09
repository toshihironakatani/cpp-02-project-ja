#include <iostream>
#include <algorithm>

#include "building.hpp"
#include "elevator.hpp"

Building::Building(int num_floor, int capacity, std::vector<Elevator*> elevators): num_floor(num_floor), capacity(capacity), elevators(elevators) {};

void Building::pick_up(Elevator* elevator, std::vector<Passenger*> passengers) {
  for(auto e: calls) {
    if(elevator->get_current_floor() == e->pick_up_floor) {
      remove_call(e);

      Passenger* passenger = passengers[e->id];
      if(can_pick_up(elevator, passenger)){
        elevator->add_passenger(passenger);
        int destination = passenger->get_taget();

        std::cout << "** Pick up - ";
        std::cout << "id: " << passenger->get_id() << ", to: " << destination << " **" << std::endl;
        elevator->add_destination(destination);
      }
      else {
        std::cout << "** OVER WEIGHT! CANNOT PICK UP **" << std::endl;
      }
    }
  }
}

void Building::drop_off(Elevator* elevator) {
  for(auto& e: elevator->get_destinations()) {
    if(elevator->get_current_floor() == e) {
      elevator->remove_destination(e);
    }
  }
  for(auto e: elevator->get_passengers()) {
    if(elevator->get_current_floor() == e->get_taget()) {
      std::cout << "** drop off - id: " << e->get_id() << " **" << std::endl;
      elevator->remove_passenger(e);
    }
  }
}
void Building::call_elevator(int index_elevator, int destination) {
  elevators[index_elevator]->add_destination(destination);
}

void Building::move_elevators() {
  for(auto e: elevators) {
    e->move();
  }
}

bool Building::can_pick_up(Elevator* elevator, Passenger* passenger) {
  int sum = elevator->get_total_weight() + passenger->get_weight();
  if(sum <= capacity) {
    return true;
  }
  return false;
}

int Building::get_elevator_floor(int index) {
  return elevators[index]->get_current_floor();
}

Elevator* Building::get_elevator(int index) {
  return elevators[index];
}

void Building::add_call(Call* call) {
  calls.push_back(call);
}

std::vector<Call*> Building::get_calls() {
  return calls;
}

void Building::remove_call(Call* call) {
  auto new_end = std::remove(calls.begin(), calls.end(), call);
  calls.erase(new_end, calls.end());
}
