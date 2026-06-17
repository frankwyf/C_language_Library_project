//This us the head file for interface
#ifndef INTERFACE_GUARD__H 
#define INTERFACE_GUARD__H
void run_system();//run main interface
char *user_input(const char *input);//used for getting user input for choices

/*the following are three poinetrs to read in the commandline arguments 
that provids the system with a bookfile(library),userfile(user information) 
and a loan file(loan information)*/
extern char *bookfile;
extern char *Userfile;
extern char *loanfile;
#endif