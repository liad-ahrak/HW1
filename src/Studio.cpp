#ifndef STUDIO_H_
#define STUDIO_H_

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
    return trainers.size()
}
//I didn't finish
Trainer* getTrainer(int tid) {
    for(int i)
}
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif