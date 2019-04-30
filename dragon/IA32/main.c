#include <stdio.h>
#include <stdlib.h>

int main(){
    int x;
    int y = 12;
    scanf("%d", &x);
    if (x > (y + 3*2)) {
        return 0;
    }
    else return 1;
}
