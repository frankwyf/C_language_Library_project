# Readme file for programming project coursewok 1

## This is the README file of XJCO1921 programming-project coursework 1, the systme provided user register, user (librarian) login, print all books and a backend management system(addtional)
*[Functions and inplemeantations](#General-interpretation)
*[Tests and file explaination](#Tests-and-submission-files)
*[Reflection](#Reflection-and-review)

### General-interpretation
The entrance is pleaced in a file called "main.c", in the main function the system takes in command line arguments and these three arguments are corresponding to book file, user file and loan file.

In the main interface, there are five functions. 
Option 1 corresponds to user register, in which a user will have to provide a name, a username and a password to register in the system. Their information are stored in the user file and pointers are used to get user inupt.

Option 2 corresponds to login. The system has a special user (ID as 1) called "deafult", the username is "Admin" and password is "Admin123". This is the librarian account. Login as the librarian allows you to add, remove, serach or print all the books. Following the librarian are all the registered users and login as a user allows you to borrow, return, search or print all the books. All the functions above is provided in a sub-interface when the check of username and password is passed.
When log in and system starts, the current time is displayed on the screen.

*Option 3 is an additioanl feature which is not within the requirement of coursework 1. I designed it as a enmergency solution to some unexpeted situations. The backend system ONLY allows the librarian to login and it provides the librarian (manager) with functions of showing all registered users; remove a user as he/she's information or membership is expired; display all the loan information and remove a loan record when a user lost a copy of books or something worog happend when the book is returned.

Option 4 is to display all the details of the librbay, like the book id, title, author, year of publication and copies which are currently available.

Option 5 is to quit the whole system, when all the book information is updated and stored in the book file.


### Tests-and-submission-files
The systme is tested uder windows and centOS(linux) virtual machine. The Functions can be used properly and a relevant amount of error siutuations are considered and dealt with. However, I found that due to the different ways of storing a .txt file, under linux OS, all the three files(book file user file, loan file) requires a "dos2unix" command to be restored in unix coding so that the fucntions can be presented properly. In my subbmited files, there is a folder called "linux_file" which contains three unix coding .txt files for showing the system under linux OS.
During test period, I found that the up limit of a "year" value should be no more than the current year. In order to do so, I used the C libraray "time.h" to get the current system time and limit user input by this.
Besieds, to make sure that the right data type is read in to the system, every "loan" functions have a check for the type if data which are fed to the system. If they are of the wrong type, the system will return with a meaningful error message.

### Reflection-and-review
In this project, the major problem I encountered was how to use dynamic memory allocation for all aspects that require internal memory spaces. The other part, like how to read/write form a text file, manage user input and look up through linked lists all went relatively well. For testing, I encountered some problem when moving my system under a unix operating system but the problem was solved by re-saving text files as unix mode. A copy of those files is included in the submission, too.

The most challenging part is dynamic memory allocation and flexibility between operating systems. As a beginner, I am still not very familliar with dynamic memory allocation and the minor differences between different operating systems. I will practice more and learn from all my previous works to improve on these two points.

### Git with a Git Hub repository was used for verison control in this work, the URL of the remote repository and screenshots of gits commision is presented below 
URL of git respository:https://github.com/frankwyf/programming-project.git

Git commision history Screenshot:
Screenshot:https://raw.githubusercontent.com/frankwyf/programming-project/master/git%20screenshots/Screenshot.png 
Screenshot0:https://raw.githubusercontent.com/frankwyf/programming-project/master/git%20screenshots/Screenshot0.png 
Screenshot 1:https://raw.githubusercontent.com/frankwyf/programming-project/8285e99569e6907e45c3c9c5a201a2be42ff19fd/Screenshot1.png
Screenshot 2:https://raw.githubusercontent.com/frankwyf/programming-project/8285e99569e6907e45c3c9c5a201a2be42ff19fd/Screenshot2.png 
Screenshot 3:https://raw.githubusercontent.com/frankwyf/programming-project/8285e99569e6907e45c3c9c5a201a2be42ff19fd/Screenshot3.png 
Screenshot 4:https://raw.githubusercontent.com/frankwyf/programming-project/8285e99569e6907e45c3c9c5a201a2be42ff19fd/Screenshot4.png 
