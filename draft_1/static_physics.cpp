#include "static_physics.h"
#include <cmath>

/*=============Static Functions===============*/
double sine_theta (double degrees){
    const double PI = 3.141592653589793;
    double radians = degrees * (PI / 180.0);
    double sine_theta = sin(radians);
    return sine_theta;
}

double total_weight(double weight1, double weight2){
    double w = (weight1+weight2)*1000;
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
        case dry: return (mass*g*0.35);
        case wet: return (mass*g*0.20);
        case icy: return (mass*g*0.10);
        default:  return 0.0;
    }
}