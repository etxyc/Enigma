#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <string>
using namespace std;

class plugboard
{
private:
  int connection[1024][2]; //mapping of plugboard.
  int config[1024]; // configuration parameters in corresponding file.
  int config_num; // number of configuration parameters.
  string config_test[100]; //string type of configurations.
  const char* plugboard_config_; // name of configuration file.

public:
  plugboard(const char plugboard_config[]);
  void creat_connection(); // function to build the mapping.
  int output_code(int input); // function to encode character.

};

#endif
