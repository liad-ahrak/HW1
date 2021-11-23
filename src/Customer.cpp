#include <vector>
#include <string>
#include <algorithm>
#include "../include/Customer.h"
#include "../include/Workout.h"
#include <istream>
using namespace std;

typedef std::pair<int, int> my_pair;

Customer::Customer(std::string c_name, int c_id): //constructor
    name(c_name),
    id(c_id)
{}
std::string Customer::getName() const{ 
    return name;
}
int Customer::getId() const{
    return id;
}



SweatyCustomer::SweatyCustomer(std::string name, int id):
    Customer(name,id)
{} // using Customer constructor
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
    Customer(name,id)
{} // using Customer constructor
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> cheap_Id;
    if(workout_options.size()>0){
        int p_cheap = (workout_options[0]).getPrice();
        int i_cheap=0; //index of cheapest workout
        for(int i = 1; i < workout_options.size(); ++i){
            if((workout_options[i]).getPrice() < p_cheap){
                i_cheap=i;
            }
        }
        cheap_Id.push_back((workout_options[i_cheap]).getId());
    }
    return cheap_Id; 
}        
std::string CheapCustomer::toString() const{
    return "chp";
}


HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id):
    Customer(name,id)
{} // using Customer constructor
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> heavy_Id;
    if(workout_options.size()>0){
        std::vector <my_pair> anaerobic_workout;//vector with int id, int price
        for(Workout workout: workout_options){
            if(workout.getType() == ANAEROBIC){
                anaerobic_workout.push_back({workout.getId(),workout.getPrice()});
            }
        }
        std::stable_sort(anaerobic_workout.begin(), anaerobic_workout.end(),[](my_pair a, my_pair b){ //sort by Type and then price
               return a.second > b.second;
        });
        if(anaerobic_workout.size() > 0){
            for(int i=0; i < anaerobic_workout.size(); ++i){
                heavy_Id.push_back((anaerobic_workout[i].first));
            }
        }
        anaerobic_workout.clear();
    }
    return heavy_Id;
}        
std::string HeavyMuscleCustomer::toString() const{
    return "mcl";
}


FullBodyCustomer::FullBodyCustomer(std::string name, int id):
    Customer(name,id)
{} // using Customer constructor
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    std::vector<int> fullbody_Id;
    if(workout_options.size()>0){
        std::vector<my_pair> cardio_workout;
        std::vector<my_pair> mix_workout;
        std::vector<my_pair> anaerobic_workout;
        for (Workout workout: workout_options){ //Iterator
            if(workout.getType() == CARDIO){ 
                cardio_workout.push_back({workout.getId(),workout.getPrice()}); 
            }
            if(workout.getType() == MIXED){ 
                mix_workout.push_back({workout.getId(),workout.getPrice()}); 
            }
            else{
                anaerobic_workout.push_back({workout.getId(),workout.getPrice()}); 
            }
        }
        if(cardio_workout.size() > 0 && mix_workout.size() > 0 &&  anaerobic_workout.size() > 0){
            std::stable_sort(cardio_workout.begin(), cardio_workout.end(),[](my_pair a, my_pair b){
                    return a.second < b.second;
            });
            std::stable_sort(mix_workout.begin(), mix_workout.end(),[](my_pair a, my_pair b){
                    return a.second > b.second;
            });
            std::stable_sort(anaerobic_workout.begin(), anaerobic_workout.end(),[](my_pair a, my_pair b){
                    return a.second < b.second;
            });
            fullbody_Id.push_back((cardio_workout[0]).first);
            fullbody_Id.push_back((mix_workout[0]).first);
            fullbody_Id.push_back((anaerobic_workout[0]).first);
        }
        cardio_workout.clear();
        mix_workout.clear();
        anaerobic_workout.clear();
    }
    return fullbody_Id;
}
std::string FullBodyCustomer::toString() const{
    return "fbd";
}

