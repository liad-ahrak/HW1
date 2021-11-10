HW1: Action.o Customer.o main.o Studio.o Trainer.o Workout.o
	g++ Action.o Customer.o main.o Studio.o Trainer.o Workout.o -o HW1

Action.o: Action.cpp
	g++ -c Action.cpp
Customer.o: Customer.cpp
	g++ -c Customer.cpp
main.o: main.cpp
	g++ -c main.cpp
Studio.o: Studio.cpp
	g++ -c Studio.cpp
Trainer.o: Trainer.cpp
	g++ -c Trainer.cpp
Workout.o: Workout.cpp
	g++ -c Workout.cpp

clean:
	rm *.o HW1
