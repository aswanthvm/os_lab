#include <stdio.h>

void initialize(int frames[], int fsize) {
    for (int i = 0; i < fsize; i++)
        frames[i] = -1;
}

void printframes(int frames[], int fsize) {
    for (int i = 0; i < fsize; i++)
        frames[i] == -1 ? printf("- ") : printf("%d ", frames[i]);
    printf("\n");
}

void fifo(int frames[], int pages[], int fsize, int n) {
    int front = 0, rear = -1, page_faults = 0;

    for (int i = 0; i < n; i++) {
        int found = 0, page = pages[i];

        for (int j = 0; j < fsize; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d already there\n", page);
                break;
            }
        }

        if (!found) {
            page_faults++;
            rear = (rear + 1) % fsize;
            frames[rear] = page;
            printf("page %d loaded in frame %d\n", page, rear);
        }

        printframes(frames, fsize);
    }

    printf("Total page faults: %d\n", page_faults);
}

int main() {
    int n, fsize;
    printf("Enter no. of pages: ");
    scanf("%d", &n);
    printf("Enter no. of frames: ");
    scanf("%d", &fsize);

    int pages[n], frames[fsize];
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    initialize(frames, fsize);
    fifo(frames, pages, fsize, n);
    return 0;
}
