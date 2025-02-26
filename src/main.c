#include "2d.h"
#include "3d.h"
#include "SDL.h"

int main(void) {
    int cmd = 0;
    printf("Would you like to run the 2D (2) or 3D (3) demo: ");
    scanf("%d", &cmd);
    if (cmd != 2 && cmd != 3) {
        printf("You need to select either 2D (2) or 3D (3).\n");
        exit(EXIT_FAILURE);
    }
    if (cmd == 2) {
        return run_2d();
    }
    if (cmd == 3) {
        return run_3d();
    }
}