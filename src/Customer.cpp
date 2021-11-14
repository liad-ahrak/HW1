#include <vector>
#include <string>
#include <algorithm>
#include "Customer.h"
#include "Workout.h"
#include <istream>


Customer::Customer(std::string c_name, int c_id): //constructor
    name(c_name),
    id(c_id)
{}
Customer::Customer(const Customer &other): //copy constructor
    name(other.getName()),
    id(other.getId())
{}
//~Customer();//destructor
std::string Customer::getName() const{ 
    return name;
}
int Customer::getId() const{
    return id;
}



SweatyCustomer::SweatyCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> sweaty_Id;
    if(workout_options.size()>0){
        for (Workout workout: workout_options){ //Iterator
            if(workout.getType() == CARDIO){
                sweaty_Id.push_back(workout.getId()); //Value(int)
            }
        }
    }
    return sweaty_Id;
}
 std::string SweatyCustomer::toString() const {
    return "swt";
}

CheapCustomer::CheapCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> cheap_Id;
    int p_cheap = (workout_options[0]).getPrice();
    int i_cheap=0; //index of cheapest workout
    for(int i = 1; i < workout_options.size(); ++i){
        if((workout_options[i]).getPrice() < p_cheap){
            i_cheap=i;
        }
    }
    cheap_Id.push_back((workout_options[i_cheap]).getId());
    return cheap_Id; 
}      
  
std::string CheapCustomer::toString() const{
    return "chp";
}


HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> heavy_Id;
    if(workout_options.size()>0){
        std::vector<Workout> anaerobic_workout;
        for (Workout workout: workout_options){ //Iterator
            if(workout.getType() == ANAEROBIC){ 
                Workout anaerobic= Workout(workout);//copy constructor->destruct
                anaerobic_workout.push_back(anaerobic); 
            }
        }
        if(heavy_Id.size() > 0){
            std::sort(anaerobic_workout.begin(), anaerobic_workout.end(),[](Workout a, Workout b){
                return a.getPrice() < b.getPrice();
            });
            for(int i=0; i < anaerobic_workout.size(); ++i){
                heavy_Id.push_back((anaerobic_workout[i]).getId());
            }
        }
        for (Workout workout: anaerobic_workout){ //destruct the workouts in the vector
            workout.~Workout();
        }
        anaerobic_workout.~vector(); //delete the vector itselfs
    }
    return heavy_Id;
}        

std::string HeavyMuscleCustomer::toString() const{
    return "mcl";
}


FullBodyCustomer::FullBodyCustomer(std::string name, int id):
    Customer(name,id){} // using Customer constructor

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> fullbody_Id;
    if(workout_options.size()>0){
        std::vector<Workout> cardio_workout;
        std::vector<Workout> mix_workout;
        std::vector<Workout> anaerobic_workout;
        for (Workout workout: workout_options){ //Iterator
            if(workout.getType() == CARDIO){ 
                Workout cardio= Workout(workout);//copy constructor->destruct
                cardio_workout.push_back(cardio); 
            }
            if(workout.getType() == MIXED){ 
                Workout mixed= Workout(workout);//copy constructor->destruct
                mix_workout.push_back(mixed); 
            }
            else{
                Workout anaerobic= Workout(workout);//copy constructor->destruct
                anaerobic_workout.push_back(anaerobic);
            }
        }
        if(cardio_workout.size() > 0 && mix_workout.size() > 0 &&  anaerobic_workout.size() > 0){
            std::sort(cardio_workout.begin(), cardio_workout.end(),[](Workout a, Workout b){
                    return a.getPrice() < b.getPrice();
            });
            std::sort(mix_workout.begin(), mix_workout.end(),[](Workout a, Workout b){
                    return a.getPrice() > b.getPrice();
            });
            std::sort(anaerobic_workout.begin(), anaerobic_workout.end(),[](Workout a, Workout b){
                    return a.getPrice() < b.getPrice();
            });
            fullbody_Id.push_back((cardio_workout[0]).getId());
            fullbody_Id.push_back((mix_workout[0]).getId());
            fullbody_Id.push_back((anaerobic_workout[0]).getId());
        }
        //Destractors
        for (Workout workout: cardio_workout){ 
            workout.~Workout();
        }
        cardio_workout.~vector(); 
        for (Workout workout: mix_workout){ 
            workout.~Workout();
        }
        mix_workout.~vector();
        for (Workout workout: anaerobic_workout){
            workout.~Workout();
        }
        anaerobic_workout.~vector();
    }
    return fullbody_Id;
}

std::string FullBodyCustomer::toString() const{
    return "fbd";
}

