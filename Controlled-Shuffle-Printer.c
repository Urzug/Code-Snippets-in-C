#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    In-place Fisher–Yates shuffle.
    Produces a uniform random permutation of the array.
*/
static void shuffle_ints(int *a, int n) {
    for (int i = n - 1; i > 0; --i) {
        // Pick a random index from 0..i
        int j = rand() % (i + 1);

        // Swap a[i] and a[j]
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

/*
    Prints `steps` numbers using a controlled shuffle of 1..10.

    Guarantees:
    - Every block of 10 outputs is a permutation of 1..10.
    - No number is ever printed twice in a row, even across block boundaries.
*/
void printControlledShuffle(int steps) {
    const int N = 10;

    int buf[N];        // Holds the current shuffled cycle
    int idx = N;       // Current position in buf; set to N to force initial fill
    int last = -1;     // Last printed value; -1 means "none yet"

    while (steps-- > 0) {
        // If we've exhausted the current cycle, generate a new one
        if (idx >= N) {
            // Fill buffer with 1..10
            for (int i = 0; i < N; ++i)
                buf[i] = i + 1;

            // Shuffle the buffer
            shuffle_ints(buf, N);

            // Prevent boundary repeat:
            // If the first element of the new shuffle equals the last
            // printed value, swap it with a random element in positions 1..9.
            if (last != -1 && buf[0] == last) {
                int r = 1 + (rand() % (N - 1)); // range: 1..9
                int tmp = buf[0];
                buf[0] = buf[r];
                buf[r] = tmp;
            }

            idx = 0;
        }

        // Emit next value
        int v = buf[idx++];
        printf("%d\n", v);

        // Update state
        last = v;
    }
}

int main(void) {
    // Seed the RNG once at program start
    srand((unsigned)time(NULL));

    // Example: print 50 values
    printControlledShuffle(50);

    return 0;
}
