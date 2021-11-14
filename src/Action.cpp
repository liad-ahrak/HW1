#include "Action.h"
#include "Trainer.h"

BaseAction:: BaseAction() {}
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


OpenTrainer:: OpenTrainer(int id, std::vector<Customer *> &customersList)
    :trainerId(id), customers(customersList){}   
void OpenTrainer:: act(Studio &studio){
    Trainer* trnP = studio.getTrainer(trainerId);
    if (trnP == 0 || (*trnP).isOpen()){
        error("Error: Workout session does not exist or is already open");
        std::cout <<getErrorMsg() << std::endl;
    }
    else{
        Trainer& trn = *trnP;
        if (trn.getCapacity() < customers.size()){
            error("Error: The trainer doesn't the capacity for all of the customers");
            std::cout <<getErrorMsg() <<std::endl;
        }
        else{
            trn.openTrainer();
            completeStr = "open "+std::to_string(trainerId)+" ";
            for (Customer* customer : customers){   
                trn.addCustomer(customer);
                completeStr += " "+customer->getName()+","+customer->toString();
            }
            completeStr += "\n";
            complete();
            std::cout<<completeStr;
        }
    }
    studio.actionsLog.push_back(this);
}
std::string OpenTrainer:: toString() const{
    return completeStr;
}


Order:: Order(int id)
    :trainerId(id){}
void Order::act(Studio &studio){
    Trainer* trnP = studio.getTrainer(trainerId);
    if (trnP == 0 || (*trnP).isOpen()){
        error("Workout session does not exist or is already open");
        std::cout <<getErrorMsg() << std::endl;
    }
    else{
        Trainer& trn = *trnP;
        completeStr = "order "+std::to_string(trainerId)+"\n";
        for (OrderPair op : trn.getOrders()){
            completeStr += trn.getCustomer(op.first)->getName() + " Is Doing "+(op.second).getName()+"\n";
        }
        std::cout<<completeStr;
        complete();
    }
    studio.actionsLog.push_back(this);
}
std::string Order:: toString() const{
    return completeStr;
}


MoveCustomer::MoveCustomer(int src, int dst, int customerId):
    srcTrainer(src),dstTrainer(dst),id(customerId)  {}
void MoveCustomer::act(Studio &studio){
    std::string errorM = "Cannot move customer";
    Trainer* srcTP = studio.getTrainer(srcTrainer);
    Trainer* dstTP = studio.getTrainer(dstTrainer);
    if(srcTP == 0 || dstTP == 0){
        error(errorM);
        std::cout<<errorM;
        return;
    }//can get to this section only if the pointers is existing
    Customer* cost = (*srcTP).getCustomer(id);
    Trainer& srcT = (*srcTP);
    Trainer& dstT = (*dstTP);
    if(cost == 0 || !srcT.isOpen() || !dstT.isOpen() || (dstT.getCapacity()-(dstT.getCustomers()).size()) <= 0){
        error(errorM);
        std::cout<<errorM;
    }//can complete the moving only if all the term are valid 
    srcT.removeCustomer(id);
    dstT.addCustomer(cost);
    completeStr = "move"+std::to_string(srcTrainer)+std::to_string(dstTrainer)+std::to_string(id)+"\n";
    std::cout<<completeStr;
    complete();
    studio.actionsLog.push_back(this);
}
std::string MoveCustomer:: toString() const{
    return completeStr;
}


Close:: Close(int id) 
    :trainerId(id){}
void Close:: act(Studio &studio){
    std:: string errorM = "Trainer does not exist or is not open";
    Trainer* trainerP = studio.getTrainer(trainerId);
    if(trainerP == nullptr || !(*trainerP).isOpen()){
        error(errorM);
        std::cout<<errorM <<std::endl;
    }
    else{
        complete();
        completeStr = "Trainer"+ std::to_string(trainerId)+"closed. Salary"+std::to_string((*trainerP).getSalary())+"NIS"+"\n";
        (*trainerP).closeTrainer();
    }
    studio.actionsLog.push_back(this);
}
std::string Close:: toString() const{
    return completeStr;
}


