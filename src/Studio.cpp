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
    trainers(0){}

Studio::Studio(const std::string &configFilePath){
    std:: vector<std:: string> spltIn = splitInput(configFilePath, '\n');
    //need to find to to convert string to int
} // not done yet

void Studio::start(){
    open = true;
    cout<<"Studio is now open"<<endl;
    BaseAction* action= nullptr;
    string act;
    int id=0;
    do{
        string command; //first word
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
            for(int i=0; i<list_of_customer.size();++i){
            list_of_customer[i]=nullptr;
            }
        }

        else if(command == "order"){
            string trainer_id;
            stringstream line(end_sent);
            getline(line,trainer_id,' '); // first paramater
            int id= stoi(trainer_id);
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
            string cust_id;
            stringstream line(end_sent);
            getline(line,cust_id,' '); // first paramater
            int customer_id= stoi(cust_id);
            action = new MoveCustomer(original_trainer_id, dest_trainer_id, customer_id);
            action->act(*this);
        }

        else if(command == "close"){
            string trainer_id;
            stringstream line(end_sent);
            getline(line,trainer_id,' '); // first paramater
            int id= stoi(trainer_id);
            action = new Close(id);
            action->act(*this);
        }

        else if(command == "workout_option"){//???
            action = new PrintWorkoutOptions();
            action->act(*this);
        }

        else if(command == "status"){
            string id;
            stringstream line(end_sent);
            getline(line,id,' ');
            int trainer_id= stoi(id);
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

    } while(command =="closeAll"){

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

std::string Studio:: getType(){
    std::string active_action;
    // first word of the line
    buildAction(active_action);

}
BaseAction* buildAction(char* command){
    actionType = getType(command);
    if(actionType == 'open'){
        int trainer = getTrainerId(command);
        std::vector<Customer*> customer = getCustomers(command);
        return new OpenTrainer(trainer,customer);
    }
    
    else if(actionType == 'order'){
        int trainer = getTrainerId(command);
        return new Order(trainer);
    }
    
    else if(actionType == 'move'){
        

    }
    else if(actionType == 'close'){
        int trainer = getTrainerId(command);
        return new Close(trainer);
    }

    else if(actionType == 'closeAll'){

    }
    else if(actionType == 'workout_option'){

    }
    else if(actionType == 'status'){

    }
    else if(actionType == 'log'){

    }
    else if(actionType == 'backup'){

    }
    else if(actionType == 'restore'){

    }
    else if(actionType == 'close'){
        close();

    }




}
