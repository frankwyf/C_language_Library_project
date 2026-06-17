#include "interface.h"
#include "book_management.h"
#include "user_management.h"
#include "management.h"

char *bookfile = NULL;
char *Userfile = NULL;
char *loanfile = NULL;

FILE *file = NULL;
BookList *lpointer = NULL;
const char *title = NULL;
const char *author = NULL;
unsigned int year = 0;

FILE *userfile = NULL;
Librarian *admin = NULL;
FILE *loan = NULL;
User *LoginCheck = NULL;
Book book = {0};

Loanlist *all = NULL;
