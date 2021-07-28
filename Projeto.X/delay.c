#include "delay.h"
#include <string.h>

void tempo(unsigned char x) {
    volatile unsigned char j, k, m, n;
    for (n = 0; n < x; n++) {
        for (m = 0; m < 100; m++) {
            for (j = 0; j < 41; j++) {
                for (k = 0; k < 3; k++);
            }
        }
    }
}