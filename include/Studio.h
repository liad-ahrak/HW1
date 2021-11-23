#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include <sstream>
#include "../include/Workout.h"
#include "../include/Trainer.h"
#include "../include/Studio.h"
#include "Action.h"
#include <iostream>


class Studio{		
public:
	Studio();
    Studio(const std::string &configFilePath);
    Studio(Studio& other);
    ~Studio();
    Studio & operator=(Studio &other);
    Studio(Studio&& other);
    Studio& operator=(Studio&& other);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();


private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif