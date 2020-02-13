//
//  misc.cpp
//  botball2020
//
//  Created by QA on 1/5/20.
//  Copyright © 2020 oroni club. All rights reserved.
//

#include "misc.hpp"
#include "gyro.hpp"
#include <iostream>
#include <kipr/botball.h>


void drive(double ls, double rs){
    
    mav(0, ls);
    mav(3, rs);
    }

void initial(){
  
    gyro rawr;
    
    rawr.turn_angle(90);
    rawr.turn_angle(-90);
    
    while(digital(0) != 1){
        drive(200, 200);
    }
    
    rawr.angle_straight(2, -100);
    rawr.turn_angle(90);
    
    while(analog(0) < 4000){
        drive(200, 200);
    }
    rawr.angle_straight(5, -150);
    rawr.turn_angle(90);
    rawr.turn_angle(-90);
}
