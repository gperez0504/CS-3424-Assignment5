#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char getSelection();
int setSeekPosition(FILE* courseFile);
bool courseExists(int hours);
void createRecord(FILE* courseFile);
void readRecord(FILE* courseFile);
void updateRecord(FILE* courseFile);
void deleteRecord(FILE* courseFile);

//COURSE struct as provided by assignemnt
// ! Do not modify struct in any way
typedef struct {
    char name[80];
    char schedule[4];
    unsigned hours;
    unsigned size;
    unsigned padding; //Not used but required
} COURSE;