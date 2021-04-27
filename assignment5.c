// TODO: Implement checking if course exists as it's own function. Almost every function has a copy/pasted block of code

#include "assignment5.h"
char inputBuffer[80];

int main(int argc, char *argv[]){
    //Print byline.
    puts("Assignment 5 created by Cole Holub (duu712)");
    
    //Open courses.dat file and create it if it does not exist.
    FILE* courseFile = fopen("courses.dat", "rb+");
    if(courseFile == NULL){
        courseFile = fopen("courses.dat", "wb+");
    }

    //Keep prompting the user for input until CTRL-D.
    //Detects CTRL-D by checking if EOF is in the stdin buffer.
    //Might be a better way of doing this
    while(!feof(stdin)){
        char selection = getSelection();
        //If CTRL-D is detected, fall into this statment.
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

/**
 * Function displays main menu and prompt the user for a selection.
 * Then takes the selection and sets it to lower case to be used in the switch statment.
 * @return A lowercase A-Z character.
 */
char getSelection(){
    //Display menu.
    puts("\nEnter one of the following actions or type CTRL-D to exit.");
    puts("C - create a new course record");
    puts("R - read an existing course record");
    puts("U - update an existing course record");
    puts("D - delete an existing course record");
    //Prompt user for input.
    printf(":");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    return tolower(inputBuffer[0]);
}

/**
 * Function prompts the user for a course number.
 * Then takes that course number and uses it to set the cursor poistion to (courseNumber * sizeof(COURSE))
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 * @return An integer the represents the course number.
 */
int setSeekPosition(FILE* courseFile){
    printf("Enter a course number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    int courseNum = strtol(inputBuffer, NULL, 0);
    fseek(courseFile, (sizeof(COURSE) * ( courseNum- 1)), SEEK_SET);
    return courseNum;
}

/**
 * ! Do not use, incomplete
 * TODO: Fill in the function
 * Function checks the hours section of a course struct is zero and returns true if it is non-zero.
 * @param course A pointer to a course struct.
 * @return A boolean that indicates whether or not the course exists.
 */
bool courseExists(int hours){
    return true; // ! Just here to test
}

/**
 * Function prompts the user for input and fills the course struct with it.
 * Once all input is recived it writes the struct to the courses.dat file.
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void createRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index.
    COURSE *course=malloc(sizeof(COURSE));
    setSeekPosition(courseFile);
    //Read memory location and rebuild the course struct.
    fread(course, sizeof(COURSE), 1, courseFile);
    if(course->hours != 0){
        puts("\nERROR: course already exists");
        free(course);
        return;
    }
    memset(course, 0, sizeof(COURSE));

    //Prompt user for course data and store it in the struct.
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

    //Now write the course to the file.
    fwrite(course, sizeof(COURSE), 1, courseFile);

    //Be free little memory!
    free(course);
}

/**
 * Function extracts the course struct from the file and outputs the data to the terminal.
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void readRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index.
    COURSE *course=malloc(sizeof(COURSE));
    int courseNum = setSeekPosition(courseFile);

    //Read memory location and rebuild the course struct.
    fread(course, sizeof(COURSE), 1, courseFile);
    
    //Check if course exists and return if it does not.
    if(course->hours == 0){
        puts("\nERROR: course not found");
        free(course);
        return;
    }
    
    //Print the course struct to the terminal.
    printf("\nCourse number: %d\n", courseNum);
    printf("Course name: %s", course->name);
    printf("Scheduled days: %s", course->schedule);
    printf("Credit hours: %d\n", course->hours);
    printf("Enrolled students: %d\n", course->size);

    //Be freee little memory!!
    free(course);
}

/**
 * TODO: Implement function
 * TODO: check if course exists and return error if false
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void updateRecord(FILE* courseFile){
    COURSE *course=malloc(sizeof(COURSE));
    setSeekPosition(courseFile);

    //Be freeee little memory!!!
    free(course);
}

/**
 * TODO: Implement function
 * TODO: check if course exists and return error if false
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void deleteRecord(FILE* courseFile){
    //Just set hours field to zero.
    COURSE *course=malloc(sizeof(COURSE));
    setSeekPosition(courseFile);

    //Be freeeee little memory!!!!
    free(course);
}