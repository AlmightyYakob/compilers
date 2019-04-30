#include <stdio.h>
#include <stdlib.h>

int main(){
    int x;
    int y;
    scanf("%d", &x);
    for(y = -1; y < x; y = y + 3) {
        printf("%d", y);
    }
}
