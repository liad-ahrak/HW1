#include "../include/Studio.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../include/Workout.h"
#include "../include/Trainer.h"
#include "../include/Action.h"

using namespace std;

Studio::Studio(): //constructor
    open(false), 
    trainers(0)
{}

Studio::Studio(const std::string &configFilePath){//basic data
    ifstream File(configFilePath);//our stream that we will work on
    char line[300];
    File.getline(line,300);
    int i=1;
    int num_of_trainers;
    int workout_id = 0;
    while(File){
        File.getline(line,300);
        //ignore lines of this type:
        if(line[0] == '#' || line[0] == '\0'){//ignore all the lines with # or empy lines
            i = i+1;
            continue;
        }
        else{
            if(i == 2){//num of trainers
                num_of_trainers=stoi(line);
                i=i+1;
            }
            else if(i==5){//capacity of trainers
                for(int j=0;j<num_of_trainers;++j){
                    string trainer_cap;
                    stringstream cap(line);
                    getline(cap,trainer_cap,',');
                    int capacity= stoi(trainer_cap);
                    Trainer trainer_i(capacity);//creat all the trainers
                    trainers.push_back(&trainer_i);
                }
            }
            else{// work_option
                string workout_name;
                stringstream cap(line);
                getline(cap,workout_name,',');
                string workout_type;
                getline(cap,workout_type,',');
                WorkoutType type;
                if(workout_type == "ANAEROBIC"){
                    type = ANAEROBIC;
                }
                else if(workout_type == "MIXED"){
                    type = MIXED;
                }
                else{
                    type = CARDIO;

                }
                string workout_price;
                getline(cap,workout_type,'\n');
                int price = stoi(workout_price);
                Workout test = Workout(workout_id, workout_name,price, type);
                workout_options.push_back(test);
                workout_id = workout_id+1;
            }

        }
    }
} // check



Studio:: Studio(Studio& other):
    open(other.open)
{
    for(Trainer* t:other.trainers){
        trainers.push_back(t);
    }
    for(Workout w: other.workout_options){
        Workout newW(w.getId(),w.getName(), w.getPrice(), w.getType());
        workout_options.push_back(newW);
    }
    for(BaseAction* ba: other.actionsLog){
        actionsLog.push_back(ba);
    }
}
Studio:: ~Studio(){
    open = false;
    for(Trainer* tr: trainers){
        (*tr).~Trainer();
    }
    trainers.clear();
    for(Workout w:workout_options){
        w.~Workout();
    }
    workout_options.clear();
    for(BaseAction* ba:actionsLog){
        (*ba).~BaseAction();
    }
    actionsLog.clear();

}
Studio& Studio::operator= (Studio& other){
    if(this== &other){
        return* this;
    }
    else{
        for(Trainer* tr: trainers){
        (*tr).~Trainer();
        }
        trainers.clear();
        for(Workout w:workout_options){
            w.~Workout();
        }
        workout_options.clear();
        for(BaseAction* ba:actionsLog){
            (*ba).~BaseAction();
        }
        actionsLog.clear();
        for(Trainer* t:other.trainers){
        trainers.push_back(t);
        }
        for(Workout w: other.workout_options){
            Workout newW(w.getId(),w.getName(), w.getPrice(), w.getType());
            workout_options.push_back(newW);
        }
        for(BaseAction* ba: other.actionsLog){
            actionsLog.push_back(ba);
        }
    }
}
Studio:: Studio(Studio&& other):
    open(other.open),
    trainers(other.trainers),
    workout_options(other.workout_options),
    actionsLog(other.actionsLog)
{
    other.workout_options.clear();
    other.trainers.clear();
    other.actionsLog.clear();
}
Studio& Studio:: operator=(Studio&& other){
    for(Trainer* tr: trainers){
        (*tr).~Trainer();
    }
    trainers.clear();
    for(Workout w:workout_options){
        w.~Workout();
    }
    workout_options.clear();
    for(BaseAction* ba:actionsLog){
        (*ba).~BaseAction();
    }
    actionsLog.clear();
    open = other.open;
    trainers = other.trainers;
    workout_options = other.workout_options;///problem
    actionsLog = other.actionsLog;
    other.workout_options.clear();
    other.trainers.clear();
    other.actionsLog.clear();
}

