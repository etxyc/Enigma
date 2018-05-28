#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <string>
using namespace std;

class reflector
{
private:
  int connection[1024][2]; // mapping of reflector.
  int config[1024]; // configuration parameters in file
  int config_num; // number of configuration parameters.
  string config_test[100]; // string type of configurations.
  const char* reflector_config_; // name of configuration file.

public:
  reflector(const char reflector_config[]);
  void creat_connection(); // function to build the mapping.
  int output_code(int input); // function to encode character.
};

#endif