CloseAll:: CloseAll(){}
void CloseAll:: act(Studio &studio){
    for(int i=0; i<studio.getNumOfTrainers(); i++){
        Trainer& trainer = *(studio.getTrainer(i));
        if(trainer.isOpen()){
            completeStr += "Trainer"+ std::to_string(i)+"closed. Salary"+std::to_string(trainer.getSalary())+"NIS"+"\n";
            trainer.closeTrainer();
        }
    }
    studio.actionsLog.push_back(this);
}
std::string CloseAll:: toString() const{
    return completeStr;
}



PrintWorkoutOptions:: PrintWorkoutOptions(){}
void PrintWorkoutOptions:: act(Studio &studio){
    for(Workout workout: studio.getWorkoutOptions()){
        std::string type;
        int typeI = workout.getType();
        if(typeI==ANAEROBIC){type = "Anaerobic";}
        if(typeI==MIXED){type = "Mixed";}
        if(typeI==CARDIO){type = "Cardio";}
        completeStr += workout.getName()+", "+type+", "+std::to_string(workout.getPrice())+"\n";
    }
    complete();
    std::cout<<completeStr;
    studio.actionsLog.push_back(this);
}
std::string PrintWorkoutOptions:: toString() const{ return completeStr;}




PrintTrainerStatus:: PrintTrainerStatus(int id):
    trainerId(id){}
void PrintTrainerStatus:: act(Studio &studio){
    Trainer* trainerP = studio.getTrainer(trainerId);
    if(trainerP == nullptr || !(*trainerP).isOpen()){
        completeStr += "Trainer"+std::to_string(trainerId)+"status: close \n";
    }
    else{
        Trainer trainer = *trainerP;
        completeStr += "Trainer"+std::to_string(trainerId)+"status: open \n";
        completeStr += "Customers:\n";
        std::vector<Customer*> customers = trainer.getCustomers();
        for(int i=0; i<customers.size(); ++i){
            completeStr += std::to_string(i)+" "+(*(customers.at(i))).getName()+"\n";
        }
        completeStr+="Orders:\n";
        std::vector<OrderPair> cusOp = trainer.getOrders();
        std::vector<Workout> workoutOp = studio.getWorkoutOptions();
        int countW[workoutOp.size()];
        for(int i=0; i<workoutOp.size(); ++i){countW[i]=0;}
        for(OrderPair op: cusOp){
            for(int i=0; i<workoutOp.size(); ++i){
                if(workoutOp[i].getId()==op.second.getId()){
                    ++countW[i];
                }
            }
        }
        for (int i = 0; i < workoutOp.size(); i++)
        {
            completeStr += workoutOp[i].getName()+" "+std::to_string(workoutOp[i].getPrice())+"NIS "+std::to_string(workoutOp[i].getPrice())+"\n";
        }
        completeStr+= "Current Trainer's salary: "+std::to_string(trainer.getSalary())+"\n";     
    }
    std::cout<<completeStr;
    complete();
    studio.actionsLog.push_back(this);
}
std::string PrintTrainerStatus:: toString() const{
    return completeStr;
}



PrintActionsLog:: PrintActionsLog(){}
void PrintActionsLog:: act(Studio &studio){
    std:: vector<BaseAction*> actionsLog = studio.getActionsLog();
    for(BaseAction* actP: actionsLog){
        BaseAction& act1 = * actP;
        std::cout<<act1.toString();
        if(act1.getStatus()==COMPLETED){
            std:: cout<<"complete";
        }
        else{
            std::cout<<(*actP).getErrorMsg();
        }
    }
}
std::string PrintActionsLog:: toString() const{
}



BackupStudio:: BackupStudio(){}
void BackupStudio:: act(Studio &studio){
    backup = *(Studio(studio));
}
std::string BackupStudio:: toString() const{

}



RestoreStudio ::RestoreStudio(){}
void RestoreStudio ::act(Studio &studio){//need to do move method to studio
    studio = backup;
}
std::string RestoreStudio ::toString() const{

}