#include <stdio.h>

int main() {
    char line[1024];
    if (fgets(line, sizeof(line), stdin)) {
        printf("%s", line);
    }
    printf("PIPE\n");
    return 0;
}