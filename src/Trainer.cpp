#include "Trainer.h"
#include <exception>
#include <algorithm>

typedef std::pair<int, Workout> OrderPair;

Trainer:: Trainer(int t_capacity):
    capacity(t_capacity), open(false){
}
int Trainer:: getCapacity() const{
    return capacity;
}
/**
 * @brief this function add customer to the customerList only if the trainer have place
 * 
 * @param customer = the customer that we want to add
 */
void Trainer:: addCustomer(Customer* customer){
    if(customersList.size()<capacity){
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
void Trainer:: removeCustomer(int id){
    std::vector<int> idPlaces;
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
    std::vector<Customer*> newCustomerList;
    for(int i=0; i<customersList.size(); i++){
        if(id != (*customersList[i]).getId()){
            newCustomerList.push_back(customersList[i]);
        }
    }
    customersList.clear();
    customersList=newCustomerList;
}
/**
 * @brief Get the Customer object
 * 
 * @param id == the id of the customer that we want
 * @return Customer* = returning th
 */
Customer* Trainer:: getCustomer(int id){
    Customer* theChosenOne = nullptr;
    for(Customer* cust: customersList){
        if(id ==(*cust).getId()){
            theChosenOne = cust;
        }
    }
    return theChosenOne;
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
 * 
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
 * @brief this function add order to vaild customer, its mean that he customer of this trainer
 * and than add add the workout that he want 
 * 
 * @param customer_id = the customer that we want to order for him 
 * @param workout_ids = the workout id that he want
 * @param workout_options = all the workout options
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
/**
 * @brief make the file of "open" to true
 * 
 */
void Trainer::openTrainer(){
    open=true;
}
/**
 * @brief this function delete all the saved data that the trainer have
 * and change the "open" field to false
 */
void Trainer::closeTrainer(){
    open = false;
    customersList.clear();
    orderList.clear();
    salary=0;
}
/**
 * @brief Get the Salary object
 * 
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


