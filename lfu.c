#include <stdio.h>
#define MAX_FRAMES 3
#define MAX_PAGES 20

int frames[MAX_FRAMES], counts[MAX_FRAMES];

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1, counts[i] = 0;
}

void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++)
        printf(frames[i] != -1 ? "%d " : "- ");
    printf("\n");
}

int findLFU() {
    int min = counts[0], pos = 0;
    for (int i = 1; i < MAX_FRAMES; i++)
        if (counts[i] < min) min = counts[i], pos = i;
    return pos;
}

void LFU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                counts[j]++;
                found = 1;
                printf("page %d is already in memory\n", page);
                break;
            }
        }

        if (!found) {
            int pos = findLFU();
            frames[pos] = page;
            counts[pos] = 1;
            page_faults++;
            printf("page %d is loaded in frame %d\n", page, pos);
        }

        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES], n;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    initialize();
    LFU(pages, n);
    return 0;
}
