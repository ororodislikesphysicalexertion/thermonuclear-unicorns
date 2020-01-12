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
