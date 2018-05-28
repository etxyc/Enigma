#include <iostream>
#include <fstream>
#include <cstring>

#include "reflector.h"
#include "errors.h"

reflector::reflector(const char reflector_config[])
{
  reflector_config_=reflector_config;
  ifstream input;
  config_num=-1;
  input.open(reflector_config);

  // check if fail to open the file.
  if(input.fail())
  {
    cerr << "Fail to open reflector file: " << reflector_config_ << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // read configuration into string type.
  for(int i=0;!input.eof();i++)
  {
    input >> config_test[i];
  }
  input.close();

  // read configuration into integer and creat mappings.
  input.open(reflector_config);
  for(int i=0;!input.eof();i++)
  {
    input >> config[i];
    config_num++;
    creat_connection();
  }
  input.close();

  creat_connection();

  // check if number of parameters is correct.
  if(config_num<26 && config_num%2==0)
  {
    cerr << "Insufficient number of mappings in reflector file: "
         << reflector_config_ << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  if(config_num%2==1)
  {
    cerr << "Incorrect (odd) number of parameters in reflector file "
         << reflector_config_ << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  if(config_num>26)
  {
    cerr << "Incorrect number of parameters in reflector file "
         << reflector_config_ << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }



}

void reflector::creat_connection()
{
  for(int i=0;i<=config_num-1;i++)
  {
      int j=i/2;
      int r=i%2;

      // check if there is non-numeric character.
      if((config_test[config_num-1].find_first_not_of("0123456789"))
         !=string::npos)
      {
        cerr << "Non-numeric character in reflector file " << reflector_config_
             << endl;
        throw NON_NUMERIC_CHARACTER;
      }

      // check if there is invalid index.
      if(!(config[config_num-1]>=0 && config[config_num-1]<=25))
      {
        cerr << "Invalid index in reflector file " << reflector_config_ << endl;
        throw  INVALID_INDEX;
      }

      // assign the mapping.
      connection[j][r]= config[i];
  }

  // check if there is impossible mapping.
  for(int i=0;i<=config_num-1 && config_num<=26;i++)
  {
    int count=0;
    int temp_config;
    for(int j=0;j<=config_num-1;j++)
    {
      if(config[i]==config[j])
      {
        count++;
        temp_config=config[i];
      }
    }
    if(count >= 2)
    {
      cerr << "Impossible reflector configuration, " << temp_config;
      cerr << " connects a contact with itself or more than one contact in: " ;
      cerr << reflector_config_ << endl;
      throw INVALID_REFLECTOR_MAPPING;
    }
  }
}

int reflector::output_code(int input)
{
    int output=0;
    for(int r=0;r<=config_num/2-1;r++)
    {
      for(int c=0;c<=1;c++)
      {
        if(input==connection[r][c])
        {
          if(c==0)
          {
            output=connection[r][1];
          }
          else
          {
            output=connection[r][0];
          }
        }
      }
    }
    return output;
}
