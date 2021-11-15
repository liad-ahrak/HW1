#include "Studio.h"
#include <vector>
#include <string>
#include "../include/Workout.h"
#include "../include/Trainer.h"
#include "../include/Action.h"

Studio::Studio(): //constructor
    open(0), //the studio is closed at first
    trainers(0), // 0 it is null at this case- for me
    workout_options(0),
    actionsLog(0) {}

Studio::Studio(const std::string &configFilePath); // not done yet

void Studio::start(){
    open = true;
    std::cout<<"Studio is now open"<<std::endl;
    trainers=;
    workout_options=;
    actionsLog=;
    open

}

int Studio:: getNumOfTrainers() const {
    return trainers.size();
}

Trainer* Studio::getTrainer(int tid) {
    return trainers[tid];
}
<<<<<<< HEAD

const std::vector<BaseAction*>& Studio::getActionsLog() const{// Return a reference to the history of actions
    return actionsLog;
} 

std::vector<Workout>& Studio::getWorkoutOptions(){
=======
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
std:: vector<Workout>& Studio:: getWorkoutOptions(){
>>>>>>> 99476e4ced092ba762d662f162fba290bcf3a34f
    return workout_options;
}
