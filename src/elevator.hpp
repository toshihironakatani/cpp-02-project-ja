#pragma once
#include <vector>

#include "passenger.hpp"
#include "building.hpp"

class Elevator {
public:
  Elevator();
  void add_destination(int destination);
  void remove_destination(int destination);
  void add_passenger(Passenger* passenger);
  void remove_passenger(Passenger* passenger);
  void move();
  int get_total_weight();
  int get_current_floor();
  std::vector<int> get_destinations();
  std::vector<Passenger*> get_passengers();

public:
  int current_floor = 0;
  std::vector<int> destinations;
  std::vector<Passenger*> passengers;
};
