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
    std:: vector<std:: string> spltIn = splitInput(configFilePath, '\n');
    //need to find to to convert string to int
} // not done yet

void Studio::start(){
    open = true;
    std::cout<<"Studio is now open"<<std::endl;
    std:: string act;
    while(open){
        std::cin >> act;
        std:: vector<std::string> actVector = splitInput(act, ' ');
        if(actVector[0].compare("open")){

        }
    }

}
/**
 * @brief this function split string\txt by given charcter
 * 
 * @param input = the input string\txt
 * @param ch = the charcter that we want to split by it
 * @return std::&  vector of string that every cell is word
 */
std:: vector<std::string>& Studio:: splitInput(const std::string &input, char ch){
    std:: vector<std:: string> splitCommand;
    std:: string tmp = "";
    for(int i=0; i<input.size(); i++){
        if(input[i] == ' '){
            splitCommand.push_back(tmp);
            tmp.clear();
        }
        else{
            tmp.push_back(input[i]);
        }
    }
    splitCommand.push_back(tmp);
    return splitCommand;
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
