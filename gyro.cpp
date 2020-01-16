//
//  gyro.cpp
//  botball2020
//
//  Created by QA on 1/5/20.
//  Copyright © 2020 oroni club. All rights reserved.
//

#include "gyro.hpp"
#include "misc.hpp"
#include <kipr/botball.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <chrono>

//finding the bias

using n_time = std::chrono::high_resolution_clock;
    n_time::time_point c_time = n_time::now();
    n_time::time_point start;

    
    int gyro::gyro_r(){
        double n_readings = 100;
        std::vector<double> gyro_reading;
        for(int i = 0; i < n_readings; i++) {
            
            gyro_reading.push_back(gyro_z());
            msleep(1);
            
        }
        
        average = std::accumulate(gyro_reading.begin(), gyro_reading.end(), 0.0) / n_readings;
        
        for(float i : gyro_reading){
            bias = sqrt(((i-average) * (i-average)) / n_readings);
        }
        
        return average;
    }

    
//----------------------------------------------------------------------
    
    int gyro::angle_add (){
        
        double angle_pos = std::abs((gyro_z() - average)) * 10;
        return angle_pos;
    }
    
//----------------------------------------------------------------------

    // this one kinda sucks

    void gyro::turn(double t_theta, int l_speed, int r_speed){ //fix
        
        double theta = 0.0;
        mav(0, l_speed);
        mav(3, r_speed);
        do{
            msleep(10);
            theta += angle_add();
        }
        while(theta < t_theta);
        
        drive(0, 0);
        msleep(200);
    }

// this one works!!!!! yaaaaayyyy :)))

    void gyro::turn_angle(int angleDegrees) { // positive is counterclockwise, negative is clockwise
        double DEG_TO_RAD = 600;
         double gyroCurrent = 0;
        
        int direction = angleDegrees < 0 ? -1 : 1;
        
        drive(direction * 300, -direction * 300);
        
        if(angleDegrees < 0){
                while (gyroCurrent >=  angleDegrees * DEG_TO_RAD) { // no point in multiplying angleDegress with direction
                    gyroCurrent -= std::abs(gyro_z()); // subtract for negative degrees, add for positive degrees
                    std::cout << gyroCurrent << std::endl;
                    msleep(10);
                }
        }
        
        else if(angleDegrees > 0){
            while (gyroCurrent <=  angleDegrees * DEG_TO_RAD) { // no point in multiplying angleDegress with direction
                    gyroCurrent += std::abs(gyro_z()); // subtract for negative degrees, add for positive degrees
                    std::cout << gyroCurrent << std::endl;
                    msleep(10);
                }
        }
        drive(0, 0);
         msleep(1000);
    }


    
//----------------------------------------------------------------------
    
    // needs to be fixed and tested

    inline double gyro::correction (double angle){
        
        double c = angle * expm1(angle);
        return c;
    }

//----------------------------------------------------------------------

    
    auto gyro::duration(){
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(c_time - start).count();
    }
    
    //unnecessary
    double gyro::c_angle() {
        
        double theta = 0.0;
        const double con = 2600; //fix conversion might not be accurate
        return theta / con;
        
    }

    // idk if this function works or makes sense   
    void gyro::straight (double distance, double velocity){
        
        double i_angle = c_angle();
        double d_angle = c_angle() - i_angle;
        double t_time = std::abs(distance / velocity);
        
        while(duration() < t_time)
            angle_add();
        if(c_angle() > i_angle){
            double speed_1 = velocity * (1 + correction(d_angle));
            double speed_2 = velocity * (1 - correction(d_angle));
            drive(speed_1, speed_2);
        }
        else if(c_angle() < i_angle){
            double speed_1 = velocity * (1 - correction(d_angle));
            double speed_2 = velocity * (1 + correction(d_angle));
            drive(speed_1, speed_2);
        }
        
        drive(0, 0);
    }

    //i hope this one works and makes sense
    void gyro::angle_straight(int distance, int speed){ //enter distance in cm, it gets multiplied by 95.1 to convert to KIPR units
    	double TO_CM = 95.1; //found motor position ticks per centimeter
        int time = (TO_CM * distance) / speed;
        const int initialAngle = 0;
        int differenceAngle = std::abs(initialAngle - gyro_z());
        
        if(differenceAngle > initialAngle){
        	double speed_1 = speed * (1 + differenceAngle);
        	double speed_2 = speed * (1 - differenceAngle);
        	drive(speed_1, speed_2);
            msleep(time);
        }
        
        if(differenceAngle < initialAngle){
        	double speed_1 = speed * (1 - differenceAngle);
        	double speed_2 = speed * (1 + differenceAngle);
        	drive(speed_1, speed_2);
            msleep(time);
        }
    }

    
    



