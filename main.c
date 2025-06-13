#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 1000

typedef struct { // struct of values
        int id;        
        int age;
        float units;
        float grades;
        char name[50];
        char course[7];
} Student_db;

// FUNCTIONS
void menu();
void option_menu();
Student_db *input(Student_db *records, int *n, int *j);
void search(Student_db *records, int n);
void update_name(Student_db *records);
void update_course(Student_db *records);
void update_units(Student_db *records);
void update_grades(Student_db *records);
void print_to_file(FILE *fptr, Student_db *records, int n);
void read_file(FILE *fptr, Student_db *records, int n);
int num_students(int n);

int main() {

    FILE *fptr = fopen("test1.txt", "a+");
    
    if (!fptr) {
       printf("File Opening Failed.\n");
       return 1;          
    }
    
    int num = 2, i = 0;
    
    Student_db *records = malloc(num * sizeof(Student_db));
    
    if (!records) {
       printf("Memory Allocation Failed.\n");
       return 1;          
    }
    
    while (1) {
    
        int choice;
        menu();
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: records = input(records, &num, &i); break;
            case 2: search(records, i); break;
            case 3: read_file(fptr, records, i); break;
            case 4: printf("\nTOTAL NUMBER OF STUDENTS ENROLLED: %d\n\n", num_students(i)); break;
            case 5: printf("\nExiting Program....\n\n"); free(records); fclose(fptr); return 0;
            default: printf("\nInvalid Input.\n"); break;
        
        }
 
    }
    
    return 0;
}

void menu()
{
     printf("=== STUDENT MANAGEMENT SYSTEM ===\n");
     printf("[1] - ADD A STUDENT\n");
     printf("[2] - SEARCH AND UPDATE A STUDENT\n");
     printf("[3] - SHOW ALL STUDENT RECORDS\n");
     printf("[4] - SHOW TOTAL NUMBER OF STUDENTS\n");
     printf("[5] - EXIT THE PROGRAM\n\n");
     printf("ENTER YOUR CHOICE: ");
}

Student_db *input(Student_db *records, int *n, int *j)
{
           if (*j >= *n) {
              *n += 2;
              Student_db *temp = realloc(records, (*n) * sizeof(Student_db));
              if (!temp) {
                 printf("Memory Reallocation Failed.\n");
                 free(records);
                 return NULL;
              }
              records = temp;
           }
           
           printf("\nENTER STUDENT INFORMATION\n");
        // User Inputs
           printf("Enter Student ID: ");
           scanf("%d", &records[*j].id);
           getchar();
           
           printf("Enter Student Name: ");
           fgets(records[*j].name, sizeof(records[*j].name), stdin);
           records[*j].name[strcspn(records[*j].name, "\n")] = '\0';
           
           printf("Enter Student Course: ");
           fgets(records[*j].course, sizeof(records[*j].course), stdin);
           records[*j].course[strcspn(records[*j].course, "\n")] = '\0';
           
           printf("Enter Student Age: ");
           scanf("%d", &records[*j].age);
           
           printf("Enter Student Units: ");
           scanf("%f", &records[*j].units);
           
           printf("Enter Student Grades: ");
           scanf("%f", &records[*j].grades);
           
           getchar();
           
           (*j)++;
           
           printf("\nStudent Added Successfully.\n\n");\
           return records;
}

void search(Student_db *records, int n)
{
     int key, flag = 0, opt, i;
     
     printf("Enter Student ID to Search: ");
     scanf("%d", &key);
     
     
     for (i = 0; i < n; i++) {
         if (key == records[i].id) {
                 option_menu();
                 scanf("%d", &opt);
                 
                 switch(opt) {
                        // Update Functions
                        case 1: update_name(&records[i]); flag = 1; break;
                        case 2: update_course(&records[i]); flag = 1; break;
                        case 3: update_units(&records[i]); flag = 1; break;
                        case 4: update_grades(&records[i]); flag = 1; break;
                        default: printf("\nInvalid Input.\n"); break;
                 }
         }
     }
     
     if (!flag) {
        printf("\nStudent Not Found in the System.\n\n");
     }
     

}

void option_menu()
{
     printf("\n[1] - UPDATE NAME\n");
     printf("[2] - UPDATE COURSE\n");
     printf("[3] - UPDATE UNITS\n");
     printf("[4] - UPDATE GRADES\n\n");
     printf("ENTER YOUR CHOICE: ");

}

void update_name(Student_db *records)
{
     getchar();
     char upd_name[50];

     printf("Update a Name: ");
     fgets(upd_name, sizeof(upd_name), stdin);
     upd_name[strcspn(upd_name, "\n")] = '\0';

     strcpy(records->name, upd_name);
     printf("\nStudent Name Updated Successfully.\n\n");
}

void update_course(Student_db *records)
{
     getchar();
     char upd_course[8];

     printf("Update a Course: ");
     fgets(upd_course, sizeof(upd_course), stdin);
     upd_course[strcspn(upd_course, "\n")] = '\0';

     strcpy(records->course, upd_course);
     printf("\nStudent Course Updated Successfully.\n\n");
}

void update_units(Student_db *records)
{
     float upd_units;
     
     printf("Update Student Units: ");
     scanf("%f", &upd_units);

     records->units = upd_units;
     printf("\nStudent Units Updated Successfully.\n\n");
}

void update_grades(Student_db *records)
{
     float upd_grades;
     
     printf("Update Student Grades: ");
     scanf("%f", &upd_grades);

     records->grades = upd_grades;
     printf("\nStudent Grades Updated Successfully.\n\n");
}

void print_to_file(FILE *fptr, Student_db *records, int n) // Print to File Text
{
     int i = 0;
     fprintf(fptr, "\n=== STUDENT DATABASE ===\n");
     
     for (i = 0; i < n; i++) 
     {
         fprintf(fptr, "Student #%d:\n", i + 1);
         fprintf(fptr, "Name: %s\n", records[i].name);
         fprintf(fptr, "Age: %d\n", records[i].age);
         fprintf(fptr, "ID: %d\n", records[i].id);
         fprintf(fptr, "Course: %s\n", records[i].course);
         fprintf(fptr, "Total Grade: %.2f\n", records[i].grades);
         fprintf(fptr, "Units: %.2f\n", records[i].units);
         fprintf(fptr, "------------\n\n");
     }     
     fflush(fptr);
}

void read_file(FILE *fptr, Student_db *records, int n)
{

     print_to_file(fptr, records, n);
     
     char line[size];
     rewind(fptr);
     
     while(fgets(line, sizeof(line), fptr)) {
          printf("%s", line);
     }
        // Print File Text Output
}

int num_students(int n)
{
    return n;
}
