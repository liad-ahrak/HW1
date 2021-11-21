#include "Studio.h"
#include <vector>
#include <string>
#include <sstream>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"
using namespace std;

Studio::Studio(): //constructor
    open(false), 
    trainers(0)
{}

Studio::Studio(const std::string &configFilePath){//basic data
    ifstream theFile(configFilePath);
    vector<string> spltIn
    //need to find to to convert string to int 
} // not done yet

void Studio::start(){
    open = true;
    cout<<"Studio is now open"<<endl;
    BaseAction* action= nullptr;
    string act;
    int id=0;
    string command;//first word
    do{
        string end_sent; 
        cin >> act; //the first word of the input from the user
        getline(cin,end_sent);
        stringstream word(act);
        getline(word,command,' ');
        
        if(command == "open"){
            string trainer_id;
            stringstream line(end_sent);
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
            int id= stoi(end_sent);
            action = new Order(id);
            action->act(*this);
        }

        else if(command == "move"){
            string original_id;
            stringstream line(end_sent);
            getline(line,original_id,' ');
            int original_trainer_id=stoi(original_id);// first paramater
            string dest_id;
            stringstream line(end_sent);
            getline(line,dest_id,' ');
            int dest_trainer_id=stoi(dest_id); // second paramater
            int customer_id= stoi(end_sent);
            action = new MoveCustomer(original_trainer_id, dest_trainer_id, customer_id);
            action->act(*this);
        }

        else if(command == "close"){
            int id= stoi(end_sent);
            action = new Close(id);
            action->act(*this);
        }

        else if(command == "workout_option"){
            action = new PrintWorkoutOptions();
            action->act(*this);
        }

        else if(command == "status"){
            int trainer_id= stoi(end_sent);
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

    } while(command == "closeAll"){
        action = new CloseAll();
        action->act(*this);
        open(false);
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

void Studio:: addActionToLog(BaseAction* action){
    actionsLog.push_back(action);
}


