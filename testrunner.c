#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

#define MAX_FILENAME_LEN 256
#define MAX_CMD_LEN 512
#define MAX_LINE_LEN 1024

void print_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Contents of file %s:\n", filename);

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        fflush(stdout); // Flush the standard output stream
    }

    printf("\n\n");

    fclose(file);
}

int main() {
    // printf("Testing program... \n");

    DIR *dir;
    struct dirent *ent;
    char tests_folder[] = "tests";
    char cmd[MAX_CMD_LEN];

    dir = opendir(tests_folder);
    if (dir == NULL) {
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) { // Check if it's a regular file
            char filename[MAX_FILENAME_LEN];
            snprintf(filename, sizeof(filename), "%s/%s", tests_folder, ent->d_name);

            print_file_contents(filename); 

            snprintf(cmd, sizeof(cmd), "./mysh %s", filename);

            pid_t pid = fork();
            if (pid == -1) {
                perror("Fork failed");
                return EXIT_FAILURE;
            } else if (pid == 0) { // Child process
                int ret = execl("/bin/sh", "sh", "-c", cmd, NULL);
                if (ret == -1) {
                    perror("Exec failed");
                    exit(EXIT_FAILURE);
                }
            } else { // Parent process
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)) {
                    int exit_status = WEXITSTATUS(status);
                    if (exit_status != 0) {
                        printf("Error executing test %s\n", filename);
                    }
                }
            }
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}