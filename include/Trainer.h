#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include <istream>
#include "../include/Customer.h"
#include "../include/Workout.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    Workout& findWorkout(int idW, const std::vector<Workout>& workoutOptions);
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();

    //Rule of 5
    ~Trainer(); //destructor
    Trainer(Trainer &trainer); //Copy Constructor
    Trainer & operator=(Trainer &trainer); //Copy Assignment Operator
    Trainer(Trainer&& other); //Move constructor
    Trainer &operator=(Trainer&& other); //Move Assignment Operator

private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    int salary=0;
};
//std::vector<int> sweaty_Id;
// = new 


#endif