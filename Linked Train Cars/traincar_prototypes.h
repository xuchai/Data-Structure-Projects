// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

#include "traincar.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
void PushBack(TrainCar* &t, TrainCar* car);
void DeleteAllCars(TrainCar* &head);
void TotalWeightAndCountCars(TrainCar* t, int &total_weight,int &num_engines, int &num_freight_cars,
                             int &num_passenger_cars,int &num_dining_cars,int &num_sleeping_cars);
float CalculateSpeed(TrainCar* t);

//----------------------------------------------------------------------------------------------------
bool is_infinite(TrainCar* t);
void AverageDistance_DiningCar(TrainCar* t, int &denominator, int &numerator);
float AverageDistanceToDiningCar(TrainCar* t);
int ClosestEngineToSleeperCar(TrainCar* t);
//----------------------------------------------------------------------------------------------------
int Calculate_weight(TrainCar* head);
float Calculate_num_of_engines(TrainCar* head);
TrainCar* train_constructing(TrainCar* &engines, TrainCar* &freight, int min_speed, int max_car_per_train,
                             float freight_weight_one_engine, int &num_engines);
std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights, float min_speed,
                                   int max_car_per_train);

//-----------------------------------------------------------------------------------------------------
void remove_cars(TrainCar* &p);
void insert_cars_prev(TrainCar* &car, TrainCar* &p);
void insert_cars_next(TrainCar* &car, TrainCar* &p);
int Calculate_numcars_apart_from_engines(TrainCar* train1);
void Separate(TrainCar* &train1,TrainCar* &train2,TrainCar* &train3);









