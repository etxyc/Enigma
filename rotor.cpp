#include <iostream>
#include <fstream>
#include <cstring>

#include "rotor.h"


rotor::rotor(char const *rotor_config,int position_config,
             int num_of_rotor,rotor* left_rotor)
{
  rotor_config_=rotor_config;
  ifstream input;
  config_num=-1;

  input.open(rotor_config);

  // check if fail to open the file.
  if(input.fail())
  {
    cerr << "Fail to open rotor file: " << rotor_config_ << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // read configuration into string type.
  for(int i=0;!input.eof();i++)
  {
    input >> config_test[i];
  }
  input.close();

  // read configuration into integer and creat mappings.
  input.open(rotor_config);
  for(int i=0;!input.eof();i++)
  {
    input >> config[i];
    config_num++;
    creat_connection();
  }
  input.close();

  position=position_config;
  num=num_of_rotor;

  // read notch parameters.
  notch_num=0;
  for(int i=26;i<=config_num-1;i++)
  {
    notch[notch_num]=config[i];
    notch_num++;
  }

  creat_connection();

  // check if number of parameters is correct.
  if(config_num<26)
  {
    cerr << "Not all inputs mapped in rotor file: " << rotor_config_ << endl;
    throw INVALID_ROTOR_MAPPING;
  }

  // set initial position.
  set_position();
}

void rotor::creat_connection()
{
  for(int i=0;i<=config_num-1;i++)
  {
    // check if there is non-numeric character.
    if((config_test[config_num-1].find_first_not_of("0123456789"))
       !=string::npos)
    {
      cerr << "Non-numeric character for mapping in rotor file "
           << rotor_config_ << endl;
      throw NON_NUMERIC_CHARACTER;
    }

    // check if there is invalid index.
    if(!(config[config_num-1]>=0 && config[config_num-1]<=25))
    {
      cerr << "Invalid index for mapping in rotor file " << rotor_config_
           << endl;
      throw  INVALID_INDEX;
    }

    // assign the mapping.
    connection[i][0]=i;
    connection[i][1]=config[i];
  }

    // check if there is impossible mapping.
    for(int j=0;j<=config_num-2 && config_num<=25 ;j++)
    {
      if(connection[config_num-1][1]==connection[j][1])
      {
        cerr << "Invalid mapping of input "
             << connection[config_num-1][0]
             << " to output "
             << connection[config_num-1][1]
             << " (output "
             << connection[config_num-1][1]
             << " is already mapped to from input "
             << connection[j][0]
             << ")" << endl;
        throw INVALID_ROTOR_MAPPING;
      }
    }

}

void rotor::turn()
{
  int temp[1][2];
  temp[0][0]=connection[0][0];
  temp[0][1]=connection[0][1];

  for(int i=0; i<=24; i++)
  {
    connection[i][0]=connection[i+1][0];
    connection[i][1]=connection[i+1][1];
  }
  connection[25][0]=temp[0][0];
  connection[25][1]=temp[0][1];

  if(this->if_notch() && left_rotor != NULL)
  {
    left_rotor->turn();
  }
}

int rotor::encode(int input)
{
  int output;
  for(int i=0;i<=25;i++)
  {
    if(connection[i][0]==connection[input][1])
    output=i;
  }
  return output;
}


int rotor::back_encode(int input)
{
  int output;
  for(int i=0;i<=25;i++)
  {
    if(connection[i][1]==connection[input][0])
    output=i;
  }
  return output;
}

void rotor::set_position()
{
  int j=26;
  int k=0;
  for(int i=0; i<position; i++)
  {
    connection[j][0]=connection[i][0];
    connection[j][1]=connection[i][1];
    j++;
    k++;
  }

  k=position;
  for(int i=0; i<=25 ; i++)
  {
    connection[i][0]=connection[k][0];
    connection[i][1]=connection[k][1];
    k++;
  }
}

bool rotor::if_notch()
{
  for(int i=0;i<=notch_num-1;i++)
  {
    if(connection[0][0]==notch[i])
      return 1;
  }
    return 0;
}

void rotor::turn_left_rotor()
{
  if(this->if_notch())
  {
    left_rotor->turn();
  }
}

void rotor::link_to_left_rotor(rotor* rotor_to_the_left)
{
  left_rotor=rotor_to_the_left;
}
