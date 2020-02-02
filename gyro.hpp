//
//  gyro.hpp
//  botball2020
//
//  Created by QA on 1/5/20.
//  Copyright © 2020 oroni club. All rights reserved.
//

//#ifndef gyro_hpp
//#define gyro_hpp


#pragma once
#include <stdio.h>
#include <iostream>
#include <kipr/botball.h>

class gyro{
    double bias = 0.0;
    double average = 0.0;
    public:
    int gyro_r();
    int angle_add();
    void turn(double t_theta, int l_speed, int r_speed);
<<<<<<< HEAD
    void angle_turn(int angleTheta);
=======
    void turn_angle(int angleDegrees);
>>>>>>> jll
    inline double correction (double angle);
    auto duration();
    virtual double c_angle();
    void straight (double distance, double velocity);
    void angle_straight(int distance, int speed);
    void create_straight(int distance, int speed);


};



//#endif /* gyro_hpp */
