#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to print results
void printBins(int binsUsed) {
    printf("Total bins used: %d\n", binsUsed);
}

/* ---------------- FIRST FIT ---------------- */
void firstFit(int weight[], int n, int capacity) {
    int bin_rem[MAX];
    int binsUsed = 0;

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < binsUsed; j++) {
            if (bin_rem[j] >= weight[i]) {
                bin_rem[j] -= weight[i];
                break;
            }
        }
        if (j == binsUsed) {
            bin_rem[binsUsed] = capacity - weight[i];
            binsUsed++;
        }
    }
    printBins(binsUsed);
}

/* ---------------- FIRST FIT DECREASING ---------------- */
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void firstFitDecreasing(int weight[], int n, int capacity) {
    int sorted[MAX];
    for (int i = 0; i < n; i++)
        sorted[i] = weight[i];

    qsort(sorted, n, sizeof(int), compare);
    
    printf("First Fit Decreasing: ");
    firstFit(sorted, n, capacity);
}

/* ---------------- BEST FIT ---------------- */
void bestFit(int weight[], int n, int capacity) {
    int bin_rem[MAX];
    int binsUsed = 0;

    for (int i = 0; i < n; i++) {
        int min_space = capacity + 1;
        int bestIndex = -1;

        for (int j = 0; j < binsUsed; j++) {
            if (bin_rem[j] >= weight[i] && (bin_rem[j] - weight[i]) < min_space) {
                bestIndex = j;
                min_space = bin_rem[j] - weight[i];
            }
        }

        if (bestIndex != -1) {
            bin_rem[bestIndex] -= weight[i];
        } else {
            bin_rem[binsUsed] = capacity - weight[i];
            binsUsed++;
        }
    }
    printf("Best Fit: ");
    printBins(binsUsed);
}

/* ---------------- MAIN FUNCTION ---------------- */
int main() {
    int n, capacity;
    int weight[MAX];

    printf("Enter number of items: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter bin capacity: ");
    if (scanf("%d", &capacity) != 1) return 1;

    printf("Enter item weights:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }

    printf("\n--- Results ---\n");
    printf("First Fit: ");
    firstFit(weight, n, capacity);
    
    firstFitDecreasing(weight, n, capacity);
    
    bestFit(weight, n, capacity);

    return 0;
}
