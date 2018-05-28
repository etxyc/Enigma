enigma: main.o machine.o plugboard.o reflector.o rotor.o
	g++ -Wall -g main.o machine.o plugboard.o reflector.o rotor.o -o enigma

main.o: main.cpp machine.h
	g++ -Wall -g -c main.cpp

machine.o: machine.cpp machine.h plugboard.h reflector.h rotor.h
	g++ -Wall -g -c machine.cpp

plugboard.o: plugboard.cpp plugboard.h
	g++ -Wall -g -c plugboard.cpp

reflector.o: reflector.cpp reflector.h
	g++ -Wall -g -c reflector.cpp

rotor.o: rotor.cpp rotor.h
	g++ -Wall -g -c rotor.cpp
