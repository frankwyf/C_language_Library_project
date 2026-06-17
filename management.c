#include "interface.h"
#include "user_management.h"
#include "book_management.h"
#include "management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>



#define Createuser(p) p=(User *)malloc(sizeof(User));
#define Createlibrarian(p) p=(Librarian *)malloc(sizeof(Librarian));
#define Createloan(p) p=(Loan *)malloc(sizeof(Loan));
#define Createloanlist(p) p=(Loanlist *)malloc(sizeof(Loanlist));





//the funtion is used to load all loan information form the loan file
//used when user is returning book
//read out the whole loan file,returns 0 if success, else return 1
int load_all_loans(FILE *loan){
	loan=fopen(loanfile,"r");
	if (loan==NULL){
		printf("File cannot open!\n");
		return 1;
	}
	else{
		Loan *p,*last;
        Createloanlist(all);
		Createloan(all->loanlist);//creat the header node
        all->total=0;
		last=all->loanlist;
		char temp[1024];//read in a whole line form the text file
		memset(temp, '\0', 1024);//initialize the temp string
		char *frtn=fgets(temp,sizeof(temp),loan);
		if (frtn==NULL){
			printf("\nThe loan file is empty! Borrow some book first!\n");
			return 1;
		}
		int i=strlen(temp);
		temp[i-1]='\0';//delete the '/n' at the end of the line
		int line=1;//show error message if something worng happened
		while (frtn != NULL){//read file till the end (an empty line)
		    Createloan(p);//create the first real node
			char *ptr=strtok(temp,",");//cut the input string by comma
			int row=0;
			int len;// the length of a piece of data
			int index;//the index of the character in the char pointer
			while (ptr != NULL){
				switch (row){//copying data into the data part in a node
                    case 0:
					    len=strlen(ptr);
	                    for (index=0;index<len;index++){
		                    if (!isdigit(ptr[index])){
			                    printf("\nSome thing worng with the user ID of line %i in loan file.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
                        p->user=atoi(ptr);
					    break;
					case 1:
					    len=strlen(ptr);
	                    for (index=0;index<len;index++){
		                    if (!isdigit(ptr[index])){
			                    printf("\nSome thing worng with the book ID of line %i in loan file.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
					    p->bookid=atoi(ptr);
					    break;
					case 2:
					    p->title=ptr;
						int i;
						i=strlen(p->title);
						p->title=(char *)malloc((size_t)i + 1);
						strcpy(p->title,ptr);
					    break;
					case 3:
					    len=strlen(ptr);
	                    for (index=0;index<len;index++){
		                    if (isspace(ptr[index])){
								index+=1;//ignore the space in title
							}
		                    if (!isalpha(ptr[index])){
			                    printf("\nSome thing worng with the author of line %i in loan file.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
					    p->authors=ptr;
						int j;
						j=strlen(p->authors);
						p->authors=(char *)malloc((size_t)j + 1);
						strcpy(p->authors,ptr);
					    break;
					case 4:
					    len=strlen(ptr);
	                    for (index=0;index<len;index++){
		                    if (!isdigit(ptr[index])){
			                    printf("\nSome thing worng with the year of line %i in loan file.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
					    p->year=atoi(ptr);
					    break;
					case 5:
					    len=strlen(ptr);
	                    for (index=0;index<len;index++){
		                    if (!isdigit(ptr[index]) || atoi(ptr)!=1){//every user can only borrow 1 copy of each book
			                    printf("\nSome thing worng with the copy number of line %i in loan file.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
					    p->copies=atoi(ptr);
					    break;
				}
				row+=1;
				ptr=strtok(NULL,",");
			}
            all->total+=1;//add the length of all by 1 
			p->next=NULL;
			last->next=p;
			last=p;//iserting a new node into the linked list
			line+=1;
		    memset(temp, '\0', 1024);
            frtn = fgets(temp,sizeof(temp),loan);//read in the second line
		    if (frtn != NULL) {
		    	int j=strlen(temp);
		    	temp[j-1]='\0';//delete the '/n' at the end of the line
		    }
		}
		fclose(loan);
		return 0;
	}	
}
/*this function is used to store the data after retrun a book
it rewrites the loan file with the updated loan list */

int store_loans(FILE *loan){
	loan=fopen(loanfile,"w");
	if (loan==NULL){
		printf("\nLoan file is missing!\n");
		return 1;
	}
	else{
		Loan *store,*final;
	    final=all->loanlist;
	    Createloan(store);
	    store=final->next;
	    unsigned int list_long=0;
	    while (list_long<all->total){
		    fprintf(loan,"%i,%i,%s,%s,%i,%i\n",store->user,store->bookid,store->title,store->authors,store->year,store->copies);
		    final=store;
		    store=store->next;
			free(final);
		    list_long+=1;
	    }
        fclose(loan);
		return 0;//showing success of store books
	}
}

//the function that read in the whole list of users and display them
void print_all_users(){
	printf("The first user is yourself(the librarian).\n");
	printf("UserID");
	printf("%*s",10," ");
	printf("Name");
	printf("%*s",20," ");
	printf("Username");
	printf("%*s",16," ");
	printf("Password\n");
	User *printall;
	printall=admin->UserList->next->next;
	while(printall!=NULL){
		printf("%-8i\t%-22s\t%-22s\t%-20s\n",printall->id,printall->name,printall->username,printall->password);//output formates
		printall=printall->next;
	}
}

void print_all_loans(){
	if (load_all_loans(loan)==0){
		printf("UserID");
	    printf("%*s",10," ");
	    printf("BookID");
	    printf("%*s",10," ");
	    printf("Title");
	    printf("%*s",19," ");
	    printf("Author");
	    printf("%*s",18," ");
	    printf("Year");
 	    printf("%*s",12," ");
	    printf("Copies\n");
	    Loan *all_loan;
	    all_loan=all->loanlist->next;
	    while(all_loan!=NULL){
		    printf("%-8i\t%-8i\t%-22s\t%-20s\t%-8i\t%-8i\n",all_loan->user,all_loan->bookid,all_loan->title,all_loan->authors,all_loan->year,all_loan->copies);//output formates
		    all_loan=all_loan->next;
	    }
	}
	else{
		printf("\nSomething wrong with the loan information!\n");
		return;
	}
}
//function used to write the new user list into userfile
int store_users(FILE *loan){
	loan=fopen(Userfile,"w");
	if (loan==NULL){
		printf("\nFatal error! Book file is missing!\n");
		return 1;
	}
	else{
		User *store,*final;
	    final=admin->UserList;
	    Createuser(store);
	    store=final->next;
	    unsigned int user_long=0;
	    while (user_long<admin->users){
		    fprintf(loan,"%i,%s,%s,%s\n",store->id,store->name,store->username,store->password);
		    final=store;
		    store=store->next;
		    user_long+=1;
	    }
		fclose(loan);
		return 0;//showing success of store books
	}
}

//fuvntion used to remove a user form the userfile
int remove_users(){
	printf("Enter the id of the user you want to remove: ");
	char *remove_user=(char *)malloc(sizeof(int)*10+sizeof(char));//the maxium length of a id maybe 10 digits + one for the '\n'
	fgets(remove_user,51,stdin);
	int a=strlen(remove_user);
	remove_user[a-1]='\0';//get rid of the '\n' at the last of the input
	int b;
	for (b=0;b<a-1;b++){
		if (!isdigit(remove_user[b])){
			printf("\nThis is an invalid user id!\n");
			return 1;
		}
		else{continue;}
	}
	unsigned int user=(unsigned int)atoi(remove_user);
	if (user>admin->users || user<2){//can't remove the librarian
		printf("\nID out of range! Please re-enter.\n");
		return 1;
	}
	//remove the user from the user list
	User *removeuser,*ending;
	removeuser=admin->UserList;
	while (removeuser->next!=NULL){
		ending=removeuser;
		removeuser=removeuser->next;
		if (user==removeuser->id){
			ending->next=removeuser->next;
			free(removeuser);
			removeuser=ending->next;
			printf("\nUser(ID): %i has been removed.\n",user);
			free(remove_user);
			admin->users=admin->users-1;//reduce the loan 
			//rewrite the userfile
			store_users(loan);
			return 0;
		}
	}
	printf("\nUser not found.\n");
	return 1;
}

//function to remove a loan record,can be used when user return book is mulfunctioning
int remove_loans(){
	if (load_all_loans(loan)==0){
		printf("Enter the id of the user: ");
	    char *remove_loan=(char *)malloc(sizeof(int)*10+sizeof(char));//the maxium length of a id maybe 10 digits + one for the '\n'
	    fgets(remove_loan,51,stdin);
	    int a=strlen(remove_loan);
	    remove_loan[a-1]='\0';//get rid of the '\n' at the last of the input
	    int b;
	    for (b=0;b<a-1;b++){
		    if (!isdigit(remove_loan[b])){
			    printf("\nThis is an invalid user id!\n");
			    return 1;
		    }
		    else{continue;}
	    }
		unsigned int ruserid=(unsigned int)atoi(remove_loan);
		if (ruserid>admin->users || ruserid<2){//librarian can't borrow a book
		    printf("\nUser ID out of range! Please re-enter.\n");
		    return 1;
	    }
		//get the id of the book (since a user may have multiple loans)
		printf("Enter the id of the book: ");
	    char *remove_id=(char *)malloc(sizeof(int)*10+sizeof(char));//the maxium length of a id maybe 10 digits + one for the '\n'
	    fgets(remove_id,51,stdin);
	    int x=strlen(remove_id);
	    remove_id[x-1]='\0';//get rid of the '\n' at the last of the input
	    int y;
	    for (y=0;y<x-1;y++){
		    if (!isdigit(remove_id[y])){
			    printf("\nThis is an invalid user id!\n");
			    return 1;
		    }
		    else{continue;}
	    }
		unsigned int rbookid=(unsigned int)atoi(remove_id);
		if (rbookid>lpointer->length || rbookid<2){//librarian can't borrow a book
		    printf("\nBook ID out of range! Please re-enter.\n");
		    return 1;
	    }
		//remove the loan from the loan list
	    Loan *remove,*ending;
	    remove=all->loanlist;
	    while (remove->next!=NULL){
		    ending=remove;
		    remove=remove->next;
		    if (ruserid==remove->user && rbookid==remove->bookid){
			    ending->next=remove->next;
			    free(remove);
			    printf("\nLoan reocrd user(ID): %i  book(ID):%i has been removed.\n",ruserid,rbookid);
			    free(remove_id);
				free(remove_loan);
			    all->total=all->total-1;//reduce the loan 
			    //rewrite the userfile
			    store_loans(loan);
			    return 0;
		    }
	    }
		printf("\nLoan record not found.\n");
		free(remove_id);
		free(remove_loan);
		return 1;
	}
	else{
		printf("Failed to laod loan infromation.\n");
		return 1;
	}
}

int backend_management(FILE *userfile){
	if (load_users(userfile)==0){//load in the user file to check whether it is the librarian or not
	    printf("\nWelcome to the backend system!\n\nPlease login as the librarian.\n");
		printf("Please enter username(less than 100 characters): ");
        char *username=(char *)malloc(sizeof(char)*100);//the maxium length of a username maybe 50 characters
	    fgets(username,100,stdin);
	    int i=strlen(username);
	    username[i-1]='\0';//get rid of the '\n' at the last of the input
        printf("Please enter password(no more than 10 letters or 10 intergers): ");
        char *password=(char *)malloc(sizeof(char)*30);//the maxium length of a password maybe 30 characters
	    fgets(password,50,stdin);
	    int j=strlen(password);
	    password[j-1]='\0';//get rid of the '\n' at the last of the input

		User *administor;//serve as a check for user login, also aused as the identity of the user in user system
        administor=admin->UserList->next;
		if (strcmp(administor->username,username)==0 && strcmp(administor->password,password)==0 && administor->id==1){//librarian log in
		    time_t t;
            struct tm * lt;
            time (&t);//get Unix time
            lt = localtime (&t);//turn into time struct
			printf("\nSuccessfully logged in as Librarian: %s at %d/%d/%d %d:%d:%d\n",administor->username,lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			//interface for librarian usage
            int bchoice = 5; //exit
	        do {
	            char * answer = user_input("\nPlease choose an option:\n1) Show all registered users \n2) Remove users \n3) Display all loans \n4) Remove loans\n5) Quit\nOption: ");
	            bchoice = atoi(answer);
                free(answer);
		        switch (bchoice) {
		            case 1:
		                print_all_users();
		                break;
		            case 2:
			            remove_users();
			            break;
			        case 3:
			            print_all_loans();
			            break;
		            case 4:
		                remove_loans();
		                break;
					case 5:
					    time (&t);//get Unix time
                        lt = localtime (&t);//turn into time struct
				        printf("\nRequest to log out at %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			            printf("\nThank you Manager: %s!\nLoging you out...\n\n",administor->username);
			            break;
		            default:
		                printf("\nSorry, the option you entered was invalid, please try agian.\n");
                } 
            } while (bchoice != 5);
		}
        else{
		    printf("\nInvalid librarian!\n");
			free(username);
			free(password);
				return 1;
	    }
		free(username);
		free(password);
		return 0;
	}
	return 1;
}