void Studio::start(){
    open = true;
    cout<<"Studio is now open"<<endl;
    BaseAction* action= nullptr;
    string act;
    int id=0;
    string command;//first word
    string full_command;
    while(open){
        getline(cin,full_command);
        stringstream word(full_command);
        getline(word,command,' '); // the first word of the sentance

        if(command == "open"){
            string trainer_id;
            stringstream line(full_command);
            getline(line,trainer_id,' ');
            int id= stoi(trainer_id); // first paramater

            string customer_name;
            vector<Customer*> list_of_customer;
            while(getline(line,customer_name,',')){
                string type_customer;
                getline(line,type_customer,' ');
                Customer* new_customer;
                if(type_customer=="swt"){
                    SweatyCustomer customer(customer_name,id);
                    id= id+1;
                    new_customer = &customer;
                }
                else if(type_customer=="chp"){
                    CheapCustomer customer(customer_name,id);
                    id= id+1;
                    new_customer = &customer;
                }
                else if(type_customer=="mcl"){
                    HeavyMuscleCustomer customer(customer_name,id);
                    id= id+1;
                    new_customer = &customer;
                }
                else{//fbd
                    FullBodyCustomer customer(customer_name,id);
                    id= id+1;
                    new_customer = &customer;
                }
                list_of_customer.push_back(new_customer);
            }
            action= new OpenTrainer(id, list_of_customer);
            action->act(*this);

            //delete the trainers tha8t are more then the capacity
            list_of_customer.clear();//just the pointes not the customers
        }

        else if(command == "order"){
            string id;
            stringstream line(full_command);
            getline(line,id,' ');
            int trainer_id= stoi(id);
            full_command.clear();
            action = new Order(trainer_id);
            action->act(*this);
            
        }

        else if(command == "move"){
            string original_id;
            stringstream line(full_command);
            getline(line,original_id,' ');
            int original_trainer_id=stoi(original_id);// first paramater
            string dest_id;
            //stringstream line(full_command);
            getline(line,dest_id,' ');
            int dest_trainer_id=stoi(dest_id); // second paramater
            string cust_id;
            getline(line,cust_id,' ');
            int customer_id= stoi(cust_id);
            full_command.clear();
            action = new MoveCustomer(original_trainer_id, dest_trainer_id, customer_id);
            action->act(*this);
        }

        else if(command == "close"){
            string id;
            stringstream line(full_command);
            getline(line,id,' ');
            int trainer_id= stoi(id);
            full_command.clear();
            action = new Close(trainer_id);
            action->act(*this);
        }

        else if(command == "workout_option"){
            action = new PrintWorkoutOptions();
            action->act(*this);
        }

        else if(command == "status"){
            string id;
            stringstream line(full_command);
            getline(line,id,' ');
            int trainer_id= stoi(id);
            full_command.clear();
            action = new PrintTrainerStatus(trainer_id);
            action->act(*this);
        }

        else if(command == "log"){
            action = new PrintActionsLog();
            action->act(*this);
        }

        else if(command == "backup"){
            action = new BackupStudio();
            action->act(*this);
        }

        else if(command == "restore"){
            action = new RestoreStudio();
            action->act(*this);
        }

        else if(command == "closeAll"){
            action = new CloseAll();
            action->act(*this);
            open=false;
        }
        actionsLog.push_back(action);
        full_command.clear();
    }
}

int Studio:: getNumOfTrainers() const {
    return trainers.size();
}

Trainer* Studio::getTrainer(int tid) {
    return trainers[tid];
}

const std::vector<BaseAction*>& Studio::getActionsLog() const{// Return a reference to the history of actions
    return this->actionsLog;
} 

std::vector<Workout>& Studio::getWorkoutOptions(){
    return workout_options;
}



