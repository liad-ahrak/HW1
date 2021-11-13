#include "Action.h"
#include <istream>


BaseAction:: BaseAction();
ActionStatus BaseAction:: getStatus() const{
    return status;
}
void BaseAction:: complete(){
    status = COMPLETED;
}
void BaseAction:: error(std::string errorMsg){
    (*this).errorMsg = errorMsg;
    status = ERROR;
 }
std::string BaseAction:: getErrorMsg() const{
     return errorMsg;
 }


OpenTrainer:: OpenTrainer(int id, std::vector<Customer *> &customersList){
    Trainer* trnP = Studio:: getTrainer(id);
    if (trnP == 0 || (*trnP).isOpen()){
        error();
        std::cout <<get
    }
}
    void OpenTrainer:: act(Studio &studio);
    std::string OpenTrainer:: toString() const;
private:
	const int trainerId;
	std::vector<Customer *> customers;



class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;
private:
};


PrintWorkoutOptions:: PrintWorkoutOptions();
void PrintWorkoutOptions:: act(Studio &studio){
    for(Workout workout: studio.getWorkoutOptions()){
        std::cout << workout.getName() <<", ";
        std::cout << workout.getType() <<", ";
        std::cour << workout.getPrice() <<", " << endl;
    }
    complete();
}
std::string PrintWorkoutOptions:: toString() const{ return "PrintWorkoutOptions";}



class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;

};


#endif