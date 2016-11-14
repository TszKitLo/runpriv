/*
	Tsz Kit Lo (912404574)
	ECS 153
	Lab 4
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
#include <time.h>


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
	// check sniff ownership
	if(sniff.st_uid != getuid()){
		std::cout << "Sniff is not owned by you" << std::endl;
		return false;
	}

	// check owner execution right
	if((sniff.st_mode & S_IXUSR) || (sniff.st_mode & S_IRWXU)){
        std::cout << "Sniff cannot be excuted by owner" << std::endl;
		return false;
    }

    // if user is not root
    if(getuid() != 0){
    	// check others rights
    	if(sniff.st_mode & S_IRWXO || sniff.st_mode & S_IROTH || sniff.st_mode & S_IWOTH || sniff.st_mode & S_IXOTH){
    		std::cout << "Sniff can be excuted by owner only" << std::endl;
			return false;
    	}
    }

    //Step 5
    time_t currentTime;
	time(&currentTime);

    if(difftime(currentTime, sniff.st_mtime) > 60){
    	std::cout << "Sniff is modified or reacted 1 minute ago" << std::endl;
		return false;
    }
    

	return true;
}

void chmodOwn(){
	// chown
	int msg = system("chown root:proj sniff");
	std::cout << msg << std::endl;

	// chmod
	if(chmod("./sniff",04550) != 0){
		std::cout << "Chmod error!" << std::endl;
	}
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

	// Step 6: change mod and own
	chmodOwn();	
    
    return 0;
}

