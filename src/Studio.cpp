#include "Studio.h"
#include <vector>
#include <string>
#include "../include/Workout.h"
#include "../include/Trainer.h"
#include "../include/Action.h"


Studio:: Studio():open(0), trainer=0, workout_options=0, actionLog=0
{
}
    Studio(const std::string &configFilePath);
    void start();
int Studio:: getNumOfTrainers() const {
    return trainers.size();
}
//I didn't finish
Trainer* getTrainer(int tid) {
    for(int i)
}
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
std:: Stuido:: vector<Workout>& getWorkoutOptions(){
    for(Workout workout: workout_options){
        std::cout <<
    }
}
