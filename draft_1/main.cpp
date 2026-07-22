#include <iostream>
#include "static_physics.h" // Links to the menu so it knows the formulas exist

/*=============Main Function===============*/
int main (){
    // Declare variables
    double loco_weight, cargo_weight, angle, curve_radius, gradient, maxtractive_effort;
    int weather_input, grade_input;
    const double g = 9.81;

    std::cout << "=========================================\n";
    std::cout << "       KINETICRAIL SETUP TERMINAL        \n";
    std::cout << "=========================================\n\n";

    // 2. Simulating the "Database Feed"
    std::cout << "Enter Locomotive Mass (tonnes): ";
    std::cin >> loco_weight;
    std::cout << "Enter Cargo/Wagon Mass (tonnes): ";
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

    // 4. Output Data
    std::cout << "\n=========================================\n";
    std::cout << "        CALCULATING DYNAMICS...          \n";
    std::cout << "=========================================\n\n";
    
    std::cout << "Total Train Mass:    " << total_weight1 << " tonnes\n";
    std::cout << "Curve Resistance:    " << curve_resistance1 << " N/kN\n";
    std::cout << "Max Adhesion Force:  " << max_adhesion_force1 << " N\n";
    std::cout << "Converted Grade:     " << grade_convert1 << "\n";
    std::cout << "Sine of Angle:       " << sine_theta1 << "\n";

    return 0;
}