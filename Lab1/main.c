#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    char surname[50];
    int age;
};

int main() {
    int numStudents;

    printf("How many students are in your group -> ");
    scanf("%d", &numStudents);

    struct Student *students = (struct Student *)malloc(numStudents * sizeof(struct Student));

    for (int i = 0; i < numStudents; i++) {
        printf("Enter name -> ");
        scanf("%s", students[i].name);

        printf("Enter surname -> ");
        scanf("%s", students[i].surname);

        printf("Enter age -> ");
        scanf("%d", &students[i].age);
    }

    printf("\nYou have added the following students:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Surname: %s\n", students[i].surname);
        printf("Age: %d\n", students[i].age);
        printf("\n");
    }

    free(students);

    return 0;
}
