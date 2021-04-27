#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char getSelection();
void setSeekPosition(FILE* courseFile);
bool courseExists(COURSE *course);
void createRecord(FILE* courseFile);
void readRecord(FILE* courseFile);
void updateRecord(FILE* courseFile);
void deleteRecord(FILE* courseFile);

typedef struct {
    char name[80];
    char schedule[4];
    unsigned hours;
    unsigned size;
    unsigned padding; //Not used but required
} COURSE;