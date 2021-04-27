#include "assignment5.h"
char inputBuffer[80];

int main(int argc, char *argv[]){
    //Print byline
    puts("Assignment 5 created by Cole Holub (duu712)");
    
    //Open courses.dat file and create it if it does not exist
    FILE* courseFile = fopen("courses.dat", "rb+");
    if(courseFile == NULL){
        courseFile = fopen("courses.dat", "wb+");
    }
    while(!feof(stdin)){
        char selection = getSelection();
        if(feof(stdin)){
            puts("\nCTRL-D detected. Goodbye.");
            fclose(courseFile);
            return 0;
        }
        switch(selection){
        
            case 'c' :
            createRecord(courseFile);
            break;

            case 'r' :
            readRecord(courseFile);
            break;

            case 'u' :
            updateRecord(courseFile);
            break;

            case 'd' :
            deleteRecord(courseFile);
            break;

            default :
            puts("Invalid selection");
        }
    }
}

char getSelection(){
    //Display menu
    puts("\nEnter one of the following actions or type CTRL-D to exit.");
    puts("C - create a new course record");
    puts("R - read an existing course record");
    puts("U - update an existing course record");
    puts("D - delete an existing course record");
    //Prompt user for input
    printf(":");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    return tolower(inputBuffer[0]);
}

void setSeekPosition(FILE* courseFile){
    printf("Enter a course number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    fseek(courseFile, (sizeof(COURSE) * (strtol(inputBuffer, NULL, 0) - 1)), SEEK_SET);
    return;
}

bool courseExists(){
    
}

void createRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index
    COURSE *course=malloc(sizeof(COURSE));
    memset(course, 0, sizeof(COURSE));
    setSeekPosition(courseFile);

    //Prompt user for course data and store it in the struct
    printf("Enter a course name: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    strcpy(course->name, inputBuffer);
    printf("Enter course schedule (MWF or TR): ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    strcpy(course->schedule, inputBuffer);
    printf("Enter course credit hours: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    course->hours = strtol(inputBuffer, NULL, 0);
    printf("Enter student enrollment: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    course->size = strtol(inputBuffer, NULL, 0);

    //Now write the course to the file
    fwrite(course, sizeof(COURSE), 1, courseFile);

    //Be free little memory!
    free(course);
}

void readRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index
    COURSE *course=malloc(sizeof(COURSE));
    setSeekPosition(courseFile);

    //Read memory location and rebuild the course struct
    fread(course, sizeof(COURSE), 1, courseFile);
    
    //TODO: Fix formatting
    //Print the course struct to the terminal
    printf("%s\n", course->name);
    printf("%s\n", course->schedule);
    printf("%d\n", course->hours);
    printf("%d\n", course->size);

    //Be freee little memory!!
    free(course);
}

void updateRecord(FILE* courseFile){
    COURSE *course=malloc(sizeof(COURSE));
    setSeekPosition(courseFile);

    //Be freeee little memory!!!
    free(course);
}

void deleteRecord(FILE* courseFile){
    //Just set hours feild to zero
    COURSE *course=malloc(sizeof(COURSE));
    setSeekPosition(courseFile);

    //Be freeeee little memory!!!!
    free(course);
}