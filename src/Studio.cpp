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

Studio::Studio(const std::string &configFilePath){
    std
} // not done yet

void Studio::start(){
    open = true;
    std::cout<<"Studio is now open"<<std::endl;

    std:: string act;
    while(open){
        std::cin >> getline(command, ); 
        BaseAction* act = buildAction(command);
        act -> act(*this);

    }

}

int Studio:: getNumOfTrainers() const {
    return trainers.size();
}

Trainer* Studio::getTrainer(int tid) {
    return trainers[tid];
}

const std::vector<BaseAction*>& Studio::getActionsLog() const{// Return a reference to the history of actions
    return actionsLog;
} 

std::vector<Workout>& Studio::getWorkoutOptions(){
    return workout_options;
}
/**
 * @brief add new action to the logActions vector
 * 
 * @param action = the new action we want to add to the log
 */
void Studio:: addActionToLog(BaseAction* action){
    actionsLog.push_back(action);
}
/**
 * @brief this function close the studio
 * 
 */
void Studio:: close(){
    open = false;
}

BaseAction* buildAction(char* command){
    actionType = getType(command);
    if(actionType == 'open'){
        int trainer = getTrainerId(command);
        std::vector<Customer*> customer = getCustomers(command);
        return new OpenTrainer(trainer,customer);

    }
}
