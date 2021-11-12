#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "../include/Workout.h"


Customer::Customer(std::string c_name, int c_id): //constructor
    name(c_name),
    id(c_id),
    price(0);
{}
public:       
virtual std::vector<int> Customer::order(const std::vector<Workout> &workout_options)=0; //Abstract
virtual std::string toString() const = 0 //Abstract
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
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> sweaty_Id;
    if(workout_options.size()>0){
        for (Workout workout: workout_options){
            if(workout.getType() == CARDIO){
                sweaty_Id.push_back(workout.getId()); //Value(int)
                this-> price +=workout.getPrice();
            }
        }
    }
    return sweaty_Id;
}
 std::string SweatyCustomer::toString() const {
    std::string sweaty_Str = //later after the method in action;
    return sweaty_Str;
}
//private:
}; // }; end of class


class CheapCustomer : public Customer {
public:
CheapCustomer::CheapCustomer(std::string name, int id):
    Customer(name,id) // using Customer constructor
{}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> cheap_Id;
    if(workout_options.size()>0){
        cheap_Id.push_back(workout_options[0].getId());//the vector is sorted in the file
        this-> price +=workout.getPrice();
    }
    return cheap_Id;
}        
    std::string CheapCustomer::toString() const{
        std::string cheap_Str = //later after the method in action;
        return cheap_Str;
    }
//private:
};


class HeavyMuscleCustomer : public Customer {
public:
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id):
    Customer(name,id), // using Customer constructor
{}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> heavy_Id;
    if(workout_options.size()>0){
        for (Workout workout: workout_options){
            if(workout.getType() == ANAEROBIC){ // the vector is sorted in the file
                heavy_Id.push_back(workout.getId());
            }
        }
    }
    return heavy_Id;
}        
    }
    std::string HeavyMuscleCustomer::toString() const{
        std::string heavy_Str = //later after the method in action;
        return heavy_Str;
    }
//private:
};


class FullBodyCustomer : public Customer {
public:
FullBodyCustomer::FullBodyCustomer(std::string name, int id):
    Customer(name,id) // using Customer constructor
{}
    std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
        std::vector<int> fullbody_Id;
        if(workout_options.size()>0){
        for (Workout workout: workout_options){
            if(workout.getType() == ANAEROBIC){ // the vector is sorted in the file
                fullbody_Id.push_back(workout.getId());
            }
        }
    }
    return fullbody_Id;
    }
    std::string FullBodyCustomer::toString() const{
        std::string fullbody_Str = //later after the method in action;
        return fullbody_Str;
    }
//private:
};


#endif