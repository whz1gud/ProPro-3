#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    char name[30];
    char surname[30];
    int course;     // year of study
    double average; // average grade

    int load;             // number of courses
    char courses[10][30]; // course names
    int grades[10];       // course grades

    char languages[100]; // spoken languages

} Student;

int main(int argc, char *argv[])
{
    FILE *db = NULL;
    // open database file for reading, provide a parameter or use default "db.bin"
    if (argc > 1)
        db = fopen(argv[1], "rb");
    else
        db = fopen("db.bin", "rb");

    if (db)
    {
        Student students[1000]; // all the data goes here
        int size = 0;           // how many students in database

        // reading data from file
        fread(&size, sizeof(int), 1, db);

        for (int i = 0; i < size; i++)
        {
            fread(&students[i], sizeof(Student), 1, db);
        }
        printf("%d records loaded succesfully\n", size);

        // MODIFY CODE BELOW

        int counterDemo = 0; // for counting students

        for (int i = 0; i < size; ++i)
        {                            // process all the student records in database
            Student s = students[i]; // store data for each student in s

            double anotherDemo = 0; // for counting courses/grades
            double gradeSum = 0;
            double recountedAvg = 0;

            for (int i = 0; i < s.load; ++i)
            {                  // process each course taken by the student                  // *** second filter, conditions on the course/grade
                ++anotherDemo; // counting courses
                gradeSum += s.grades[i];
            }

            if (anotherDemo == 0)
            {
                recountedAvg = 0;
            }
            else
            {
                recountedAvg = gradeSum / anotherDemo;
            }
            
            if (anotherDemo == s.load && recountedAvg != s.average)
            {
                printf("GPA should be: %0.2f, instead of %0.2f!\n", recountedAvg, s.average);
                ++counterDemo;                                                                                        // counting students
                printf("%s %s, Year: %d; GPA: %0.2f; Courses: %d\n", s.name, s.surname, s.course, s.average, s.load); // print student data
                for (int i = 0; i < s.load; ++i)
                {
                    printf("%s - %d | ", s.courses[i], s.grades[i]);
                }
                printf("\nLanguages: %s\n", s.languages);
                printf("\n");
            } // *** third filter, various other conditions
        }
        printf("Filter applied, %d students found\n", counterDemo); // how many passed the filters
        fclose(db);
    }
    else
    {
        printf("File db.bin not found, check current folder\n");
    }

    return 0;
}