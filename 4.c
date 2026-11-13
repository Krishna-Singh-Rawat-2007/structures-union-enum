// Structures - 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rollno;
    char name[50];
    int age;
    float gpa;
} Student;

Student* create_student_list(int *capacity) {
    printf("Enter the number of student to list");
    int number_of_student = 0;
    scanf("%d", &number_of_student);
    if(number_of_student == 0){
        printf("No Memory allocated\n");
        return NULL;
    }
    else if(number_of_student < 0){
        printf("Number of students cannot be negaitve\n");
        return NULL;
    }
    else if(number_of_student > 1000000){
        printf("No Memory allocated\n");
        return NULL;
    }
    else{
        Student *Student_list = (Student*) malloc(number_of_student * sizeof(Student));
        if (Student_list == NULL){
        printf("Memory Allocation falied\n");
        return NULL;
    }
    else{
        printf("Memory Allocation was successfull");
        *capacity =number_of_student;
        return Student_list;
       
    }
    }
    

}

int add_student(Student *studs, int Rollno, char *name, int age, float gpa, int *count, int capacity) {
   
    // Checking for duplicate roll number 
    for (int i = 0; i < *count ; i++) {
        if (studs[i].rollno == Rollno) {
            printf("Roll number already exists!\n");
            return 1;
        }
    }
     if (*count >= capacity) {
        printf("No memory left! Cannot add another student.\n");
        return 1;
    }
    if (strlen(name) >=50){
        printf("Name exceeds the size limit");
        return 1;
    }
    if (age< 16 || age > 100){
        printf("age is not pe requirement");
        return 1;
    }
    if (gpa >4 || gpa<0){
        printf("GPA is not how it should be(more than 4 or less than 0)");
        return 1;
    }
    if (Rollno <= 0) {
    printf("Roll number must be positive!\n");
    return 1;
    }

    // Insert at the next available index
    studs[*count].rollno = Rollno;
    studs[*count].age = age;
    studs[*count].gpa = gpa;
    strcpy(studs[*count].name, name);
    (*count)++;

    return 0;
}

