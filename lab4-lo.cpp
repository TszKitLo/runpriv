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

bool checkPwd(){
	int msg = system("kinit");
	std::cout << msg << std::endl;

	return true;
}

bool checkSniff(){

	// Step 3
	struct stat sniff;
	if(stat("./sniff", &sniff) != 0){
		std::cout << "sniff not found" << std::endl;
		return false;
	}

	//Step 4
	

	return true;
}

int main()
{	
	// Step 1: Compare real UID of the process to the student
	if(!isCreatedByMe()){
		
		return 0;
	}

	// Step 2: Check password
	if(!checkPwd()){
		
		return 0;
	}

	// Step 3,4,5: Check sniff existence, ownership and modification time
	if(!checkSniff()){
		
		return 0;
	}



	std::cout << "Success" << std::endl;
    
    return 0;
}

