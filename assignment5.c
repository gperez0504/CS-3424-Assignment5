//TODO: Need to redo comments. Half of them are no longer applicable

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
    //Making sure the file still exists
    if(courseFile == NULL){
        puts("ERROR: file error");
        return 0;
    }
    fseek(courseFile, 0, SEEK_SET);
    printf("Enter a course number: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    int courseNum = atoi(inputBuffer);
    fseek(courseFile, sizeof(COURSE) * (courseNum - 1), SEEK_SET);
    return courseNum;
}

/**
 * ? Can this be changed to get course and return a pointer to a course struct if course can be found?
 * Function checks the hours section of a course struct is zero and returns true if it is non-zero.
 * @param course A pointer to a course struct.
 * @return A boolean that indicates whether or not the course exists.
 */
bool courseExists(FILE* courseFile){
    unsigned courseHours;
    fseek(courseFile, 84, SEEK_CUR);
    size_t freadReturn = fread(&courseHours, sizeof(unsigned), 1, courseFile);
    fseek(courseFile, -84, SEEK_CUR);
    if((courseHours == (unsigned)0) || (freadReturn = 0)){
        return false;
    }
    return true;
}

/**
 * Function prompts the user for input and fills the course struct with it.
 * Once all input is recived it writes the struct to the courses.dat file.
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void createRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index.
    setSeekPosition(courseFile);
    //Read memory location and rebuild the course struct.
    //Check if course exists.
    if(!courseExists(courseFile)){
        COURSE *course=malloc(sizeof(COURSE));
        memset(course, (unsigned)0, sizeof(COURSE));
        //Prompt user for course data and store it in the struct.
        printf("Enter a course name: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        strcpy(course->name, inputBuffer);
        printf("Enter course schedule (MWF or TR): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        strcpy(course->schedule, inputBuffer);
        printf("Enter course credit hours: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        course->hours = (unsigned)atoi(inputBuffer);
        printf("Enter student enrollment: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        course->size = (unsigned)atoi(inputBuffer);

        //Now write the course to the file.
        fwrite(course, sizeof(COURSE), 1, courseFile);

        //Be free little memory!
        free(course);
    } else {
        puts("\nERROR: course already exists");
    }
}

/**
 * Function extracts the course struct from the file and outputs the data to the terminal.
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void readRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index.
    int courseNum = setSeekPosition(courseFile);
    //Read memory location and rebuild the course struct.
    //Check if course exists
    if(courseExists(courseFile)){
        COURSE *course=malloc(sizeof(COURSE));
        fread(course, sizeof(COURSE), 1, courseFile);
        
        //Print the course struct to the terminal.
        printf("\nCourse number: %d\n", courseNum);
        printf("Course name: %s", course->name);
        printf("Scheduled days: %s", course->schedule);
        printf("Credit hours: %d\n", course->hours);
        printf("Enrolled students: %d\n", course->size);
        
        //Be freee little memory!!
        free(course);
    } else {
        puts("\nERROR: course not found");
    }
}

/**
 * TODO: Implement function
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void updateRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index.
    setSeekPosition(courseFile);
    //Read memory location and rebuild the course struct.
    //Check if course exists
    if(courseExists(courseFile)){
        COURSE *course=malloc(sizeof(COURSE));
        fread(&course, sizeof(COURSE), 1, courseFile);

        //Be freeee little memory!!!
        free(course);
    } else {
        puts("\nERROR: course not found");
    }
}

/**
 * Function takes the requested course struct and zero's out the hours feild to "delete" it
 * @param courseFile A pointer to the courses.dat file that the program is working with.
 */
void deleteRecord(FILE* courseFile){
    //Malloc the course struct and set our cursor position using the course number as a index.
    setSeekPosition(courseFile);
    //Read memory location and rebuild the course struct.
    //Check if course exists
    if(courseExists(courseFile)){
        COURSE *course=malloc(sizeof(COURSE));
        fread(course, sizeof(COURSE), 1, courseFile);
        fseek(courseFile, -(sizeof(COURSE)), SEEK_CUR);

        //Set course hours to 0 and write the "deleted" struct back to memory
        memset(course, (unsigned)0, sizeof(COURSE));
        fwrite(course, sizeof(COURSE), 1, courseFile);

        //Be freeeee little memory!!!!
        free(course);
    } else {
        puts("\nERROR: course not found");
    }
}