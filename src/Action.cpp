#include "../include/Action.h"
#include <vector>
using namespace std;

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const{
    return status;
}

void BaseAction::complete(){
    status = COMPLETED;
}

void BaseAction::error(std::string errorMsg){
    (*this).errorMsg = errorMsg;
    status = ERROR;
}

std::string BaseAction::getErrorMsg() const{
    return errorMsg;
}

/**
 * @brief this function is public 
 * because the protected doesn't at the sons of BaseAction
 * 
 * @return std:: the error massege 
 */
std::string BaseAction::publicgetErrorMsg() const{
    return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id),
                                                                           customers(customersList) {}

void OpenTrainer::act(Studio &studio)
{
    Trainer *trnP = studio.getTrainer(trainerId);
    if (trnP == 0 || (*trnP).isOpen())
    { //trainer does not exist or open already
        error("Error: Workout session does not exist or is already open");
        completeStr = std::to_string(trainerId);
        for (Customer *cust : customers)
        {
            Customer &customer = *cust;
            completeStr += " " + customer.getName() + "," + customer.toString();
        }
        std::cout << getErrorMsg() << std::endl;
    }
    else
    {
        Trainer &trn = *trnP;
        trn.openTrainer();
        completeStr = "open " + std::to_string(trainerId);
        for (int i = 0; i < trn.getCapacity(); i++)
        {
            Customer &customer = *(customers[i]);
            trn.addCustomer(customers[i]);
            completeStr += " " + customer.getName() + "," + customer.toString();
        }
        complete(); //success
        std::cout << completeStr;
    }
}
std::string OpenTrainer::toString() const
{
    return completeStr;
}

Order::Order(int id) : trainerId(id) {}

void Order::act(Studio &studio)
{
    Trainer *trnP = studio.getTrainer(trainerId);
    if (trnP == 0 || !(*trnP).isOpen())
    {
        error("Trainer does not exist or is not open");
        std::cout << getErrorMsg() << std::endl;
    }
    else
    {
        Trainer &trn = *trnP;
        completeStr = "order " + std::to_string(trainerId) + "\n";
        for (OrderPair op : trn.getOrders())
        {
            completeStr += (*(trn.getCustomer(op.first))).getName() + " Is Doing " + (op.second).getName() + "\n";
        }
        std::cout << completeStr;
        complete();
    }
}

