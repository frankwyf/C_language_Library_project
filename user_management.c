#include"interface.h"
#include"user_management.h"
#include"book_management.h"
#include "management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define CreateNode(p) p=(Book *)malloc(sizeof(Book));
#define Booklist(p) p=(BookList *)malloc(sizeof(BookList));
#define Createuser(p) p=(User *)malloc(sizeof(User));
#define Createlibrarian(p) p=(Librarian *)malloc(sizeof(Librarian));
#define Showlist(p) p=(ShowList *)malloc(sizeof(ShowList));
#define Createloan(p) p=(Loan *)malloc(sizeof(Loan));


//load the users into the linked list
//Librarian also serve as the head node of the user linked list
int load_users(FILE *userfile){
    userfile=fopen(Userfile,"r");
    if (userfile==NULL){
        printf("Failed to load the user file! Please contact the librarian.\n");
        exit(-1);
    }
    else{
        printf("\nWelcom to user system!\n\n");
        User *p,*last;
        Createlibrarian(admin);//set the linked list node of librarain
        Createuser(admin->UserList);
        last=admin->UserList;
        char tem[1024];//read in a whole line form the text file
	    memset(tem, '\0', 1024);//initialize the temp string
	    char *pt=fgets(tem,sizeof(tem),userfile);
		if (pt==NULL){
			printf("\nThe user file is empty! Register an account first!\n");
			return 1;
		}
	    int i=strlen(tem);
		tem[i-1]='\0';//delete the '/n' at the end of the line
		int line=1;//show error message if something worng happened
	    while (pt != NULL){
            Createuser(p);
            char *data=strtok(tem,",");//cut the input string by comma
            int attributes=0;
			int len;// the length of a piece of data
		    int index;//the index of the character in the char pointer 
            while (data != NULL){
               switch (attributes){//copying data into the data part in a node
                    case 0:
					    len=strlen(data);
	                    for (index=0;index<len;index++){
		                    if (!isdigit(data[index])){
			                    printf("\nSome thing worng with the user ID of line %i.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
					    p->id=atoi(data);
					    break;
					case 1:
					    len=strlen(data);
	                    for (index=0;index<len;index++){
		                    if (isspace(data[index])){
								index+=1;//ignore the space in title
							}
		                    if (!isalpha(data[index])){
			                    printf("\nSome thing worng with the name(user) of line %i.\n",line);
			                    return 1;
		                    }
		                    else{continue;}
	                    }
					    p->name=data;
                        int i;
						i=strlen(p->name);
						p->name=(char *)malloc((size_t)i + 1);
						strcpy(p->name,data);
					    break;
					case 2:
					    p->username=data;
                        int k;
						k=strlen(p->username);
						p->username=(char *)malloc((size_t)k + 1);
						strcpy(p->username,data);
					    break;
					case 3:
					    p->password=data;
						int j;
						j=strlen(p->password);
						p->password=(char *)malloc((size_t)j + 1);
						strcpy(p->password,data);
					    break;
				}
				attributes+=1;
				data=strtok(NULL,",");
			}
          	p->next=NULL;
			last->next=p;
			last=p;//iserting a new node into the linked list
			line+=1;//read in the next line
		    memset(tem, '\0', 1024);
            pt = fgets(tem,sizeof(tem),userfile);//read in the second line
		    int j=strlen(tem);
		    tem[j-1]='\0';//delete the '/n' at the end of the line
		}
		admin->users=last->id;//the length of the booklist
		fclose(userfile);
		return 0;
	}
}
//function to load the loan file
int load_loan(FILE *userfile,User *returnuser){
	(void)userfile;
	loan=fopen(loanfile,"r");
	if (loan==NULL){
		printf("Loan file cannot open!\n");
		return -1;
	}
	else{
		Book *p,*last;
		last=returnuser->borrowed->list;
		char try[1024];//read in a whole line form the text file
		memset(try, '\0', 1024);//initialize the temp string
		char *f=fgets(try,sizeof(try),loan);
		//when open a empty loan file
		if (f==NULL){
			printf("\nThe loan file is empty! Borrow some book first!\n");
			return 1;
		}
		//open a file in "a" prints a '\n' at first line
		if (f[0]=='\n'){
			memset(try, '\0', 1024);
		    f=fgets(try,sizeof(try),loan);
		}
		//skip this empty line since it doesn't has any meaning
		int i=strlen(try);
		try[i-1]='\0';//delete the '/n' at the end of the line
		returnuser->borrowed->length=0;//set the length to 0 everytime reads in from the fucntion
		int line=1;//show error message if something worng happened
		while (f != NULL){//read file till the end (an empty line)
		    CreateNode(p);//create the first real node
			char *t=strtok(try,",");//cut the input string by comma

			//only get the loan of the user who is currently logged in
			unsigned int Check_user=(unsigned int)atoi(t);
			if (Check_user==returnuser->id){
				returnuser->id=Check_user;//copying the user id to show data structure
				t=strtok(NULL,",");//read in real data
				int row=0;
				int len;// the length of a piece of data
			    int index;//the index of the character in the char pointer
			    while (t != NULL){
				    switch (row){//copying data into the data part in a node
					    case 0:
						    len=strlen(t);
	                        for (index=0;index<len;index++){
		                        if (!isdigit(t[index])){
			                        printf("\nSome thing worng with the book ID of line %i in loan file.\n",line);
			                        return 1;
		                        }
		                        else{continue;}
	                        }
					        p->id=atoi(t);
					        break;
					    case 1:
					        p->title=t;
						    int i;
						    i=strlen(p->title);
							    p->title=(char *)malloc((size_t)i + 1);
						    strcpy(p->title,t);
					        break;
					    case 2:
						    len=strlen(t);
	                        for (index=0;index<len;index++){
		                        if (isspace(t[index])){
								    index+=1;//ignore the space in title
							    }
		                        if (!isalpha(t[index])){
			                        printf("\nSome thing worng with the author of line %i in loan file.\n",line);
			                        return 1;
		                        }
		                        else{continue;}
	                        }
					        p->authors=t;
						    int j;
						    j=strlen(p->authors);
						    p->authors=(char *)malloc((size_t)j + 1);
						    strcpy(p->authors,t);
					        break;
					    case 3:
						    len=strlen(t);
	                        for (index=0;index<len;index++){
		                        if (!isdigit(t[index])){
			                        printf("\nSome thing worng with the year of line %i in loan file.\n",line);
			                        return 1;
		                        }
		                        else{continue;}
	                        }
					        p->year=atoi(t);
					        break;
					    case 4:
						    len=strlen(t);
	                        for (index=0;index<len;index++){
		                        if (!isdigit(t[index])){
			                        printf("\nSome thing worng with the year of line %i in the loan file.\n",line);
			                        return 1;
		                        }
		                        else{continue;}
	                        }
					        p->copies=atoi(t);
					        break;
				    }
				    row+=1;
				    t=strtok(NULL,",");
			    }
			    p->next=NULL;
			    last->next=p;
			    last=p;//iserting a new node into the linked list
				returnuser->borrowed->length+=1;//add 1 to the length of the borrowed book list of the particular user
			}
		    memset(try, '\0', 1024);
            f = fgets(try,sizeof(try),loan);//read in the second line
		    int j=strlen(try);
			try[j-1]='\0';//delete the '/n' at the end of the line
		}
		fclose(loan);
		return 0;
	}	
}


//funtion used for users to borrow a book
int borrow_book(User *borrowuser,FILE *loan){//borrow a book is user sensitive
    loan=fopen(loanfile,"a");
	printf("Enter the ID of the book you wish to borrow: ");
	char *str=(char *)malloc(sizeof(int)*5+sizeof(char));//the maxium length of a ID maybe is 4 digit(range from 0~99999) + one for the '\n'
	fgets(str,21,stdin);
	int i=strlen(str);
	str[i-1]='\0';//get rid of the '\n' at the last of the input
	int j;
	for (j=0;j<i-1;j++){
		if (!isdigit(str[j])){
			printf("\nThis is an invalid ID!\n");
			return 1;;
		}
		else{continue;}
	}
	unsigned int borrow_id=(unsigned int)atoi(str);//read in the ID for borrow operations 

	if (borrow_id>lpointer->length || borrow_id<1){
		printf("\nID out of range! Please re-enter.\n");
		return 1;
	}
	else{
		//check whether the user has borrowed a copy of the book
		load_loan(userfile,borrowuser);
		Book *repeat;
		repeat=borrowuser->borrowed->list;
		unsigned int step=0;
		while (step<=borrowuser->borrowed->length){
			if (repeat->id==borrow_id){
				printf("\nSorry! It seems that you have borrowed a copy of : %i,%s !\n",repeat->id,repeat->title);
				step+=1;
				return 1;
			}
			else{
				repeat=repeat->next;
				step+=1;
			}
		}
	    unsigned int loop=0;//for loop around the whole list
		Book *p,*end;
		end=lpointer->list;
	    while (loop<lpointer->length){
			//borrow operations
			CreateNode(p);
			p=end->next;
			if (p->id==borrow_id){
				//check whether there is an available copy
				if (p->copies==0){
					printf("\nSorry! There is no avaliable copies for borrowing!\n");
					return 1;
				}
				else{
					//copy the book to the user's loan file
				    fprintf(loan,"%i,%i,%s,%s,%i,%i\n",borrowuser->id,p->id,p->title,p->authors,p->year,1);
					//only need to know the userid book title and the yaer fir tarck of the book(even by search) 
				    p->copies=p->copies-1;//cut one from the libraray
			        borrowuser->borrowed->length+=1;//record the length of loan
				    loop+=1;
				    printf("\nYou have successfuly borrowed this book: %s!\n",p->title);
					fclose(loan);
				    return 0;
				}
			}
			else{
				end=p;
			    p=p->next;
			    loop+=1;
		    }
	    }
	}
	fclose(loan);
	return 1;
}

int return_book(User *returnuser,FILE *loan){//borrow a book is user sensitive
		if (load_loan(loan,returnuser)==0){
			//check whether the user have borrowed any books yet
            if (returnuser->borrowed->length==0){
			   	printf("\nYou haven't borrowed any book!\n");
				return 1;
		    }
			//if there is at least one loan record
			printf("\nBelow is the list of books you aer currently borrowing:\n\n");
		    print_title();
			Book *return_show;
			return_show=returnuser->borrowed->list->next;
			while(return_show!=NULL){
			    printf("%-2i\t%-39s\t%-22s\t%-8i\t%i\n",return_show->id,return_show->title,return_show->authors,return_show->year,return_show->copies);//output formates
		        return_show=return_show->next;
	        }
		}
		else{//fail to load loan
			printf("\nReturn system failed...\n");
			return 1;
		}
		//ask the user to enter the id of the book he/she wishes to return
		printf("\nEnter the ID number you want to return: ");
		char *str=(char *)malloc(sizeof(int)*5+sizeof(char));//the maxium length of a ID maybe is 4 digit(range from 0~99999) + one for the '\n'
	    fgets(str,21,stdin);
	    int i=strlen(str);
	    str[i-1]='\0';//get rid of the '\n' at the last of the input
	    int j;
	    for (j=0;j<i-1;j++){
		    if (!isdigit(str[j])){
			    printf("\nThis is an invalid ID!\n");
			    return 1;;
		    }
		    else{continue;}
	    }
	    unsigned int return_id=(unsigned int)atoi(str);//read in the ID for borrow operations

        //make sure the id is in range
		if (return_id>lpointer->length || return_id<1){
		    printf("\nID out of range! Please re-enter.\n");
		    return 1;
	    }

		/*return operation is presented below
        "return" the book to the library by adding the copies by 1
		delete the loan record in the loan file
		*/
		Book *returnp,*lastp;
		lastp=lpointer->list;
		CreateNode(returnp);
		returnp=lastp->next;
		while (returnp!=NULL){
			if (returnp->id==return_id){//find the book to be return
				returnp->copies+=1;//add the copy back to the book list
				returnuser->borrowed->length=returnuser->borrowed->length-1;//reduce the length of the user borrwed list
				//adjust the loan file
			    if (load_all_loans(loan)==0){//load in all the loans records
				    Loan *r,*last;
					last=all->loanlist;
					Createloan(r);
					r=last->next;
					while (r!=NULL){
						if (return_id==r->bookid){
							last->next=r->next;
							free(r);
							all->total=all->total-1;//reduce the length of the loans by one
							//rewrite the loan file
							if (store_loans(loan)==0){
								printf("\nThe book %i,%s has been successfully returned!\n",returnp->id,returnp->title);
								return 0;
							}
							else{
								printf("\nUpdating loan file failed! Please contact the librarian for help.\n");
								return 1;
							}
						}
						else{
							r=r->next;
							last=last->next;
						}
					}
				}
				else{
					printf("\nFailed to load loan records!\n");
					return 1;
				}
			}
			else{//not find the book to be returned in the original book list
				returnp=returnp->next;
			}
		}
		return 1;
}

//function for librarian to add a book to the book list
int add_book(Book book){
	//store the title
	printf("\nEnter the title of the book you want to add: ");
	char *add_title=(char *)malloc(sizeof(char)*200);//the maxium length of a book title maybe 200 characters
	fgets(add_title,200,stdin);
	int i=strlen(add_title);
	add_title[i-1]='\0';//get rid of the '\n' at the last of the input
	int j;
	for (j=0;j<i-1;j++){
		if (isdigit(add_title[j])){
			printf("\nThis is an invalid book title!\n");
			return 1;
		}
		else{continue;}
	}
	book.title=add_title;

	//store the author
	printf("Enter the author of the book you want to add: ");
	char *add_author=(char *)malloc(sizeof(char)*100);//the maxium length of a book author maybe 100 characters
	fgets(add_author,100,stdin);
	int x=strlen(add_author);
	add_author[x-1]='\0';//get rid of the '\n' at the last of the input
	int y;
	for (y=0;y<x-1;y++){
		if (isspace(add_author[y])){
			y+=1;
		}
		if (!isalpha(add_author[y])){
			printf("\nThis is an invalid book title!\n");
			return 1;
		}
		else{continue;}
	}
	book.authors=add_author;

	//store the year
	printf("Enter the year of the book you want to add: ");
	char *add_year=(char *)malloc(sizeof(int)*4+sizeof(char));//the maxium length of a year is 4 digit + one for the '\n'
	fgets(add_year,18,stdin);
	int m=strlen(add_year);
	if (m>5){//the lenght of a year can be maximum at 4 digits (and one '\n')
	    printf("\nThis is an invalid year!\n");
		return 1;
	}
	add_year[m-1]='\0';//get rid of the '\n' at the last of the input
	int n;
	for (n=0;n<m-1;n++){
		if (!isdigit(add_year[n])){
			printf("\nThis is an invalid year!\n");
			return 1;
		}
		else{continue;}
	}
	int addyear=atoi(add_year);
	time_t t;
    struct tm * lt;
    time (&t);//get Unix time
    lt = localtime (&t);//trun into time struct
    int thisyear=lt->tm_year+1900;
	if (addyear>thisyear){
		printf("\nThis year is %i! No futher year is possible!\n",thisyear);
		return 1;
	}
	book.year=addyear;

	//add the copies of the book
	printf("Enter the copies of the book you want to add(no more than): ");
	char *add_copies=(char *)malloc(sizeof(int)*4+sizeof(char));//the maxium length of a copy is 4 digit + one for the '\n'
	fgets(add_copies,18,stdin);
	int a=strlen(add_copies);
	if (a>5){//no negative copy numbers
		printf("\nToo much copies!\n");
		return 1;
	}
	add_copies[a-1]='\0';//get rid of the '\n' at the last of the input
	int b;
	for (b=0;b<a-1;b++){
		if (!isdigit(add_copies[b])){
			printf("\nThis is an invalid copy number!\n");
			return 1;
		}
		else{continue;}
	}
	int addcopy=atoi(add_copies);
	book.copies=addcopy;

	//book id is the last one
	book.id=lpointer->length+1;
    
	//create a node to store the value 
	Book *add,*temp;
	CreateNode(add);
	//copy new book data
	add->id=book.id;
	add->authors=book.authors;
	add->title=book.title;
	add->year=book.year;
	add->copies=book.copies;
	//test if there is a repeated book in the library
	Book *redundant;
	redundant=lpointer->list->next;
	unsigned int length=0;
	while (length<lpointer->length){
		if (strcmp(redundant->authors,add->authors)==0 && strcmp(redundant->title,add->title)==0 && redundant->year==add->year){
			printf("\nThe book is already in the library!\nAdding copies to the exsisting book in library...\n");
			redundant->copies=redundant->copies+book.copies;
			return 1;
		}
		else{
			redundant=redundant->next;
			length+=1;
		}
	}
	//add to the book list (at last)
	temp=lpointer->list;
	while (temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=add;
	add->next=NULL;
	lpointer->length+=1;
	printf("\nThe book: %s is successfuly added to the library!\n",book.title);
	//free the pointers used to read in data
	free(add_year);
	free(add_copies);
	return 0;
}

//function for librarian to remove a book from the book list(by id)
int remove_book(Book book){
	//by the id of the book
	printf("Enter the id of the book you want to remove: ");
	char *remove_id=(char *)malloc(sizeof(int)*10+sizeof(char));//the maxium length of a id maybe 10 digits + one for the '\n'
	fgets(remove_id,51,stdin);
	int a=strlen(remove_id);
	remove_id[a-1]='\0';//get rid of the '\n' at the last of the input
	int b;
	for (b=0;b<a-1;b++){
		if (!isdigit(remove_id[b])){
			printf("\nThis is an invalid book id!\n");
			return 1;
		}
		else{continue;}
	}
	unsigned int removeid=(unsigned int)atoi(remove_id);
	//check th id is in range or not
	if (removeid>lpointer->length || removeid<1){
		printf("\nID out of range! Please re-enter.\n");
		return 1;
	}
	book.id=removeid;

	//deleted the specified node in the book list
	Book *p1,*p;
	p=lpointer->list;
	while (p->next!=NULL){
		p1=p;
		p=p->next;
		if (book.id==p->id){
			p1->next=p->next;
			free(p);
			p=p1->next;
			printf("\nBook(ID): %i has been removed successfuly.\n",book.id);
			lpointer->length=lpointer->length-1;//reduce the length of the booklist by 1
			free(remove_id);//free the char * used to read in the book id
			unsigned int track;//to track whetehr all the booklist has been modified correctly
			track=p1->id;
			while (track<lpointer->length){
				p->id=p->id-1;//to move forward the book id after the deleted node by 1
				p=p->next;
				track+=1;
			}
			return 0;
		}
	}
	return 1;
}

//fucntion for user register
int user_regist(FILE *userfile){
	if (load_users(userfile)==0){//reload the userfile in case anychages have been made 
        //get user's name
        printf("Please enter your name(less than 50 words,only space and characters are allowed):");
	    char *name=(char *)malloc(sizeof(char)*50);//the maxium length of a name maybe is 50 letters
	    fgets(name,50,stdin);
	    int i=strlen(name);
	    name[i-1]='\0';//get rid of the '\n' at the last of the input
	    int j;
	    for (j=0;j<i;j++){
		    if (isspace(name[j])){
				j+=1;//ignore the space in title
			}
		    if (!isalpha(name[j])){
			    printf("\nSome thing worng with your name!\nOnly space and characters are allowed.\n");
			    return 1;
            }
            else{continue;}
	    }//name should only contain space and letters

        //get username
	    printf("Please enter your username(less than 100 characters): ");
	    char *username=(char *)malloc(sizeof(char)*100);//the maxium length of a username maybe is 100 characters
	    fgets(username,100,stdin);
	    int m=strlen(username);
	    username[m-1]='\0';//get rid of the '\n' at the last of the input
	
	    //get password
	    printf("Please enter your password(no more than 10 letters or 10 intergers): ");
	    char *password=(char *)malloc(sizeof(char)*10+sizeof(int)*10);//the maxium length of a username maybe is 100 characters
	    fgets(password,50,stdin);
	    int k=strlen(password);
	    password[k-1]='\0';//get rid of the '\n' at the last of the input

	    int newid=admin->users+1;//set the new user ID

	    //check whether there exists a same user or not
	    User *checkrepeat;
		checkrepeat=admin->UserList->next;
		while (checkrepeat!=NULL){
			if (strcmp(checkrepeat->username,username)==0){
				printf("\nThe username has been taken!\n");
				return 1;
			}
			if (strcmp(checkrepeat->password,password)==0){
				printf("\nThe password has been taken!\n");
				return 1;
			}
			checkrepeat=checkrepeat->next;
		}
		
	    //write in the new user's information to user.txt
	    userfile=fopen(Userfile,"a");
	    if (userfile==NULL){
		    printf("\nFail to open user file. Contact the librarian.\n");
		    fclose(userfile);
		    return 1;
	    }
	    else{
		    fprintf(userfile,"%i,%s,%s,%s\n",newid,name,username,password);
		    fclose(userfile);
		    free(name);
		    free(username);
		    free(password);
		    printf("\nYou have registered successfully!\n");
		    printf("\nChoose option 2 if you want to login right after.\n");
		    return 0;
	    }    
	}
	else{
		printf("\nFailed to load user file!\n");
		return 1;
	}
}

void login(FILE *userfile){
    if (load_users(userfile)==0){
        printf("Please enter username(less than 100 characters): ");
        char *username=(char *)malloc(sizeof(char)*100);//the maxium length of a username maybe 50 characters
	    fgets(username,100,stdin);
	    int i=strlen(username);
	    username[i-1]='\0';//get rid of the '\n' at the last of the input
        printf("Please enter password(no more than 10 letters or 10 intergers): ");
        char *password=(char *)malloc(sizeof(char)*10+sizeof(int)*10);//the maxium length of a password maybe 30 characters
	    fgets(password,50,stdin);
	    int j=strlen(password);
	    password[j-1]='\0';//get rid of the '\n' at the last of the input

        //check whether the user is a normal user or librarian

        User *LoginCheck;//serve as a check for user login, also aused as the identity of the user in user system
        LoginCheck=admin->UserList->next;
		int success=0;//determin whether a user has successfully logged in or not
        while (LoginCheck!=NULL){
            if (strcmp(LoginCheck->username,username)==0 && strcmp(LoginCheck->password,password)==0 && LoginCheck->id!=1){//the first is the librarian
			    success=1;
				Booklist(LoginCheck->borrowed);//creat the bokklist of loan books embedded in the particular user
	            CreateNode(LoginCheck->borrowed->list);//creat the first node in the booklist struct as the head node of the loan list
				LoginCheck->borrowed->list->id=0;//initialize the loan list by id
            	LoginCheck->borrowed->length=0;//initialize the length of the booklist
				time_t t;
                struct tm * lt;
                time (&t);//get Unix time
                lt = localtime (&t);//turn into time struct
				printf("\n(Successfully logged in as: %s at %d/%d/%d %d:%d:%d)\n",LoginCheck->username,lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
				//interface for normal user
                int choice = 5; //exit
	            do {
	                char * answer = user_input("\nPlease choose an option:\n1) Borrow book \n2) Return book \n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
	                choice = atoi(answer);
	                free(answer);
		            switch (choice) {
		                case 1:
			                borrow_book(LoginCheck,loan);
			                break;
			            case 2:
			                return_book(LoginCheck,loan);
			                break;
			            case 3:
			                search_for_books(lpointer);
			                break;
			            case 4:
			                print_all_books(lpointer);
			                break;
		                case 5:
						    time (&t);//get Unix time
                            lt = localtime (&t);//turn into time struct
				            printf("\nRequest to log out at %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			                printf("\nThank you for using the library!\n Loging you out...\n\n");
			                break;
		                default:
			                printf("\nSorry, the option you entered was invalid, please try agian.\n");
	                } 
                } while (choice != 5);
            }
		    if (strcmp(LoginCheck->username,username)==0 && strcmp(LoginCheck->password,password)==0 && LoginCheck->id==1){//librarian log in
			    success=1;
				time_t t;
                struct tm * lt;
                time (&t);//get Unix time
                lt = localtime (&t);//turn into time struct
				printf("\n(Successfully logged in as Librarian: %s at %d/%d/%d %d:%d:%d)\n",LoginCheck->username,lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
				//interface for librarian usage
                int lchoice = 5; //exit
	            do {
	                char * answer = user_input("\nPlease choose an option:\n1) Add book \n2) Remove book \n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
	                lchoice = atoi(answer);
	                free(answer);
		            switch (lchoice) {
		                case 1:
			                add_book(book);
			                break;
			            case 2:
			                remove_book(book);
			                break;
			            case 3:
			                search_for_books(lpointer);
			                break;
			            case 4:
			                print_all_books(lpointer);
			                break;
		                case 5:
                            time (&t);//get Unix time
                            lt = localtime (&t);//turn into time struct
				            printf("\nRequest to log out at %d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			                printf("\nThank you for managing the library!\nLoging you out...\n\n");
			                return;
		                default:
			                printf("\nSorry, the option you entered was invalid, please try agian.\n");
	                } 
                } while (lchoice != 5);
		    }
            else{
			    LoginCheck=LoginCheck->next;
		    }
        }
		if (success==0){
			printf("\nSorry, your username or password is invalid, please try again!\n");
			return;
		}
    }
    else{
        printf("\nFailed to laod users.\n EXITING...");
        return;
    }
}
