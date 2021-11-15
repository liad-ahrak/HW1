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
        std::vector <Workout*> anaerobic_workout;//vector with pointers to our vector
        for(Workout workout: workout_options){
            if(workout.getType() == ANAEROBIC){
                anaerobic_workout.push_back(&workout);
            }
        }
        std::sort(anaerobic_workout.begin(), anaerobic_workout.end(),[](Workout* a, Workout* b){ //sort by Type and then price
               return (*a).getPrice() < (*b).getPrice();
        });
        if(anaerobic_workout.size() > 0){
            for(int i=0; i < anaerobic_workout.size(); ++i){
                heavy_Id.push_back((*anaerobic_workout[i]).getId());
            }
        }
    }// at the end of the AF anaerobic_workout is deleted
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
        std::vector<Workout*> cardio_workout;
        std::vector<Workout*> mix_workout;
        std::vector<Workout*> anaerobic_workout;
        for (Workout workout: workout_options){ //Iterator
            if(workout.getType() == CARDIO){ 
                cardio_workout.push_back(&workout); 
            }
            if(workout.getType() == MIXED){ 
                mix_workout.push_back(&workout); 
            }
            else{
                anaerobic_workout.push_back(&workout);
            }
        }
        if(cardio_workout.size() > 0 && mix_workout.size() > 0 &&  anaerobic_workout.size() > 0){
            std::sort(cardio_workout.begin(), cardio_workout.end(),[](Workout* a, Workout* b){
                    return (*a).getPrice() < (*b).getPrice();
            });
            std::sort(mix_workout.begin(), mix_workout.end(),[](Workout* a, Workout* b){
                    return (*a).getPrice() > (*b).getPrice();
            });
            std::sort(anaerobic_workout.begin(), anaerobic_workout.end(),[](Workout* a, Workout* b){
                    return (*a).getPrice() < (*b).getPrice();
            });
            fullbody_Id.push_back((*cardio_workout[0]).getId());
            fullbody_Id.push_back((*mix_workout[0]).getId());
            fullbody_Id.push_back((*anaerobic_workout[0]).getId());
        }
    }
    return fullbody_Id;
}

std::string FullBodyCustomer::toString() const{
    return "fbd";
}

