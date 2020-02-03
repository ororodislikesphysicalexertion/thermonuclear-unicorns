//
//  main.cpp
//  botball2020
//
//  Created by QA on 1/5/20.
//  Copyright © 2020 oroni club. All rights reserved.
//

#include <iostream>
#include "gyro.hpp"
#include "misc.hpp"
#include <kipr/botball.h>

void initial();

int main(int argc, const char * argv[]) {
    
    initial();
    demobotSeedings();
   
  //  std::cout << "Print gyro value: " << rawr.gyro_r() << std::endl;
    
    
    return 0;
}

void demobotSeedings(){
    
    rawr.angle_turn(); // rotate so that demobot is towards coupler
    rawr.straight_angle(20, 200); // driving towards coupler
    rawr.angle_turn(pi/4); // pulling coupler out from beneath
    rawr.straight_angle(20, -200); // backs up with coupler
    rawr.angle_turn(pi); // rotates with couler towards water poms
    rawr.straight_angle(40, 300); // drives straight up to the water pom ledge

    rawr.straight_angle(40, -300); // goes back until it is bad at the ramp entrance
    rawr.angle_turn(pi/4);
    rawr.straight_angle(10, 150);
    rawr.angle_turn(-pi/4);
    rawr.straight_angle(35, 250); // goes up the ramp
    rawr.angle_turn(-pi/4); // dp I want to use this or a touch sensor? anyways, demobot turns to go on bridge
    rawr.straight_angle(30, 200); // drives straight slowly while a mechanism pushes water poms into coupler below
    
}

void createSeedings(){

create_connect();
  
    gyro rawr;
    
    rawr.create_straight(10, 200);// out of starting box
    rawr.turn_angle(-90);// turn towards bridge
    rawr.create_straight(10, 200); // move towards bridge
    
    //servo repositioning stuff
    
    rawr.create_straight(7, 170); //under bridge, stops in front of cube blocks
    
    // sensor stuff
    
    rawr.create_straight(7, 170); // back up till it's in front of bridge again
    rawr.turn_angle(90)// turn towards black processor
    rawr.create_straight(5, 100); // move towards black processor
    rawr.turn_angle(-90); // turn towards ore storage
    rawr.create_straight(10, 200); // moves straighttowards ore storage while sweeping the tiny ore boxes
    
    create_disconnect();
    
}

