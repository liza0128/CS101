#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE* fp;
    fp = fopen("a.bin", "w+");
    fclose(fp);
    return 0;
}
