#include"interface.h"
#include"user_management.h"
#include"book_management.h"
#include"management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define CreateNode(p) p=(Book *)malloc(sizeof(Book));
#define Booklist(p) p=(BookList *)malloc(sizeof(BookList));
#define DeleteNode(p) free((void *)p);



char *user_input(const char *input) {
	printf("%s",input);//print the interface choices 1,2,3...

	size_t capacity = 64;
	size_t len = 0;
	char *answer = (char *)malloc(capacity);
	if (answer == NULL) {
		return NULL;
	}

	while (fgets(answer + len, (int)(capacity - len), stdin) != NULL) {
		len = strlen(answer);
		if (len > 0 && answer[len - 1] == '\n') {
			answer[len - 1] = '\0';
			break;
		}

		if (capacity - len <= 1) {
			size_t new_capacity = capacity * 2;
			char *tmp = (char *)realloc(answer, new_capacity);
			if (tmp == NULL) {
				free(answer);
				return NULL;
			}
			answer = tmp;
			capacity = new_capacity;
		}
	}

	if (len == 0 && feof(stdin)) {
		free(answer);
		answer = (char *)malloc(2);
		if (answer == NULL) {
			return NULL;
		}
		answer[0] = '0';
		answer[1] = '\0';
		return answer;
	}

	for (size_t i = 0; answer[i] != '\0'; i++) {
		if (!isdigit((unsigned char)answer[i])) {
			answer[0] = '0';
			answer[1] = '\0';
			return answer;
		}
	}

	return answer;
}

void run_system(){
	time_t t;
    struct tm * lt;
	if (load_books(file)==0){
	int choice = 5; //exit
	    do {
	        char * answer = user_input("\nPlease choose an option:\n1) Register an account\n2) Login for books \n3) Manager system\n4) Display all books\n5) Quit\nOption: ");
	        if (answer == NULL) {
	        	printf("\nInput error. Exiting...\n");
	        	exit(1);
	        }
	        choice = atoi(answer);
	        free(answer);
		    switch (choice) {
		        case 1:
			        user_regist(userfile);
			        break;
			    case 2:
			        login(userfile);
			        break;
			    case 3:
			        backend_management(userfile);
			        break;
			    case 4:
			        print_all_books(lpointer);
			        break;
		        case 5:
				    if (store_books(file)==0){
						time (&t);//get Unix time
                        lt = localtime (&t);//turn into time struct
						printf("\nThank you for using the library!\nGoodbye! %d/%d/%d %d:%d:%d\n\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			            break;
					}
					else{
						break;
					}
		        default:
			        printf("\nSorry, the option you entered was invalid, please try agian.\n");
	        } 
        } while (choice != 5);
	}
	else{
		printf("Failed to load book data!\n");
		exit(-1);
	}
}
