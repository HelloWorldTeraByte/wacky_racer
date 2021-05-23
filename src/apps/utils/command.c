#include "command.h"
#include "stdlib.h"
#include "string.h"


struct Command create_command(char cmd, int arg1 , int arg2){
    struct Command command = 
    {
        .cmd = (int) cmd,
        .arg1 = arg1,
        .arg2 = arg2
    };
    return command;
}

//This function is working properly! confirmed by hank! atoi should be able to deal with negative numbers.
struct Command str2cmd(char* buffer)
{
    
	char delim[] = SEPERATOR;
	char *ptr = strtok(buffer, delim);

    int val[3]; //buffer for values.
    
    int i = 0;
	while (ptr != NULL)
	{
        val[i] = atoi(ptr);
		ptr = strtok(NULL, delim);
        i++;
	}
    return create_command(val[0], val[1], val[2]);
}


