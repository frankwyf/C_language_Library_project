#ifndef MANAGEMENT_GUARD__H 
#define MANAGEMENT_GUARD__H

#include <stdio.h>

typedef struct _Loan {
    unsigned int user; //user ID
    unsigned int bookid; //Book ID
	char *title; //book title
	char *authors; //comma separated list of authors
	unsigned int year; // year of publication
	unsigned int copies; //number of copies the library has
	struct _Loan *next; //pointer to the next book element
}Loan;

typedef struct _Loanlist {
    Loan *loanlist;//the list of loan informations
    unsigned int total;//the legth of loanlist
}Loanlist;

extern Loanlist *all;//the linked list use to load all users' borrowed books

int load_all_loans(FILE *loan);/* the function to load all the loans into a linked list
can be used in return book (updating the loan file), loan management (for the librarian) */

int store_loans(FILE *loan);/* the function to rewrite the loan file with the updated loan list*/

/*the funtion is provided for librarians to manage the back end of the system
it requires to login as the librarian and supports the fuction of mananging the loan information 
Also, it allows the manager to manage registered users of the system*/
int backend_management(FILE *userfile);

void print_all_users();//print all the registered users
void print_all_loans();//print all loan information
int remove_users();//fuvntion used to remove a user form the userfile
int remove_loans();//function to remove a loan record,can be used when user return book is mulfunctioning
#endif