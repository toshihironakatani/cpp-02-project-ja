#include <iostream>
#include <algorithm>
#include <vector>
#include "elevator.hpp"
#include "passenger.hpp"
#include "building.hpp"

Elevator::Elevator() {};

void Elevator::add_destination(int destination) {
  destinations.push_back(destination);
}

void Elevator::remove_destination(int destination) {
  auto new_end = std::remove(destinations.begin(), destinations.end(), destination);
  destinations.erase(new_end, destinations.end());
}

void Elevator::add_passenger(Passenger* passenger) {
  passengers.push_back(passenger);
}

void Elevator::remove_passenger(Passenger* passenger) {
  auto new_end = std::remove(passengers.begin(), passengers.end(), passenger);
  passengers.erase(new_end, passengers.end());
}

void Elevator::move() {
  if(destinations.size() > 0) {
    if(current_floor < destinations[0]) {
      current_floor++;
    }
    else if(current_floor > destinations[0]) {
      current_floor--;
    }
  }
}

int Elevator::get_total_weight() {
  int sum = 0;
  for(auto e: passengers) {
    sum += e->get_weight();
  }
  return sum;
}

int Elevator::get_current_floor() {
  return current_floor;
}

std::vector<int> Elevator::get_destinations() {
  return destinations;
}

std::vector<Passenger*> Elevator::get_passengers() {
  return passengers;
}
