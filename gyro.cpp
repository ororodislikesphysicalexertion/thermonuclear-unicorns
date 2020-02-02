//
//  gyro.cpp
//  botball
//
//  Created by QA on 5/29/19.
//  Copyright B) 2019 oroni club. All rights reserved.
//

#include "gyro.hpp"
#include "misc.hpp"
#include <kipr/botball.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <chrono>



//clock stuff

using n_time = std::chrono::high_resolution_clock;
    n_time::time_point c_time = n_time::now();
    n_time::time_point start = n_time::now();


auto gyro::duration(){
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(c_time-start).count();
    }



//	auto currentTime = std::chrono::system_clock::now();
//	auto cTime = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

//----------------------------------------------------------------------


	//finding the gyro bias
    
    int gyro::gyro_r(){
        double n_readings = 100;
        std::vector<double> gyro_reading;
        for(int i = 0; i < n_readings; i++) {
            
            gyro_reading.push_back(gyro_z());
          //  std::cout<< gyro_z() <<std::endl;
            msleep(1);
            
        }
        
        average = std::accumulate(gyro_reading.begin(), gyro_reading.end(), 0.0) / n_readings;
        
        for(float i : gyro_reading){
            bias = sqrt(((i-average) * (i-average)) / n_readings);
        }
        
        return average;
    }

    
//----------------------------------------------------------------------
    
// incremental function

    int gyro::angle_add (){ 
        
        double angle_pos = std::abs(gyro_z() - average) * 10;
        return angle_pos;
    }
    
//----------------------------------------------------------------------

//turn function

// this one doesn't work and sucks
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

//this one works and is awesome, just needs some conversion value adjustments
void gyro::turn_angle(int angleDegrees) { // positive is counterclockwise, negative is clockwise
        double DEG_TO_RAD = 600;
     	double gyroCurrent = 0;
        
        int direction = angleDegrees < 0 ? -1 : 1;
        
        drive(direction * 300, -direction * 300);
        
        if(angleDegrees < 0){
       		 while (gyroCurrent >=  angleDegrees * DEG_TO_RAD) { // no point in multiplying angleDegress with direction
           		 gyroCurrent -= angle_add(); // subtract for negative degrees, add for positive degrees
           		 std::cout << gyroCurrent << std::endl;
           		 msleep(10);
       		 }
        }
        
        else if(angleDegrees > 0){
        	while (gyroCurrent <=  angleDegrees * DEG_TO_RAD) { // no point in multiplying angleDegress with direction
           		 gyroCurrent += angle_add(); // subtract for negative degrees, add for positive degrees
           		 std::cout << gyroCurrent << std::endl;
           		 msleep(10);
       		 }      
        }
        drive(0, 0);
     	msleep(1000);
    }	
    
//----------------------------------------------------------------------

//curve function to make robot straight

    inline double gyro::correction (double angle){
        
        double c = angle * exp(angle);
        return c;
    }

//----------------------------------------------------------------------
  
//useless conversion function ngl
    double gyro::c_angle() {
        
        double theta = 0.0;
        const double con = 53800; 
        return theta / con;
        
    }

//----------------------------------------------------------------------
    
//straight function

// this function WORKS
void gyro::angle_straight(int distance, int speed){ //enter distance in cm, it gets multiplied by 95.1 to convert to KIPR units
    	double TO_CM = 95.1; //found motor position ticks per centimeter
        int time = ((TO_CM * distance) / std::abs(speed)) * 1000; // milliseconds
        double currentAngle = 0;
    //    int differenceAngle = std::abs(initialAngle - gyro_z());
        
        while(duration() < time){
        
        if(speed > 0){
            //try with normal values first, like 10
        	double speed_1 = speed * (1 + correction(currentAngle));
        	double speed_2 = speed * (1 - correction(currentAngle));
        	drive(speed_1, speed_2);
            
        }
        
        else{
        	double speed_1 = speed * (1 - correction(currentAngle));
        	double speed_2 = speed * (1 + correction(currentAngle));
        	drive(speed_1, speed_2);
            
        }
            msleep(time);
            currentAngle += angle_add();
        }
					  
	drive(0, 0);
        msleep(1000);
    }

    
    //----------------------------------------------------------------------


void gyro::create_straight(int distance, int speed){ //enter distance in cm, it gets multiplied by 95.1 to convert to KIPR units
    	double TO_CM = 95.1; //found motor position ticks per centimeter
        int time = ((TO_CM * distance) / std::abs(speed)) * 1000; // milliseconds
        
        create_drive_straight(speed);
	msleep(time);
        
    }



