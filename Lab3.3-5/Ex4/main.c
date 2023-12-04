#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generateRandomArray(double arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = (((rand() % 10001) / 100.0) - 50.0);
    }
}

double calculateAverage(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

void printArray(double arr[], int n) {
    printf("Масив: ");
    for (int i = 0; i < n; i++) {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}

int countElementsGreaterThanAverage(double arr[], int n, double average) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count++;
        }
    }
    return count;
}

double sumOfAbsoluteValuesAfterNegative(double arr[], int n) {
    double sum_after_negative = 0;
    int negative_found = 0;

    for (int i = 0; i < n; i++) {
        if (!negative_found && arr[i] < 0) {
            negative_found = 1;
        }

        if (negative_found) {
            sum_after_negative += fabs(arr[i]);
        }
    }
    return sum_after_negative;
}

int main() {
    int n;

    printf("Введіть кількість елементів масиву: ");
    scanf("%d", &n);

    double arr[n];
    int count;
    double sum_after_negative;

    generateRandomArray(arr, n);

    printArray(arr, n);

    double average = calculateAverage(arr, n);

    count = countElementsGreaterThanAverage(arr, n, average);

    sum_after_negative = sumOfAbsoluteValuesAfterNegative(arr, n);

    printf("Кількість елементів, які більші за середнє значення: %d\n", count);
    printf("Сума модулів елементів після першого від'ємного: %.2lf\n", sum_after_negative);

    return 0;
}
