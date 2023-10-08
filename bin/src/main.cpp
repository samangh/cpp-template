#include <stdio.h>
#include <iostream>

#include "template/test.h"

#ifdef WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int, char**)
{
    std::cout << "Hello" <<std::endl;
	test();
    return 0;
}

