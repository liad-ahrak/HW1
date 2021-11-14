#include <string>
#include "../include/Workout.h"

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO
};

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
    id(w_id),
    name(w_name),
    price(w_price),
    type(w_type) 
{}
Workout::Workout(const Workout &other): //copy constructor
    id(other.getId()),
    name(other.getName()),
    price(other.getPrice()),
    type(other.getType()) 
{}
Workout:: ~Workout(){//destructor- everything saved on the stack exept name
//
    name.~string();   
}
//Getter functions
int Workout::getId() const{ //return the data without ability to change it 2 const
    return id;
}
std::string Workout::getName() const{
    return name;
}
int Workout::getPrice() const{
    return price;
}
WorkoutType Workout::getType() const{
    return type;
}