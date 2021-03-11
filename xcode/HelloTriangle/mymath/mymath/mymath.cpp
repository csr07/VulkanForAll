//
//  mymath.cpp
//  mymath
//
//  Created by Cesar Gomez on 03/03/21.
//

#include <iostream>
#include "mymath.hpp"
#include "mymathPriv.hpp"

const char* mymath::HelloWorld(const char * s)
{
    mymathPriv *theObj = new mymathPriv;
    const char* str = theObj->HelloWorldPriv(s);
    delete theObj;
    return str;
};

const char* mymathPriv::HelloWorldPriv(const char * s)
{
    std::cout << s << std::endl;
    char greet[] = "Holi ";
    return strcat(greet, s);
};

