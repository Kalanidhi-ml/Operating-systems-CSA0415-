#include <stdio.h>
#include <string.h>

struct Directory {
    char dirname[20];
    char filenames[100][20];
    int fileCount;
};

int main() {
    struct Directory dir;
    dir.fileCount = 0;

    printf("Enter directory name: ");
    scanf("%s", dir.dirname);

    int choice;
    char filename[20];

    while (1) {
        printf("\n--- SINGLE LEVEL DIRECTORY ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (dir.fileCount >= 100) {
                    printf("Directory is full!\n");
                } else {
                    printf("Enter file name to create: ");
                    scanf("%s", filename);
                    int found = 0;
                    for (int i = 0; i < dir.fileCount; i++) {
                        if (strcmp(dir.filenames[i], filename) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (found) {
                        printf("File already exists!\n");
                    } else {
                        strcpy(dir.filenames[dir.fileCount], filename);
                        dir.fileCount++;
                        printf("File created successfully.\n");
                    }
                }
                break;

            case 2:
                printf("Enter file name to delete: ");
                scanf("%s", filename);
                int index = -1;
                for (int i = 0; i < dir.fileCount; i++) {
                    if (strcmp(dir.filenames[i], filename) == 0) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    printf("File not found!\n");
                } else {
                    for (int i = index; i < dir.fileCount - 1; i++) {
                        strcpy(dir.filenames[i], dir.filenames[i + 1]);
                    }
                    dir.fileCount--;
                    printf("File deleted successfully.\n");
                }
                break;

            case 3:
                printf("Enter file name to search: ");
                scanf("%s", filename);
                int found = 0;
                for (int i = 0; i < dir.fileCount; i++) {
                    if (strcmp(dir.filenames[i], filename) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    printf("File is present in the directory.\n");
                } else {
                    printf("File not found!\n");
                }
                break;

            case 4:
                if (dir.fileCount == 0) {
                    printf("Directory is empty.\n");
                } else {
                    printf("Files in directory '%s':\n", dir.dirname);
                    for (int i = 0; i < dir.fileCount; i++) {
                        printf("- %s\n", dir.filenames[i]);
                    }
                }
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}