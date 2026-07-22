#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>
using namespace std;
int main (){
    double velocity;// Auto assign to the value 0
    double pos;
    double time;
    double acc;
    double dt = 0.1;
    while (true){
        velocity += acc*dt;
        pos += pos*dt;
        cout << "velocity "<< velocity;
        cout << "time"<< time;
        cout << "position "<< pos;
        
    }
}