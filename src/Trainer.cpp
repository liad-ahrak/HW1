#include "Trainer.h"
#include <exception>
#include <algorithm>
#include <istream>

typedef std::pair<int, Workout> OrderPair;

Trainer:: Trainer(int t_capacity):
    capacity(t_capacity),
    open(false)
    // the two other fields is called with the default constructor
{}

int Trainer:: getCapacity() const{
    return capacity;
}

void Trainer:: addCustomer(Customer* customer){
    if(customersList.size() < capacity){
        customersList.push_back(customer);
    }
}

/**
 * @brief this function make copy of the cusomers vector and orderList vector 
 * without the customer that we want to remove, and than clear the two vectors 
 * and replace them with the new "copies"
 * 
 * @param id = the id of the customer that we want to remove
 */
void Trainer:: removeCustomer(int id){ //Action MoveCostumer
    // check that this customer exists in the trainer session
    int index=-1;
    for(int i=0; (i<customersList.size()); ++i){
        if((*customersList[i]).getId() == id){
            index = i;
            //delete object
            (*customersList[i]).getName().clear();
        }
        else if(index!=-1){
            customersList[i]=customersList[i-1];
            if(i == customersList.size()-1){
                customersList[i]=nullptr;
            }
        }
    }
    //std::vector<int> idPlaces;
    std:: vector<OrderPair> newOrderList;
    for(OrderPair op: orderList){
        if(id!=op.first){
            newOrderList.push_back(op);
        }
        else{
            salary -= op.second.getPrice();
        }
    }
    orderList.clear();
    orderList = newOrderList;
    if(customersList.size() == 0){
        open==false;
    }
}
    
/**
 * @brief Get the Customer object
 * 
 * @return Customer* 
 */
Customer* Trainer:: getCustomer(int id){
    for(Customer* custumer: customersList){
        if(id ==(*custumer).getId()){
            return custumer;
        }
    }
    return nullptr;
}

/**
 * @brief this function give refrence to the customers list
 * 
 * @return std::vector<Customer*>& the customerList
 */
std::vector<Customer*>& Trainer::getCustomers(){
    return customersList;
}

/**
 * @brief Get the Orders object
 * 
 * @return std::vector<OrderPair>& 
 */
std::vector<OrderPair>& Trainer:: getOrders(){
    return orderList;
}

/**
 * @brief find the workout with the same id from the workoutOptions vector
 * @param idW = the workout id that we want
 * @param workoutOptions the workoutOptins vector
 * @return Workout& 
 */
Workout& Trainer:: findWorkout(int idW, const std::vector<Workout>& workoutOptions){
    for(Workout work: workoutOptions){
        if(work.getId()==idW){
            return work;
        }
    }
}

/**
 * @brief this function add order to vaild customer,this customer belongs to this trainer
 * and than add the workout that he wants.
 */
void Trainer:: order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){
    bool validC = false;
    for(Customer* customer: customersList){
        if ((*customer).getId() == customer_id){
            validC = true;
        } 
    }
    if(validC){
        for(int idW : workout_ids){
            Workout& work = findWorkout(idW,workout_options);
            OrderPair order{customer_id,work};
            orderList.push_back(order);
            salary += work.getPrice();
        }
    }
}

void Trainer::openTrainer(){
    open=true;
}

/**
 * @brief this function delete all the saved data that the trainer have
 * and change the "open" field to false
 */
void Trainer::closeTrainer(){
    open = false;
    for(Customer* customer:customersList){
        delete(customer);
    }
    customersList.clear();
    for(OrderPair pair:orderList){
        //:((((((((((((((((()))))))))))))))))
    }
    orderList.clear();
    salary=0;
}

/**
 * @brief Get the Salary object
 * @return int this is the salary
 */
int Trainer:: getSalary(){
    return salary;
}

/**
 * @brief this function return if this trainer is open or close
 * 
 * @return true = the trainer is open
 * @return false = the trainer is close
 */
bool Trainer:: isOpen(){
    return open;
}

//Rule of 5
Trainer::~Trainer(){
    //customersList
    for(int i=0; i<customersList.size();++i){
        (*customersList[i]).~Customer();
        customersList[i]=nullptr;
    }
    //orderList
    orderList.clear();
} //destructor
    
Trainer::Trainer(Trainer &trainer){
    std::vector<Customer*> new_trainer_customersList;
    std::vector<OrderPair> new_trainer_orderList;
    //customersList
    for(int i=0; i<customersList.size();++i){
        new_trainer_customersList[i]= customersList[i];
    }
    //orderList
    for(int i=0; i<orderList.size();++i){
        OrderPair a((orderList[i]).first,(orderList[i]).second);
        new_trainer_orderList.push_back(a);
    }
    int cap= trainer.getCapacity();
    Trainer new_trainer(cap, trainer.isOpen(),new_trainer_customersList, new_trainer_orderList);
    new_trainer.salary=trainer.salary;
} //Copy Constructor
    
Trainer & Trainer::operator=(Trainer &trainer){
    //check for "self assignment" and do nothing in that case
    if(this == &trainer){
        return *this;
    }
    // delete the prev info in this
    this->customersList;
    this->orderList;

    return *this;

} //Copy Assignment Operator
    
Trainer::Trainer(Trainer&& other){

} //Move constructor
    
Trainer & Trainer::operator=(Trainer &){

} //Move Assignment Operator

