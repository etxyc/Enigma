#ifndef ROTOR_H
#define ROTOR_H

#include <string>
#include "errors.h"

using namespace std;

class rotor
{
private:
  int connection[1024][2]; // mappings of rotor.
  int config[1024]; // configuration parameters in corresponding file.
  int config_num; // number of configurations.
  int notch[26]; // array of notches.
  int notch_num; // number of notches.
  int position; // initial position of rotor.
  int num; // the serial number of rotor.
  rotor* left_rotor; // the pointer points to the rotor on its left.
  string config_test[100]; //string type of configurations.
  const char* rotor_config_; // name of configuration file.

public:
  rotor(char const rotor_config[],int position_config, int num_of_rotor,
        rotor* left_rotor);
  void creat_connection(); // function to build the mapping.
  void turn(); // function to turn the rotor.
  int encode(int input); // function to encode character.
  int back_encode(int input); // function to encode character from left to right.
  void set_position(); // function to set the initial postion of rotor.
  bool if_notch(); // function to check if notch is on the top.
  void turn_left_rotor(); // function to turn the rotor on the left.
  void link_to_left_rotor(rotor* rotor_to_the_left); // function to creat link
                                                    // to the rotor on the left.
};

#endif
