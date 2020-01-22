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

int main(int argc, const char * argv[]) {
    
    // turning function testing
    
    gyro rawr;
    rawr.angle_turn(90);
    rawr.angle_turn(45);
    rawr.angle_turn(45);
    std::cout << "Print gyro value: " << rawr.gyro_r() << std::endl;
    
    
    return 0;
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