void display_students(Student *students, int count) {
    if (count==0){
        printf("No records available\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("Rollno: %d,Name: %s, Age: %d, GPA: %.2f\n",students[i].rollno, students[i].name, students[i].age, students[i].gpa);
    }
}
void search_by_Rollno(Student *studs, int count, int rollno) {
     if ( count==0 ){
        printf("No records available\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        if (studs[i].rollno == rollno) {
            printf("Student found!\n");
            printf("Name: %s\n", studs[i].name);
            printf("Age: %d\n", studs[i].age);
            printf("GPA: %.2f\n", studs[i].gpa);
            return;
        }
    }

    printf("Student not found!\n");

}
void Update_student_info(Student *studs, int count, int rollno){
    if (count==0){
        printf("No records available\n");
        return;
    }
    for(int i= 0; i<count; i++){
        if (studs[i].rollno == rollno){
            printf("Student found!\n");
            int age;
            float gpa;
            char name[50];
            printf("Enter new name: ");
            scanf(" %49[^\n]", name);
            
            if (strlen(name) >50){
                printf("Name exceeds the size limit");
                return ;
            }
            printf("Enter the new age");
            scanf("%d", &age);


           if (age< 16 || age > 100){
                printf("age is not pe requirement");
                return ;
            }
            printf("Enter the new gpa");
            scanf("%f", &gpa);
            
            if (gpa >4 || gpa<0){
                printf("GPA is not how it should be(more than 4 or less than 0)");
                return ;
            }
            studs[i].age = age;
            studs[i].gpa = gpa;
            strcpy(studs[i].name, name);
            return ; 
        }
        
    }
    printf("record not found");
}
void delete_student(Student *studs, int *count, int rollno){
    if (*count==0){
        printf("there is no records");
        return;

    }
    for(int i= 0; i <(*count);i++){
        if (studs[i].rollno == rollno){
            for(int j =i;j<((*count) - 1); j++){
                studs[j]=studs[j+1];

            } 
            (*count)--;
            printf("Deleted successfully");
            return;
        }
        

    }
    printf("Student not found!\n");
}

void gpa_summary(Student *studs, int count) {

    if (count == 0) {
        printf("No student records available!\n");
        return;
    }

    int highest = 0;
    int lowest = 0;
    float total = 0;

    for (int i = 0; i < count; i++) {

        if (studs[i].gpa > studs[highest].gpa) {
            highest = i;
        }

        if (studs[i].gpa < studs[lowest].gpa) {
            lowest = i;
        }

        total += studs[i].gpa;
    }

    printf("\n--- GPA Summary ---\n");

    printf("\nStudent with Highest GPA:\n");
    printf("Roll No: %d\n", studs[highest].rollno);
    printf("Name: %s\n", studs[highest].name);
    printf("GPA: %.2f\n", studs[highest].gpa);

    printf("\nStudent with Lowest GPA:\n");
    printf("Roll No: %d\n", studs[lowest].rollno);
    printf("Name: %s\n", studs[lowest].name);
    printf("GPA: %.2f\n", studs[lowest].gpa);

    printf("\nAverage GPA: %.2f\n", total / count);
}


void sort_students(Student *studs, int count) {

    if (count == 0) {
        printf("No student records available!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {

        for (int j = 0; j < count - i - 1; j++) {

            // Sort GPA in descending order
            // If GPA is equal, sort roll number in ascending order
            if (studs[j].gpa < studs[j + 1].gpa ||
               (studs[j].gpa == studs[j + 1].gpa &&
                studs[j].rollno > studs[j + 1].rollno)) {

                Student temp = studs[j];
                studs[j] = studs[j + 1];
                studs[j + 1] = temp;
            }
        }
    }

    printf("Students sorted successfully!\n");
    display_students(studs, count);
}
Student* increase_capacity(Student *studs, int *capacity) {

    int new_capacity = (*capacity) * 2;

    Student *temp = realloc(studs, new_capacity * sizeof(Student));

    if (temp == NULL) {
        printf("Memory reallocation failed!\n");
        return studs;
    }

    *capacity = new_capacity;

    printf("Memory expanded successfully!\n");

    return temp;

}
void free_student_list(Student *students) {
    free(students);
}

int main() {

    int count = 0;
    int capacity = 0;
    int choice;
    int rollno, age;
    float gpa;
    char name[50];
    int i = 1;
    char option = 'y';

    Student *studs = NULL;

    while (i == 1) {

        printf("\n====== STUDENT MANAGEMENT SYSTEM ======\n"
               "1. Create Student List\n"
               "2. Add Student\n"
               "3. Display Students\n"
               "4. Search Student\n"
               "5. Update Student\n"
               "6. Delete Student\n"
               "7. GPA Summary\n"
               "8. Sort Students\n"
               "9. Exit\n"
               "\nEnter your choice: ");

        scanf("%d", &choice);

        if (choice == 1) {

            if (studs != NULL) {
                printf("Student list already exists!\n");
            }
            else {
                studs = create_student_list(&capacity);
            }

        }

        else if (choice == 2) {

            if (studs == NULL) {
                printf("Create the student list first!\n");
            }
            else {
                printf("Enter roll number: ");
                scanf("%d", &rollno);

                printf("Enter name: ");
                scanf(" %49[^\n]", name);

                printf("Enter age: ");
                scanf("%d", &age);

                printf("Enter GPA: ");
                scanf("%f", &gpa);

                if (count >= capacity) {
                    int old_capacity = capacity;
                    studs = increase_capacity(studs, &capacity);

                    if (capacity == old_capacity) {
                        printf("Unable to add student!\n");
                    }
                    else {
                        add_student(studs, rollno, name, age, gpa,
                                    &count, capacity);
                    }
                }
                else {
                    add_student(studs, rollno, name, age, gpa,
                                &count, capacity);
                }
            }

        }

        else if (choice == 3) {
            display_students(studs, count);
        }

        else if (choice == 4) {
            printf("Enter roll number to search: ");
            scanf("%d", &rollno);
            search_by_Rollno(studs, count, rollno);
        }

        else if (choice == 5) {
            printf("Enter roll number to update: ");
            scanf("%d", &rollno);
            Update_student_info(studs, count, rollno);
        }

        else if (choice == 6) {
            printf("Enter roll number to delete: ");
            scanf("%d", &rollno);
            delete_student(studs, &count, rollno);
        }

        else if (choice == 7) {
            gpa_summary(studs, count);
        }

        else if (choice == 8) {
            sort_students(studs, count);
        }

        else if (choice == 9) {
            printf("Exiting program...\n");
            free_student_list(studs);
            return 0;
        }

        else {
            printf("Invalid choice!\n");
        }
        i = 0;
        printf("do you wish to continue? (y/n)");
        scanf(" %c", &option);
        if (option=='y'){
            i = 1;
        }
        else {
            free_student_list(studs);
            return 0;
    }
}



