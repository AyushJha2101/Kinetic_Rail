//Static Physics Engine
#include "static_physics.h"
#pragma once
#include <iostream>
#include <cmath>
//I will create classes and objects later now for prototype 
/*=============Track Conditions===============*/
enum track_condition{wet,icy,dry};
enum grade_type { percent, permille };
/*=============Function Declarations===============*/
double sine_theta(double degrees);
double total_weight(double weight1, double weight2);
double curve_resistance(double radius);
double grade_convert(double gradient, grade_type type);
double max_adhesion_force(double mass, const double g, track_condition condition);
/*=============Main Function===============*/
int main (){
    // Declare variables
    double loco_weight, cargo_weight, angle, curve_radius, gradient, maxtractive_effort;
    int weather_input, grade_input;
    const double g = 9.81;

    std::cout << "=========================================\n";
    std::cout << "       KINETICRAIL SETUP TERMINAL        \n";
    std::cout << "=========================================\n\n";

    // 2. Simulating the "Database Feed" (Using terminal for the prototype)
    std::cout << "Enter Locomotive Mass (kg): ";
    std::cin >> loco_weight;
    std::cout << "Enter Cargo/Wagon Mass (kg): ";
    std::cin >> cargo_weight;
    
    std::cout << "Enter Incline Angle (degrees): ";
    std::cin >> angle;
    std::cout << "Enter Curve Radius (m): ";
    std::cin >> curve_radius;

    std::cout << "\n--- Track Conditions ---\n";
    std::cout << "Select Weather (0 = Wet, 1 = Icy, 2 = Dry): ";
    std::cin >> weather_input;
    track_condition current_weather = static_cast<track_condition>(weather_input);

    std::cout << "Select Gradient Format (0 = Percent, 1 = Permille): ";
    std::cin >> grade_input;
    grade_type current_grade = static_cast<grade_type>(grade_input);
    
    std::cout << "Enter Gradient Value: ";
    std::cin >> gradient;

    // 3. Engine Processing (The actual physics pipeline)
    double sine_theta1 = sine_theta(angle);
    double total_weight1 = total_weight(loco_weight, cargo_weight);
    double curve_resistance1 = curve_resistance(curve_radius);
    double max_adhesion_force1 = max_adhesion_force(total_weight1, g, current_weather); 
    double grade_convert1 = grade_convert(gradient, current_grade); 
    return 0;
}
/*=============Static Functions===============*/
double sine_theta (double degrees){
    const double PI = 3.141592653589793;
    double radians = degrees * (PI / 180.0);
    double sine_theta = sin(radians);
    return sine_theta;
}
double total_weight(double weight1, double weight2){
    double w = (weight1+weight2);
    return w;
}
double curve_resistance(double radius){
    double curve_r = (650)/(radius - 55); //Roeckl formula
    return curve_r;
}
double grade_convert(double gradient, grade_type type){
    switch(type){
        case percent:
            return (gradient/100);
        case permille:
            return (gradient/1000);
        default: return -1.0;
    }
}
double max_adhesion_force(double mass, const double g, track_condition condition){
    switch(condition){
        case dry:
            return (mass*g*0.35);
        case wet:
            return(mass*g*0.20);

        case icy:
            return (mass*g*0.10);

        default:
            return 0.0;
    }
}