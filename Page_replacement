#include <stdio.h>
#include <stdbool.h>

#define MAX 50

void printFrames(int frames[], int fault) {
    printf("PF No. %d: ", fault);
    for (int i = 0; i < 3; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

bool isInFrame(int frames[], int page) {
    for (int i = 0; i < 3; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int findOptimal(int pages[], int frames[], int current, int total) {
    int farthest = current;
    int pos = -1;
    for (int i = 0; i < 3; i++) {
        int j;
        for (j = current + 1; j < total; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == total)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

void fifo(int pages[], int n) {
    int frames[3] = {-1, -1, -1};
    int index = 0, faults = 0;
    printf("FIFO Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % 3;
            printFrames(frames, ++faults);
        }
    }
    printf("FIFO Page Faults: %d\n\n", faults);
}

void lru(int pages[], int n) {
    int frames[3] = {-1, -1, -1};
    int time[3] = {0, 0, 0};
    int count = 0, faults = 0;
    printf("LRU Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (isInFrame(frames, pages[i])) {
            for (int j = 0; j < 3; j++) {
                if (frames[j] == pages[i])
                    time[j] = ++count;
            }
        } else {
            int pos = -1;
            for (int j = 0; j < 3; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, 3);

            frames[pos] = pages[i];
            time[pos] = ++count;
            printFrames(frames, ++faults);
        }
    }
    printf("LRU Page Faults: %d\n\n", faults);
}

void optimal(int pages[], int n) {
    int frames[3] = {-1, -1, -1};
    int faults = 0;
    printf("Optimal Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, pages[i])) {
            int pos = -1;
            for (int j = 0; j < 3; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
                pos = findOptimal(pages, frames, i, n);

            frames[pos] = pages[i];
            printFrames(frames, ++faults);
        }
    }
    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int framesCount, refLen, pages[MAX];

    printf("Enter the number of Frames: ");
    scanf("%d", &framesCount);

    printf("Enter the length of reference string: ");
    scanf("%d", &refLen);

    printf("Enter the reference string: ");
    for (int i = 0; i < refLen; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(pages, refLen);
    lru(pages, refLen);
    optimal(pages, refLen);

    return 0;
}
