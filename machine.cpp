#include <iostream>
#include <string>

#include "machine.h"

machine::machine(const char* plugboard_config,const  char* reflector_config,
                int rotor_num, const char* position_config, char** rotor_config)
        :pb(plugboard_config),rf(reflector_config),
         num_of_rotors(rotor_num),position_config(position_config),
         rotor_config(rotor_config)
        {
          char message[1024];

          if(num_of_rotors>0)
          {
            // check if there are rotors and load them.
            load_rotor();

            // read the message and check if there is invalid character.
            cin >> ws;
            cin.getline(message,1024);
            for(int i=0;message[i]!='\0';i++)
            {
              if(message[i]!=' ')
              {
                if(message[i]<'A' || message[i]>'Z' )
                {
                  cerr << message[i] << " is not a valid input character "
                  << "(input characters must be upper case letters A-Z)!"
                  << endl;
                  throw INVALID_INPUT_CHARACTER;
                }
                // output encoded character.
                cout<< num_to_letter(encode(letter_to_num(message[i])));
             }
            }
            delete [] rot;
          }
          else // no rotor case.
          {
            cin >> ws;
            cin.getline(message,1024);
            for(int i=0;message[i]!='\0';i++)
            {
              if(message[i]<'A' || message[i]>'Z' )
              {
                cerr << message[i] << " is not a valid input character "
                << "(input characters must be upper case letters A-Z)!" << endl;
                throw INVALID_INPUT_CHARACTER;
              }
              cout<<
              num_to_letter(encode_with_no_rotor(letter_to_num(message[i])));
            }
          }
        }

void machine::load_rotor()
{
  // load position configuration file.
  load_position_config();

  // creat rotors.
  rot = new rotor* [num_of_rotors];
  for(int i=0;i<=num_of_rotors-1;i++)
  {
    rot[i] = new rotor(rotor_config[i],position[i],i,NULL);
  }

  // link each rotor to its left rotor.
  for(int i=1;i<=num_of_rotors-1;i++)
  {
    rot[i]->link_to_left_rotor(rot[i-1]);
  }
}

void machine::load_position_config()
{
  ifstream input;
  pos_num=-1;

  position_config_=position_config;

  input.open(position_config);

  // check if fail to open the file.
  if(input.fail())
  {
    cerr << "Fail to open position file: " << position_config_ << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // read configuration into string type.
  for(int i=0;!input.eof();i++)
  {
    input >> config_test[i];

    // check if there is non-numeric character.
    if((config_test[i].find_first_not_of("0123456789"))!=string::npos)
    {
      cerr << "Non-numeric character in rotor positions file "
      << position_config_ << endl;
      throw NON_NUMERIC_CHARACTER;
    }

  }
  input.close();

  input.open(position_config);
  for(int i=0;!input.eof();i++)
  {
    input >> position[i];


    // check if there is invalid index.
    if(!(position[i]>=0 && position[i]<=25))
    {
      cerr << "Invalid index in rotor positions file " << position_config_
           << endl;
      throw  INVALID_INDEX;
    }
    pos_num++;
  }
  input.close();

  // check if there is enough position parameters for rotors.
  if(pos_num<num_of_rotors)
  {
      cerr << "No starting position for rotor 0 in rotor position file: "
           << position_config_ << endl;
      throw NO_ROTOR_STARTING_POSITION;
  }
}

void machine::transform_rotors()
{
  //  turn proper rotors.
  rot[num_of_rotors-1]->turn();

}

int machine::forward_rotor_encode(int input)
{
  transform_rotors();
  int code=input;
  for(int i=num_of_rotors-1;i>=0;i--)
  {
    code=rot[i]->encode(code);
  }
  return code;
}

int machine::back_rotor_encode(int input)
{
  int code=input;
  for(int i=0;i<=num_of_rotors-1;i++)
  {
    code=rot[i]->back_encode(code);
  }
  return code;
}

int machine::encode(int input)
{
  int code=input;

  code=pb.output_code(code);
  code=forward_rotor_encode(code);
  code=rf.output_code(code);
  code=back_rotor_encode(code);
  code=pb.output_code(code);

  return code;
}

int machine::encode_with_no_rotor(int input)
{
  int code=input;
  code=pb.output_code(code);
  code=rf.output_code(code);
  code=pb.output_code(code);
  return code;
}

int machine::letter_to_num(char letter)
{
  int num=letter;
  num=num-'A';
  return num;
}

char machine::num_to_letter(int num)
{
  char letter=num;
  letter=num+'A';
  return letter;
}
