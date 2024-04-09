#include "passenger.hpp"
#include <iostream>

Passenger::Passenger(int id, int weight): id(id), weight(weight) {};

int Passenger::get_weight() {
  return weight;
}

int Passenger::get_taget() {
  return target_floor;
}

int Passenger::get_id() {
  return id;
}

void Passenger::set_target(int floor) {
  target_floor = floor;
}
