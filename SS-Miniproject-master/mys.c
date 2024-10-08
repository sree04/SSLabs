#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include <semaphore.h>


#include"Authenticator.h"
#include"Database.h"
#include"Search.h"
#include"Add.h"

#define buffsz 100000
#define MAX_CLIENTS 3

void *handle_client(void *arg) {
    int client_sock = *(int*)arg;
    free(arg);

    // Handle client connection here
    // This is where you'd put your existing client handling code

    char buffer[buffsz];
    // ... (your existing client handling code goes here)
 //communication between a client and server starts
    while(1)
    {
        //write main menu
        char* mainMenu="Welcome to Academia\n"
                        "Enter your Choice\n"
                        "1. Admin\n"
                        "2. Student\n"
                        "3. Faculty\n";
        
        write(client_sock,mainMenu,strlen(mainMenu));
        //write main menu



        //read choice
        int choice;
        read(client_sock,&choice,sizeof(int));
        //read choice
        if(choice==1){
            //authentication input

            //write input email msg
            char* EmailMsg="Enter Email:\n";
            write(client_sock,EmailMsg,strlen(EmailMsg));
            //write input email msg

            //read input email
            char inputEmail[100];
            read(client_sock,&inputEmail,sizeof(inputEmail));
            //read input email

            //write input Password msg
            char* PasswordMsg="Enter Password:\n";
            write(client_sock,PasswordMsg,strlen(PasswordMsg));
            //write input Password msg

            //read input password
            char inputPassword[100];
            read(client_sock,&inputPassword,sizeof(inputPassword));
            //read input password
            int isValid=AuthenticateAdmin(inputEmail,inputPassword);

            //write isvalid to client
            write(client_sock,&isValid,sizeof(isValid));
            //write isvalid to client
            if(isValid==1){
                //Authentication Successful
                //write adminMenu msg
                char* adminMenu="Welcome to Admin Menu\n"
                                "1.Add Student\n"
                                "2.Add Faculty\n"
                                "3.Activate Student\n"
                                "4.Deactivate Student\n"
                                "5.Update Student Details\n"
                                "6.Update Faculty Details\n"
                                "7.Exit\n";
                write(client_sock,adminMenu,strlen(adminMenu));
                //write adminMenu msg
                
                //read adminMenu choice
                int adminChoice;
                read(client_sock,&adminChoice,sizeof(int));
                //read adminMenu choice
                if(adminChoice==1){
                    struct Student addStudent;
                    
                    //write student name
                    char* msg="Enter student name\n";
                    write(client_sock,msg,strlen(msg));
                    //write student name

                    //read student name
                    read(client_sock,&addStudent.name,sizeof(addStudent.name));
                    //read student name
                    
                    //write student rollno
                    msg="Enter student rollno\n";
                    write(client_sock,msg,strlen(msg));
                    //write student rollno

                    //read student rollno
                    read(client_sock,&addStudent.rollno,sizeof(addStudent.rollno));
                    //read student rollno

                    //write student emailID
                    msg="Enter student emailID\n";
                    write(client_sock,msg,strlen(msg));
                    //write student emailID

                    //read student emailID
                    read(client_sock,&addStudent.emailId,sizeof(addStudent.emailId));
                    //read student emailID

                    //write student password
                    msg="Enter student password\n";
                    write(client_sock,msg,strlen(msg));
                    //write student password

                    //read student password
                    read(client_sock,&addStudent.password,sizeof(addStudent.password));
                    //read student password
                    int checker=searchStudent(addStudent.rollno);

                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker
                    addStudent.status=1;

                    
                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //duplicate entry
                        break;

                    }else if(checker==1){
                        //unique entry
                        int addStudentEntry=AddStudent(addStudent);
                        //write addStudentEntry
                        write(client_sock,&addStudentEntry,sizeof(int));
                        //write addStudentEntry
                        if(addStudentEntry==-1){
                            break;
                        }else{
                            //write student added successfully!!!
                            msg="Student added successfully!!!\n";
                            write(client_sock,msg,strlen(msg));
                            break;
                            //write student added successfully!!!
                        }

                    }else{
                        break;
                    }

                }
                else if(adminChoice==2){
                    struct Faculty addFaculty;
                    
                    //write Faculty name
                    char* msg="Enter faculty name\n";
                    write(client_sock,msg,strlen(msg));
                    //write Faculty name

                    //read Faculty name
                    read(client_sock,&addFaculty.name,sizeof(addFaculty.name));
                    //read Faculty name
                    
                    //write Faculty rollno
                    msg="Enter faculty UID\n";
                    write(client_sock,msg,strlen(msg));
                    //write Faculty rollno

                    //read Faculty uid
                    read(client_sock,&addFaculty.facultyUID,sizeof(addFaculty.facultyUID));
                    //read Faculty uid


                    //write Faculty password
                    msg="Enter Faculty password\n";
                    write(client_sock,msg,strlen(msg));
                    //write Faculty password

                    //read Faculty password
                    read(client_sock,&addFaculty.password,sizeof(addFaculty.password));
                    //read Faculty password
                    int checker=searchFaculty(addFaculty.facultyUID);

                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    
                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //duplicate entry
                        break;

                    }else if(checker==1){
                        //unique entry
                        int addFacultyEntry=AddFaculty(addFaculty);
                        //write addFacultyEntry
                        write(client_sock,&addFacultyEntry,sizeof(int));
                        //write addFacultyEntry
                        if(addFacultyEntry==-1){
                            break;
                        }else{
                            //write Faculty added successfully!!!
                            msg="Faculty added successfully!!!\n";
                            write(client_sock,msg,strlen(msg));
                            break;
                            //write Faculty added successfully!!!
                        }

                    }else{
                        break;
                    }

                }
                else if(adminChoice==3){
                    struct Student activateThisStudent;
                    //write Student UID
                    char* msg="Enter Student rollno\n";
                    write(client_sock,msg,strlen(msg));
                    //write Student UID

                    //read Student UID
                    read(client_sock,&activateThisStudent.rollno,sizeof(activateThisStudent.rollno));
                    //read Student UID

                    int checker=searchStudent(activateThisStudent.rollno);
                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //duplicate entry
                        activateThisStudent.status=1;
                        //update status in database
                        updateStatusStudent(activateThisStudent);
                        //update status in database
                        
                        msg="Student status activated\n";

                        //write student msg
                        write(client_sock,msg,strlen(msg));
                        //write student msg

                    }else if(checker==1){
                        //unique entry
                        msg="No such student exist\n";

                        //write student not found
                        write(client_sock,msg,strlen(msg));
                        //write student not found
                        
                        break;
                    }else{
                        break;
                    }
                }
                else if(adminChoice==4){
                    struct Student deactivateThisStudent;
                    //write Student UID
                    char* msg="Enter Student rollno\n";
                    write(client_sock,msg,strlen(msg));
                    //write Student UID

                    //read Student UID
                    read(client_sock,&deactivateThisStudent.rollno,sizeof(deactivateThisStudent.rollno));
                    //read Student UID

                    int checker=searchStudent(deactivateThisStudent.rollno);
                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //duplicate entry
                        deactivateThisStudent.status=0;
                        //update status in database
                        updateStatusStudent(deactivateThisStudent);
                        //update status in database
                        
                        msg="Student status deactivated\n";

                        //write student msg
                        write(client_sock,msg,strlen(msg));
                        //write student msg

                    }else if(checker==1){
                        //unique entry
                        msg="No such student exist\n";

                        //write student not found
                        write(client_sock,msg,strlen(msg));
                        //write student not found
                        
                        break;
                    }else{
                        break;
                    }
                }
                else if(adminChoice==5){
                    //update student

                    //write input rollnumber
                    char* msg="Input Rollnumber of student to update\n";
                    write(client_sock,msg,strlen(msg));
                    //write input rollnumber
                    char inputrollno[100];
                    //read Student UID
                    read(client_sock,inputrollno,sizeof(inputrollno));
                    //read Student UID

                    int checker=searchStudent(inputrollno);
                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //duplicate entry
                        int updateNamePass;

                        //write nam/pass
                        msg="Do you want to update Name or Password\n"
                            "1. Name\n"
                            "2. Password\n";
                        write(client_sock,msg,strlen(msg));
                        //write nam/pass

                        //read namepass value
                        int namePass;
                        read(client_sock,&namePass,sizeof(int));
                        //read namepass value

                        if(namePass==1){
                            //update Name
                            struct Student updateName;
                            int fd=open("Student.txt",O_RDWR,0666);
                            while(read(fd,&updateName,sizeof(updateName))>0){
                                if(strcmp(updateName.rollno,inputrollno)==0){
                                    //write msg to enter new name
                                    msg="Enter new name\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg to enter new name

                                    //read new name
                                    read(client_sock,updateName.name,sizeof(updateName.name));
                                    //read new name

                                    lseek(fd,-1*sizeof(updateName),SEEK_CUR);
                                    write(fd,&updateName,sizeof(updateName));

                                    //write msg updation successful
                                    msg="Name has been updated\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg updation successful
                                    break;
                                }
                            }
                            break;
                            

                        }else if(namePass==2){
                            //update password
                            struct Student updatePassword;
                            int fd=open("Student.txt",O_RDONLY,0666);
                            while(read(fd,&updatePassword,sizeof(updatePassword))>0){
                                if(strcmp(updatePassword.rollno,inputrollno)==0){
                                    //write msg to enter new password
                                    msg="Enter new password\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg to enter new password

                                    //read new password
                                    read(client_sock,updatePassword.password,sizeof(updatePassword.password));
                                    //read new password
                                    lseek(fd,-1*sizeof(updatePassword),SEEK_CUR);
                                    write(fd,&updatePassword,sizeof(updatePassword));

                                    //write msg updation successful
                                    msg="Name has been updated\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg updation successful
                                    break;
                                }
                            }
                            break;
                        }else{
                            break;
                        }

                    }else if(checker==1){
                        //unique entry
                        msg="No such student exist\n";

                        //write student not found
                        write(client_sock,msg,strlen(msg));
                        //write student not found
                        
                        break;
                    }else{
                        break;
                    }

                }
                else if(adminChoice==6){
                    //update faculty
                    //write input rollnumber
                    char* msg="Input facUID of faculty to update\n";
                    write(client_sock,msg,strlen(msg));
                    //write input rollnumber
                    char inputUID[100];
                    //read Student UID
                    read(client_sock,inputUID,sizeof(inputUID));
                    //read Student UID

                    int checker=searchFaculty(inputUID);
                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //duplicate entry
                        int updateNamePass;

                        //write nam/pass
                        msg="Do you want to update Name or Password\n"
                            "1. Name\n"
                            "2. Password\n";
                        write(client_sock,msg,strlen(msg));
                        //write nam/pass

                        //read namepass value
                        int namePass;
                        read(client_sock,&namePass,sizeof(int));
                        //read namepass value

                        if(namePass==1){
                            //update Name
                            struct Faculty updateName;
                            int fd=open("Faculty.txt",O_RDWR,0666);
                            while(read(fd,&updateName,sizeof(updateName))>0){
                                if(strcmp(updateName.facultyUID,inputUID)==0){
                                    //write msg to enter new name
                                    msg="Enter new name\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg to enter new name

                                    //read new name
                                    read(client_sock,updateName.name,sizeof(updateName.name));
                                    //read new name

                                    lseek(fd,-1*sizeof(updateName),SEEK_CUR);
                                    write(fd,&updateName,sizeof(updateName));

                                    //write msg updation successful
                                    msg="Name has been updated\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg updation successful
                                    break;
                                }
                            }
                            break;
                            

                        }else if(namePass==2){
                            //update password
                            struct Student updatePassword;
                            int fd=open("Student.txt",O_RDONLY,0666);
                            while(read(fd,&updatePassword,sizeof(updatePassword))>0){
                                if(strcmp(updatePassword.rollno,inputUID)==0){
                                    //write msg to enter new password
                                    msg="Enter new password\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg to enter new password

                                    //read new password
                                    read(client_sock,updatePassword.password,sizeof(updatePassword.password));
                                    //read new password
                                    lseek(fd,-1*sizeof(updatePassword),SEEK_CUR);
                                    write(fd,&updatePassword,sizeof(updatePassword));

                                    //write msg updation successful
                                    msg="Name has been updated\n";
                                    write(client_sock,msg,strlen(msg));
                                    //write msg updation successful
                                    break;
                                }
                            }
                            break;
                        }else{
                            break;
                        }

                    }else if(checker==1){
                        //unique entry
                        msg="No such Faculty exist\n";

                        //write student not found
                        write(client_sock,msg,strlen(msg));
                        //write student not found
                        
                        break;
                    }else{
                        break;
                    }

                }
                else if(adminChoice==7){break;}
                else{break;}
            }

            //authentication input
        }else if(choice==2){
            //student login
            //write input UID msg
            char* StudentRollnoMsg="Enter Student rollno:\n";
            write(client_sock,StudentRollnoMsg,strlen(StudentRollnoMsg));
            //write input email msg

            //read input rollno
            char inputStudentUID[100];
            read(client_sock,&inputStudentUID,sizeof(inputStudentUID));
            //read input email

            //write input Password msg
            char* PasswordMsg="Enter Password:\n";
            write(client_sock,PasswordMsg,strlen(PasswordMsg));
            //write input Password msg

            //read input password
            char inputPassword[100];
            read(client_sock,&inputPassword,sizeof(inputPassword));
            //read input password

            int isValid=AuthenticateStudent(inputStudentUID,inputPassword);
            //write isvalid to client
            write(client_sock,&isValid,sizeof(isValid));
            //write isvalid to client

            if(isValid==1){
                //write student Menu
                char* studentMenu="Welcome to Student Menu\n"
                                    "1.Enroll to new course\n"
                                    "2.Unenroll from offered course\n"
                                    "3.View enrollments in course\n"
                                    "4.Password Change\n"
                                    "5.Exit\n";
                write(client_sock,studentMenu,strlen(studentMenu));
                //write student Menu


                //read student choice
                int studentChoice;
                read(client_sock,&studentChoice,sizeof(int));
                //read student choice

                if(studentChoice==1){

                    char enrollInCourse[100];
                    //write course code
                    char* msg="Enter course code to enroll\n";
                    write(client_sock,msg,strlen(msg));
                    //write course code


                    //read course code
                    read(client_sock,&enrollInCourse,sizeof(enrollInCourse));
                    //read course code


                    int checker=searchActiveCourse(enrollInCourse);
                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker


                    if(checker==-1){
                        //unable to access course database
                        break;
                    }else if(checker==0){   
                        //course exists
                        int enrollStatus=enrollInActiveCourse(enrollInCourse,inputStudentUID);
                        //write enrollStatus
                        write(client_sock,&enrollStatus,sizeof(int));
                        //write enrollStatus
                        if(enrollStatus==-1){
                            break;
                        }else if(enrollStatus==1){
                            //student is enrolled in course successfully

                            break;
                        }else if(enrollStatus==0){
                            //one of condition fails
                            break;
                        }else{
                            break;
                        }
                        break;
                    }else if(checker==1){
                        //course does not exist
                        break;
                    }else{
                        break;
                    }
                }else if(studentChoice==2){
                    //unenroll student
                    char unEnrollInCourse[100];

                    //write course code
                    char* msg="Enter course code\n";
                    write(client_sock,msg,strlen(msg));
                    //write course code

                    //read course code
                    read(client_sock,&unEnrollInCourse,sizeof(unEnrollInCourse));
                    //read course code


                    int checker=searchActiveCourse(unEnrollInCourse);
                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        //unable to access database
                        break;
                    }else if(checker==0){
                        //course exists
                        int unenrollStatus=unenrollInActiveCourse(unEnrollInCourse,inputStudentUID);
                        //write unenrollStatus
                        write(client_sock,&unenrollStatus,sizeof(int));
                        //write unenrollStatus
                        if(unenrollStatus==-1){
                            //error
                            break;
                        }else if(unenrollStatus==1){
                            //success
                            break;
                        }else if(unenrollStatus==0){
                            //failed
                            break;
                        }else{
                            break;
                        }
                        break;
                    }else if(checker==1){
                        //course does not exist
                        break;
                    }else{
                        break;
                    }
                }else if(studentChoice==3){
                    //view enrolled courses
                    //stores data from students in courses
                    char viewCourseDetails[buffsz];

                    viewEnrolledCourses(inputStudentUID,viewCourseDetails);
                    
                    //write view course details
                    write(client_sock,&viewCourseDetails,buffsz);
                    //write view course details

                    break;
                }else if(studentChoice==4){
                    struct Student updateThisPassword;
                    int fd=open("Student.txt",O_RDWR,0666);
                    while(read(fd,&updateThisPassword,sizeof(updateThisPassword))>0){
                        if(strcmp(updateThisPassword.rollno,inputStudentUID)==0){
                            //write msg to enter new password
                            char* msg="Enter new password\n";
                            write(client_sock,msg,strlen(msg));
                            //write msg to enter new password


                            //read new password
                            read(client_sock,updateThisPassword.password,sizeof(updateThisPassword.name));
                            //read new password
                            lseek(fd,-1*sizeof(updateThisPassword),SEEK_CUR);
                            write(fd,&updateThisPassword,sizeof(updateThisPassword));


                            //write msg updation successful
                            msg="Password has been updated\n";
                            write(client_sock,msg,strlen(msg));
                            //write msg updation successful
                            break;
                        }
                        break;
                    }
                }else if(studentChoice==5){
                    break;
                }else{
                    break;
                }
            }
        }else if(choice==3){
            //faculty login
            //write input email msg
            char* facUIDMsg="Enter faculty UID:\n";
            write(client_sock,facUIDMsg,strlen(facUIDMsg));
            //write input email msg

            //read input email
            char inputFacUID[100];
            read(client_sock,&inputFacUID,sizeof(inputFacUID));
            //read input email

            //write input Password msg
            char* PasswordMsg="Enter Password:\n";
            write(client_sock,PasswordMsg,strlen(PasswordMsg));
            //write input Password msg

            //read input password
            char inputPassword[100];
            read(client_sock,&inputPassword,sizeof(inputPassword));
            //read input password



            int isValid=AuthenticateFaculty(inputFacUID,inputPassword);

            //write isvalid to client
            write(client_sock,&isValid,sizeof(isValid));
            //write isvalid to client
            if(isValid==1){
                //Authentication Successful

                //write Faculty Menu
                char* facultyMenu="Welcome to Faculty Menu\n"
                                    "1.Add new course\n"
                                    "2.Remove offered course\n"
                                    "3.View enrollments in course\n"
                                    "4.Password Change\n"
                                    "5.Exit\n";
                write(client_sock,facultyMenu,strlen(facultyMenu));
                //write Faculty Menu

                //read Faculty choice
                int facultyChoice;
                read(client_sock,&facultyChoice,sizeof(int));
                //read Faculty choice

                if(facultyChoice==1){
                    struct Course addCourse;

                    //write course code
                    char* msg="Enter course code\n";
                    write(client_sock,msg,strlen(msg));
                    //write course code

                    //read course code
                    read(client_sock,&addCourse.course_code,sizeof(addCourse.course_code));
                    //read course code


                    //write course name
                    msg="Enter course name\n";
                    write(client_sock,msg,strlen(msg));
                    //write course codnamee

                    //read course name
                    read(client_sock,&addCourse.course_name,sizeof(addCourse.course_name));
                    //read course name

                    //add facUID
                    strcpy(addCourse.facultyUID,inputFacUID);
                    //add facUID

                    //write course credits
                    msg="Enter course credits\n";
                    write(client_sock,msg,strlen(msg));
                    //write course credits

                    //read course credits
                    read(client_sock,&addCourse.credits,sizeof(addCourse.credits));
                    //read course credits

                    //current students enrolled
                    addCourse.currentStudentsEnrolled=0;
                    //current students enrolled


                    //write course maxStudentsAllowed
                    msg="Enter maximum Students allowed\n";
                    write(client_sock,msg,strlen(msg));
                    //write course maxStudentsAllowed

                    //read course maxStudentsAllowed
                    read(client_sock,&addCourse.maxStudentsAllowed,sizeof(addCourse.maxStudentsAllowed));
                    //read course maxStudentsAllowed

                    //is course active
                    addCourse.status=1;
                    //is course active
                    int checker=searchActiveCourse(addCourse.course_code);


                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        break;
                    }
                    else if(checker==0){
                        //duplicate entry
                        break;
                    }
                    else if(checker==1){
                        //course not present

                        //write course entry
                        int addCourseEntry=AddCourse(addCourse);
                        write(client_sock,&addCourseEntry,sizeof(addCourseEntry));
                        //write course entry

                        if(addCourseEntry==-1){
                            break;
                        }else{
                            //write course added successfully!!!
                            msg="Course added successfully!!!\n";
                            write(client_sock,msg,strlen(msg));
                            break;
                            //write course added successfully!!!
                        }
                    }
                    else{break;}


                }
                else if(facultyChoice==2){
                    //remove course
                    //ask for course_code
                    char removeThisCourse[100];

                    //write course code
                    char* msg="Enter course code\n";
                    write(client_sock,msg,strlen(msg));
                    //write course code

                    //read course code
                    read(client_sock,&removeThisCourse,sizeof(removeThisCourse));
                    //read course code

                    int checker=searchActiveCourse(removeThisCourse);

                    //write checker
                    write(client_sock,&checker,sizeof(int));
                    //write checker

                    if(checker==-1){
                        //unable to access
                        break;
                    }else if(checker==0){
                        removeCourse(removeThisCourse);

                        msg="Course has been removed\n";

                        //write course remove msg
                        write(client_sock,msg,strlen(msg));
                        //write course remove msg
                        break;
                    }else if(checker==1){
                        break;
                    }else{
                        break;
                    }

                }
                else if(facultyChoice==3){
                    //view enrollments

                    //sendmsg for input 
                    char* msg="Enter course code";
                    write(client_sock,msg,strlen(msg));
                    //sendmsg for input 

                    //read input coursecode
                    char inputCourseCode[100];
                    read(client_sock,&inputCourseCode,sizeof(inputCourseCode));
                    //read input coursecode

                    int checker=searchActiveCourse(inputCourseCode);
                    
                    //send checker to client
                    write(client_sock,&checker,sizeof(int));
                    //send checker to client

                    if(checker==-1){
                        //unable to access
                        break;
                    }else if(checker==0){
                        //display 
                        //send message
                        msg="Number of current students are:\n";
                        write(client_sock,&msg,sizeof(msg));
                        //send message

                        //write value
                        int activeStudents=getStudentCount(inputCourseCode);
                        write(client_sock,&activeStudents,sizeof(activeStudents));
                        //write value
                        break;
                    }else if(checker==1){
                        //course does not exist
                        break;
                    }else{
                        break;
                    }

                }
                else if(facultyChoice==4){
                    //password change
                    struct Faculty updateThisPassword;
                    int fd=open("Faculty.txt",O_RDWR,0666);
                    while(read(fd,&updateThisPassword,sizeof(updateThisPassword))>0){
                        if(strcmp(updateThisPassword.facultyUID,inputFacUID)==0){
                            //write msg to enter new password
                            char* msg="Enter new password\n";
                            write(client_sock,msg,strlen(msg));
                            //write msg to enter new password


                            //read new password
                            read(client_sock,updateThisPassword.password,sizeof(updateThisPassword.name));
                            //read new password
                            lseek(fd,-1*sizeof(updateThisPassword),SEEK_CUR);
                            write(fd,&updateThisPassword,sizeof(updateThisPassword));


                            //write msg updation successful
                            msg="Password has been updated\n";
                            write(client_sock,msg,strlen(msg));
                            //write msg updation successful
                            break;
                        }
                        break;
                    }
                }
                else if(facultyChoice==5){
                    break;
                }else{
                    break;
                }
            }
        }else{
            printf("wrong choice\n");
            break;
        }        
    }
    close(client_sock);
    sem_wait(&client_count_sem);
    client_count--;
    sem_post(&client_count_sem);

    return NULL;
}

