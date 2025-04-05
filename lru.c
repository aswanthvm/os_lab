#include <stdio.h>
#define MAX_FRAMES 3
#define MAX_PAGES 20

int frames[MAX_FRAMES], counter[MAX_FRAMES];

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1, counter[i] = 0;
}

void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++)
        printf(frames[i] != -1 ? "%d " : "- ");
    printf("\n");
}

int findLRU() {
    int max = counter[0], pos = 0;
    for (int i = 1; i < MAX_FRAMES; i++)
        if (counter[i] > max) max = counter[i], pos = i;
    return pos;
}

void LRU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d is already there\n", page);
                break;
            }
        }

        if (!found) {
            int lru = findLRU();
            printf("page %d is loaded in frame %d\n", page, lru);
            frames[lru] = page;
            counter[lru] = 0;
            page_faults++;
        }

        for (int j = 0; j < MAX_FRAMES; j++)
            counter[j]++;
        for (int j = 0; j < MAX_FRAMES; j++)
            if (frames[j] == page) {
                counter[j] = 0;
                break;
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
    LRU(pages, n);
    return 0;
}
