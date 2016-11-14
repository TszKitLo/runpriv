/*
	Tsz Kit Lo (912404574)
	ECS 153
	Lab 2
*/


#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cctype>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


bool isCreatedByMe(){

	struct stat sb;
	if(stat("./runpriv", &sb) != 0){
		std::cout << "stat() error" << std::endl;
		return false;
	}

	if(sb.st_uid != getuid()){
		std::cout << "Compared Real UID. You are not authorized to use this program." << std::endl;
		return false;
	}

	return true;

	
}

int main()
{	
	// Step 1: Compare real UID of the process to the student
	if(!isCreatedByMe()){
		
		return 0;
	}

	// Step 2: Check password
	int msg = system("kinit");
	std::cout << msg << std::endl;


	std::cout << "Success" << std::endl;
    
    return 0;
}

