#include <vector>
#include <string>
#include "../include/Workout.h"
#include "../include/Cusromer.h"


Customer::Customer(std::string c_name, int c_id):
    name(c_name),
    id(c_id);
{}
       
virtual std::vector<int> Customer::order(const std::vector<Workout> &workout_options)=0;//Abstract
virtual std::string toString() const = 0; //Abstract
std::string Customer::getName() const{
    return name;
}
int Customer::getId() const{
    return id;
}


class SweatyCustomer : public Customer {
public:
    SweatyCustomer::SweatyCustomer(std::string name, int id):
        Customer(name,id) // using Customer constructor
    {}
    std:: Customer:: vector<int> order(const std::vector<Workout> &workout_options){
        std::vector<int> sweat;
        if(workout_options.size()>0){
            for (Workout workout: workout_options){
                if(workout.getType() == CARDIO){
                    sweat.push_back(workout.getId());
                    this->price += workout.getPrice();
                }
            }
        }
        return sweat;
    }
    std::string toString() const;
//private:
};


class CheapCustomer : public Customer {
public:
CheapCustomer::CheapCustomer(std::string name, int id):
        Customer(name,id) // using Customer constructor
{}
std::vector<int> order(const std::vector<Workout> &workout_options){
    vector<int> CC=new vector<int>;
    if(workout_options.size()>0){
        Workout cheapest=workout_options[0];
        for (Workout workout: workout_options){
            if(workout.getPrice() < cheapest.getPrice()){
                cheapest = workout; //RULE OF FIVE
            }
        }
        CC.push_back(cheapest);
    }
    return CC;
    
}        
    std::string toString() const;
//private:
};


class HeavyMuscleCustomer : public Customer {
public:
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id):
        Customer(name,id) // using Customer constructor
{}
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
//private:
};


class FullBodyCustomer : public Customer {
public:
FullBodyCustomer::FullBodyCustomer(std::string name, int id):
        Customer(name,id) // using Customer constructor
{}
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
//private:
};


#endif