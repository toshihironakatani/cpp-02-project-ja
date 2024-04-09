#pragma once

#include <vector>

#include "elevator.hpp"
#include "passenger.hpp"
#include "simulator.h"

struct Call{
  int id;
  int pick_up_floor;
  int drop_off_floor;
};

class Elevator;

class Building {
public:
  Building(int num_floor, int capacity, std::vector<Elevator*> elevators);
  void pick_up(Elevator* elevator, std::vector<Passenger*> passenger);
  void drop_off(Elevator* elevator);
  void call_elevator(int index_elevator, int destination);
  void move_elevators();
  bool can_pick_up(Elevator* elevator, Passenger* passenger);
  int get_elevator_floor(int index);
  Elevator* get_elevator(int index);
  void add_call(Call *call);
  std::vector<Call*> get_calls();
  void remove_call(Call* call);

public:
  int num_floor;
  int capacity;
  std::vector<Elevator*> elevators;
  std::vector<Call*> calls;
};
