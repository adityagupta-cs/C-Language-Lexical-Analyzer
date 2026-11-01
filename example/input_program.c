#include <stdio.h>

int main() {

    int age = 20;
    float marks = 89.5;

    char grade = 'A';

    // Display student details
    printf("Age: %d\n", age);
    printf("Marks: %.2f\n", marks);

    if (age >= 18) {
        printf("Eligible\n");
    }

    return 0;
}