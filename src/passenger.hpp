#pragma once

class Passenger {
public:
  Passenger(int id, int weight);
  int get_weight();
  int get_taget();
  int get_id();
  void set_target(int floor);

private:
  int id;
  int weight;
  int target_floor;
};
