#include <stdio.h> 
#include <string.h> 

void worstFit(int blockSize[], int m, int processSize[], int n) { 
    int allocation[n]; 
    memset(allocation, -1, sizeof(allocation)); 

    for (int i = 0; i < n; i++) { 
        int wstIdx = -1; 
        for (int j = 0; j < m; j++) { 
            if (blockSize[j] >= processSize[i]) { 
                if (wstIdx == -1 || blockSize[wstIdx] < blockSize[j]) 
                    wstIdx = j; 
            } 
        } 
        if (wstIdx != -1) { 
            allocation[i] = wstIdx; 
            blockSize[wstIdx] -= processSize[i]; 
        } 
    } 

    printf("\nProcess No.\tProcess Size\tBlock No.\n"); 
    for (int i = 0; i < n; i++) { 
        printf(" %d\t\t\t%d\t\t\t", i + 1, processSize[i]); 
        if (allocation[i] != -1) 
            printf("%d", allocation[i] + 1); 
        else 
            printf("Not Allocated"); 
        printf("\n"); 
    } 

    printf("\nFree Blocks:\n"); 
    for (int i = 0; i < m; i++) { 
        printf("%d ", blockSize[i]); 
        if (i != m - 1) printf("-> ");   
    } 
    printf("\n"); 
} 

int main() { 
    int m, n; 

    printf("Enter the number of memory blocks: "); 
    scanf("%d", &m); 
    int blockSize[m]; 

    printf("Enter the sizes of %d memory blocks: ", m); 
    for (int i = 0; i < m; i++) { 
        scanf("%d", &blockSize[i]); 
    } 

    printf("Enter the number of processes: "); 
    scanf("%d", &n); 
    int processSize[n]; 

    printf("Enter the sizes of %d processes: ", n); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &processSize[i]); 
    } 

    worstFit(blockSize, m, processSize, n); 

    return 0; 
}
