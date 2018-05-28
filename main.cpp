#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "machine.h"
#include "errors.h"

using namespace std;

int main(int argc, char** argv)
{
  try
  {
// check if the number of configuration file is valid.
    if(argc == 4 || argc <=2)
    {
      cerr << "usage: enigma plugboard-file reflector-file ";
      cerr <<	"(<rotor-file>* rotor-positions)?" << endl;
      throw INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

// assign proper configuration file and record the number of rotor.
    char* plugboard_config=NULL;
    char* reflector_config=NULL;
    char* position_config=NULL;
    char** rotor_config=NULL;

    char** config;
    config=argv;

    int rotor_num=0;
    rotor_num=argc-1-3;

    if(rotor_num>0)
    {
      rotor_config = new char*[rotor_num];
    }

    int k=3;
    for(int i=0;i<=rotor_num-1;i++)
    {
      rotor_config[i]=config[k];
      k++;
    }

    plugboard_config=config[1];
    reflector_config=config[2];

    if(rotor_num>0)
      position_config=config[argc-1];

// build enigma machine by using corresponding configuration files. 
    machine enigma(plugboard_config,reflector_config,rotor_num,
                   position_config,rotor_config);

    delete [] rotor_config;
  }

// catch thrown error and return error code.
  catch(int error)
  {
    return error;
  }

  return NO_ERROR;
}
