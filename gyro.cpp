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
        
        return bias;
    }

    
//----------------------------------------------------------------------
    
    int gyro::angle_add (){ //fix
        
        double angle_pos = std::abs((gyro_z() - bias)) * msleep(1);
        return angle_pos;
    }
    
//----------------------------------------------------------------------


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

    
//----------------------------------------------------------------------
    
    inline double gyro::correction (double angle){
        
        double c = angle * expm1(angle);
        return c;
    }

//----------------------------------------------------------------------

    
    auto gyro::duration(){
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(c_time - start).count();
    }
    
    double gyro::c_angle() {
        
        double theta = 0.0;
        const double con = 0.0; //fix conversion value
        return theta / con;
        
    }
    
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

    
    



