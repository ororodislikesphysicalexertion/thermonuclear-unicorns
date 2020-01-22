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

//create hard code
create_connect();
  enable_servos();
  set_servo_position(0, 1024);
  msleep(1000);
  create_drive_straight(-100);
  msleep(2000);
  create_drive_straight(0);
  msleep(1000);
  set_servo_position(1, 288);
  msleep(1000);
  create_drive_straight(-100);
  msleep(3000);
  set_servo_position(1, 1248);
  msleep(1000);
  create_drive_straight(-75);
  msleep(500);
  set_servo_position(0, 1486);
  msleep(1500);
  create_drive_straight(-50);
  msleep(1000);
  set_servo_position(0, 1020);
  msleep(1000);
  disable_servos();
  create_disconnect();

