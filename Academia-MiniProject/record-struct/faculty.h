#ifndef FACULTY_RECORD
#define FACULTY_RECORD

#define MAX_ENROLLMENT 10

struct Faculty 
{
    int id;     // Faculty IDs
    char name[35];
    char email[30];
    char address[50];
     char destignation[30];
    char password[30];
};

#endif