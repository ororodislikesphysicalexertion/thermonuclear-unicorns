//
//  misc.cpp
//  botball2020
//
//  Created by QA on 1/5/20.
//  Copyright © 2020 oroni club. All rights reserved.
//

#include "misc.hpp"
#include <iostream>
#include <kipr/botball.h>


void drive(double ls, double rs){
    
    mav(0, ls);
    mav(3, rs);
    }

