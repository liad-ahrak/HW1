#include <vector>
#include <string>
#include <algorithm>
#include "Customer.h"
#include "Workout.h"
#include "Customer.cpp"
#include <istream>


SweatyCustomer::SweatyCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

virtual std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> sweaty_Id;
    if(workout_options.size()>0){
        for (Workout workout: workout_options){ //Iterator
            if(workout.getType() == CARDIO){
                sweaty_Id.push_back(workout.getId()); //Value(int)
                this-> price +=workout.getPrice();
            }
        }
    }
    return sweaty_Id;
}
 std::string SweatyCustomer::toString() const {
    return "swt";
}
