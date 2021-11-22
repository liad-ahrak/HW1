CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CPPFLAGS = = -I ./inculde -MMD -MP

all: link

link: compile 
	g++ -o bin/main bin/main.o bin/Action.o bin/Customer.o bin/Studio.o bin/Trainer.o bin/Workout.o

compile : src/Action.cpp src/Customer.cpp src/main.cpp src/Studio.cpp src/Trainer.cpp src/Workout.cpp
	g++ g -c -Wall -Weffc++ -std=c++11 -o bin/Action.o src/Action.cpp
	g++ g -c -Wall -Weffc++ -std=c++11 -o bin/Customer.o src/Customer.cpp
	g++ g -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp
	g++ g -c -Wall -Weffc++ -std=c++11 -o bin/Studio.o src/Studio.cpp
	g++ g -c -Wall -Weffc++ -std=c++11 -o bin/Trainer.o src/Trainer.cpp
	g++ g -c -Wall -Weffc++ -std=c++11 -o bin/Workout.o src/Workout.cpp
	
clean:
	rm -rf bin/*
