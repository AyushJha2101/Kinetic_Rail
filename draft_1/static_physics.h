#pragma once
//Header file for the static phy

/*=============Track Conditions===============*/
enum track_condition{wet,icy,dry};
enum grade_type { percent, permille };

/*=============Function Declarations===============*/
double sine_theta(double degrees);
double total_weight(double weight1, double weight2);
double curve_resistance(double radius);
double grade_convert(double gradient, grade_type type);
double max_adhesion_force(double mass, const double g, track_condition condition);