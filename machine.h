#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <fstream>

#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "errors.h"

using namespace std;

class machine
{
private:
  plugboard pb; // plugboard instance.
  reflector rf; // reflector instance.
  rotor** rot; // rotor pointer points to an array of rotor.
  int num_of_rotors; // number of rotors.
  const char* position_config; // name of position configuration file.
  const char* position_config_;
  int position[1024]; // position parameters.
  string config_test[100]; // string type of position configuration.
  int pos_num; // number of position parameters.
  char** rotor_config; // name of rotor configuration file.

public:
  machine(const char* plugboard_config, const char* reflector_config,
          int rotor_num, const char* position_config, char** rotor_config);
  void load_rotor(); // function to load rotors in enigma machine.
  void load_position_config(); // function to load position configuration.
  void transform_rotors(); // function to transform rotors before encryption.
  int forward_rotor_encode(int input); // to encode character by rotor (forward).
  int back_rotor_encode(int input); // to encode character by rotor (backward).
  int encode(int input); // function to encode (whole process).
  int encode_with_no_rotor(int input); // function to encode (0 rotor).
  int letter_to_num(char letter); // function to convert a character to number.
  char num_to_letter(int num); // function to convert a number to character. 
};


#endif
