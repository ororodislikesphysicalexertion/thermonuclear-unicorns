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

void eighty(){ // safe, consistent 80 pt function :D

	enable_servos();
	gyro rawr;
   
    set_servo_position(0, 1937);
    
      rawr.angle_straight(22, 300); 
      rawr.turn_angle(132);
      rawr.angle_straight(10, -300);
      rawr.turn_angle(40);
      rawr.angle_straight(24, 300);
      rawr.turn_angle(120);
      rawr.turn_angle(-94.5);
    
    set_servo_position(0, 1024);
    msleep(1000);
    
    rawr.angle_straight(47, -300);
    rawr.turn_angle(77);
    rawr.angle_straight(110, 300);
    rawr.turn_angle(-75);
    rawr.angle_straight(35, 300);
    disable_servos();

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

void demobotSeedings(){

    enable_servos();
	gyro rawr;
    set_servo_position(0, 558);
    
      rawr.angle_straight(22, 300); 
      rawr.turn_angle(132);
      rawr.angle_straight(10, -300);
      rawr.turn_angle(40);
      rawr.angle_straight(24, 300);
      rawr.turn_angle(83);
    
	set_servo_position(0, 1260);
    
    rawr.angle_straight(55, 400); 
    rawr.turn_angle(110);
    rawr.turn_angle(-33);
    rawr.angle_straight(5, 200);
    
    set_servo_position(0, 440);
    
    rawr.angle_straight(30, 200);
    set_servo_position(0, 1477);
    msleep(500);
    disable_servos();

   

}

int main(int argc, const char * argv[]) {
    
    initial();
    wait_for_light();
    shut_down_in(119);
    demobotSeedings();
   
  //  std::cout << "Print gyro value: " << rawr.gyro_r() << std::endl;
    
    
    return 0;
}


