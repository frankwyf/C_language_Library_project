#include "interface.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
    if (argc<4){
        printf("Please resatrt and enter the name of the bookfile,userfile and loanfile.\n");
        exit(1);
    }
    else{
        int i,j,k;
        i=strlen(argv[1]);
        j=strlen(argv[2]);
        k=strlen(argv[3]);
        bookfile=(char *)malloc(sizeof(char)*(i+1));
        Userfile=(char *)malloc(sizeof(char)*(j+1));
        loanfile=(char *)malloc(sizeof(char)*(k+1));
        strcpy(bookfile,argv[1]);
        strcpy(Userfile,argv[2]);
        strcpy(loanfile,argv[3]);
    }
    time_t t;
    struct tm * lt;
    time (&t);//get Unix time
    lt = localtime (&t);//turn into time struct
	printf("Welcome to the librbay system!\nCurrent time is %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    run_system();
    return 0;
}