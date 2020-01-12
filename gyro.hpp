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
    void angle_turn(int angleTheta);
    inline double correction (double angle);
    auto duration();
    virtual double c_angle();
    void straight (double distance, double velocity);

};



//#endif /* gyro_hpp */
