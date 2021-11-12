HW1: Action.o Customer.o main.o Studio.o Trainer.o Workout.o
	g++ Action.o Customer.o main.o Studio.o Trainer.o Workout.o -o HW1

Action.o: src/Action.cpp
	g++ -c Action.cpp
Customer.o: src/Customer.cpp
	g++ -c Customer.cpp
main.o: src/main.cpp
	g++ -c main.cpp
Studio.o: src/Studio.cpp
	g++ -c Studio.cpp
Trainer.o: Trainer.cpp
	g++ -c Trainer.cpp
Workout.o: src/Workout.cpp
	g++ -c Workout.cpp

clean:
	rm *.o HW1