int main(int argc, char* argv[]){
    if(argc<2){
        printf("less arguments\n");
        return -1;
    }
    int sockfd,client_sock,portno,n;
    char buffer[buffsz];
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t clilen;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("Creating socket failed\n");
        return -1;
    }
    bzero((char*)&serv_addr,sizeof(serv_addr));
    portno=atoi(argv[1]);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(portno);
    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        printf("Unable to bind\n");
        return -1;
    }
    listen(sockfd,5);
    clilen=sizeof(cli_addr);

     if (sem_init(&client_count_sem, 0, 1) != 0) {
        perror("Semaphore initialization failed");
        return -1;
    }

     while(1) {
        client_sock = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
        if(client_sock < 0) {
            perror("Error on accept");
            continue;
        }

        sem_wait(&client_count_sem);
        if(client_count >= MAX_CLIENTS) {
            sem_post(&client_count_sem);
            char *msg = "Server is full. Please try again later.\n";
            write(client_sock, msg, strlen(msg));
            close(client_sock);
            continue;
        }
        client_count++;
        sem_post(&client_count_sem);

//thread management

        pthread_t thread_id;
        int *client_sock = malloc(sizeof(int));
        *client_sock = client_sock;

        if(pthread_create(&thread_id, NULL, handle_client, (void*)client_sock) < 0) {
            perror("Could not create thread");
            free(client_sock);
            close(client_sock);
            sem_wait(&client_count_sem);
            client_count--;
            sem_post(&client_count_sem);
        } else {
            pthread_detach(thread_id);
        }

  
    }

//cleanup(if server exits the loop)
   
close(sockfd);
sem_destroy(&client_count_sem);
    return 0;
}

