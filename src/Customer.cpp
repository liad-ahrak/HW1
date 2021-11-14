#include <vector>
#include <string>
#include <algorithm>
#include "Customer.h"
#include "Workout.h"
#include <istream>


Customer::Customer(std::string c_name, int c_id): //constructor
    name(c_name),
    id(c_id),
    price(0)
{}
      
virtual std::vector<int> Customer::order(const std::vector<Workout> &workout_options)=0; //Abstract
virtual std::string Customer::toString() const = 0 //Abstract
std::string Customer::getName() const{ 
    return name;
}
int Customer::getId() const{
    return id;
}


class SweatyCustomer : public Customer {
public:
SweatyCustomer::SweatyCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
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
    std::string sweaty_Str = //later after the method in action;
    return sweaty_Str;
}
//private:
}; // }; end of class


class CheapCustomer : public Customer {
public:
CheapCustomer::CheapCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> cheap_Id;
    if(workout_options.size()>0){
        std::vector<Workout> order_workout_by_price= &workout_options; // BUILT COPY CONSTRUCTON IN WORKOUT
        std::sort(order_workout_by_price.begin(), order_workout_by_price.end(),[](workout a, workout b){
            return a.getPrice() < b.getPrice();
        });
        cheap_Id.push_back((order_workout_by_price[0]).getId());
        this-> price +=(order_workout_by_price[0]).getPrice();
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
    Customer(name,id){} // using Customer constructor

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> heavy_Id;
    if(workout_options.size()>0){
        std::vector<Workout> order_workout_by_price= ; // BUILT COPY CONSTRUCTON IN WORKOUT- take only ANAEROBIC
        std::sort(order_workout_by_price.begin(), order_workout_by_price.end(),[](Workout a, Workout b){
            return a.getPrice() < b.getPrice();
        });
        for(int i = order_workout_by_price.size()-1; i>=0 ; --i){ //Loop that takes all the workouts IDs
            heavy_Id.push_back((order_workout_by_price[i]).getId());
            this-> price += (order_workout_by_price[i]).getPrice();
        }
    }
    if(heavy_Id.size() == 0){
        //through Exepsion
    }
    return heavy_Id;
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
    Customer(name,id){} // using Customer constructor

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> fullbody_Id;
    if(workout_options.size()>0){
    std::vector<Workout> cardio_by_price= &workout_options; // BUILT COPY CONSTRUCTON IN WORKOUT- take only CARDIO
    std::sort(cardio_by_price.begin(), cardio_by_price.end(),[](Workout a, Workout b){
        return a.getPrice() < b.getPrice();
    }); 
    if(cardio_by_price.size()>0){
        heavy_Id.push_back((cardio_by_price[0]).getId());
        this-> price += (cardio_by_price[0]).getPrice();
    }
    else{

    }
    std::vector<Workout> mix_type_by_reverse_price= &workout_options; // BUILT COPY CONSTRUCTON IN WORKOUT- take only MIX
    std::sort(mix_type_by_reverse_price.begin(), mix_type_by_reverse_price.end(),[](workout a, Workout b){
        return a.getPrice() > b.getPrice();
    });
    if(mix_type_by_price.size()>0){
        heavy_Id.push_back((mix_type_by_price[0]).getId());
        this-> price += (mix_type_by_price[0]).getPrice();
    }
    else{

    }
    std::vector<Workout> anaerobic_by_price= &workout_options; // BUILT COPY CONSTRUCTON IN WORKOUT- take only ANAEROBIC
    std::sort(anaerobic_by_price.begin(), anaerobic_by_price.end(),[](workout a, workout b){
        return a.getPrice() < b.getPrice();
    }); 
    if(anaerobic_by_price.size()>0){
        heavy_Id.push_back((anaerobic_by_price[0]).getId());
        this-> price += (anaerobic_by_price[0]).getPrice();
    }
    else{

    }
    return fullbody_Id;
    }
    std::string FullBodyCustomer::toString() const{
        std::string fullbody_Str = //later after the method in action;
        return fullbody_Str;
    }
//private:
};