std::string Order::toString() const
{
    return completeStr;
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : srcTrainer(src),
                                                               dstTrainer(dst),
                                                               id(customerId) {}

void MoveCustomer::act(Studio &studio)
{
    std::string errorM = "Cannot move customer";
    Trainer *srcTP = studio.getTrainer(srcTrainer);
    Trainer *dstTP = studio.getTrainer(dstTrainer);
    if (srcTP == 0 || dstTP == 0)
    {
        error(errorM);
        std::cout << errorM;
    } //can get to this section only if the pointers is existing
    else
    {
        Customer *cust = (*srcTP).getCustomer(id);
        Trainer &srcT = (*srcTP);
        Trainer &dstT = (*dstTP);
        if (cust == 0 || !srcT.isOpen() || !dstT.isOpen() || (dstT.getCapacity() - (dstT.getCustomers()).size()) == 0)
        {
            error(errorM);
            std::cout << errorM;
        }                        //can complete the moving only if all the term are valid
        srcT.removeCustomer(id); // if it is the last customer trainer is closed
        dstT.addCustomer(cust);
        completeStr = "move " + std::to_string(srcTrainer) + " " + std::to_string(dstTrainer) + " " + std::to_string(id) + "\n";
        std::cout << completeStr;
        complete();
    }
}

std::string MoveCustomer::toString() const
{
    return completeStr;
}

Close::Close(int id) : trainerId(id) {}

void Close::act(Studio &studio)
{
    std::string errorM = "Trainer does not exist or is not open";
    Trainer *trainerP = studio.getTrainer(trainerId);
    if (trainerP == nullptr || !(*trainerP).isOpen())
    {
        error(errorM);
        std::cout << errorM << std::endl;
    }
    else
    {
        complete();
        completeStr = "Trainer " + std::to_string(trainerId) + " closed. Salary " + std::to_string((*trainerP).getSalary()) + "NIS" + "\n";
        (*trainerP).closeTrainer();
    }
}
std::string Close::toString() const
{
    return completeStr;
}

CloseAll::CloseAll() {}
void CloseAll::act(Studio &studio)
{
    for (int i = 0; i < studio.getNumOfTrainers(); i++)
    {
        Trainer &trainer = *(studio.getTrainer(i));
        if (trainer.isOpen())
        {
            completeStr += "Trainer " + std::to_string(i) + " closed. Salary " + std::to_string(trainer.getSalary()) + "NIS" + "\n";
            trainer.closeTrainer();
        }
    }
}

std::string CloseAll::toString() const
{
    return completeStr;
}

PrintWorkoutOptions::PrintWorkoutOptions() {}
void PrintWorkoutOptions::act(Studio &studio)
{
    for (Workout workout : studio.getWorkoutOptions())
    {
        std::string type;
        int typeI = workout.getType();
        if (typeI == ANAEROBIC)
        {
            type = "Anaerobic";
        }
        else if (typeI == MIXED)
        {
            type = "Mixed";
        }
        else
        {
            type = "Cardio";
        }
        completeStr += workout.getName() + ", " + type + ", " + std::to_string(workout.getPrice()) + "\n";
    }
    complete();
    std::cout << completeStr;
}
std::string PrintWorkoutOptions::toString() const
{
    return completeStr;
}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio)
{
    Trainer *trainerP = studio.getTrainer(trainerId);
    if (!(*trainerP).isOpen())
    {
        completeStr += "Trainer " + std::to_string(trainerId) + " status: closed \n";
    }
    else
    {
        Trainer trainer = *trainerP;
        completeStr += "Trainer " + std::to_string(trainerId) + " status: open \n";
        completeStr += "Customers:\n";
        std::vector<Customer *> customers = trainer.getCustomers();
        for (Customer *cust : customers)
        {
            completeStr += std::to_string((*cust).getId()) + " " + (*(cust)).getName() + "\n";
        }
        completeStr += "Orders:\n";
        std::vector<OrderPair> &cusOp = trainer.getOrders();
        std::vector<Workout> &workoutOp = studio.getWorkoutOptions();
        int countW[workoutOp.size()];
        for (int i = 0; i < workoutOp.size(); ++i)
        {
            countW[i] = 0;
        }
        for (OrderPair op : cusOp)
        { //count the workouts for each one
            for (int i = 0; i < workoutOp.size(); ++i)
            {
                if (workoutOp[i].getId() == op.second.getId())
                {
                    ++countW[i];
                }
            }
        }
        for (int i = 0; i < workoutOp.size(); i++)
        {
            completeStr += workoutOp[i].getName() + " " + std::to_string(workoutOp[i].getPrice()) + "NIS " + std::to_string(countW[i]) + "\n";
        }
        completeStr += "Current Trainer's salary: " + std::to_string(trainer.getSalary()) + "NIS\n";
    }
    std::cout << completeStr;
    complete();
}
std::string PrintTrainerStatus::toString() const
{
    return completeStr;
}

PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(Studio &studio){//?? why it doesnt work???
    for (BaseAction* actP : studio.getActionsLog()){
        //BaseAction &act1 = *actP;
        std::cout << actP->toString();
        if (actP->getStatus() == COMPLETED){
            std::cout << "Complete\n";
        }
        else{
            std::cout << actP->toString() << (actP)->publicgetErrorMsg() << std::endl;
        }
    }
}

std::string PrintActionsLog::toString() const
{
    return "log";
}

BackupStudio::BackupStudio() {}
void BackupStudio::act(Studio &studio){
    if(backup != nullptr){
        delete backup;
    }
    backup = new Studio(studio); 
    complete();
}
std::string BackupStudio::toString() const
{
    return "backup";
}

RestoreStudio ::RestoreStudio() {}
void RestoreStudio ::act(Studio &studio)
{ //move constructor
    if (backup == 0)
    {
        error("No backup available");
    }
    else
    {
        studio = *backup;
        complete();
    }
}
std::string RestoreStudio ::toString() const
{
    return "restore";
}