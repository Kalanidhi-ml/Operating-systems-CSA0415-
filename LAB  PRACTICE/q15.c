#include <stdio.h>
#include <string.h>

struct File {
    char filename[20];
};

struct UserDir {
    char dirname[20];
    struct File files[10];
    int fileCount;
};

int main() {
    struct UserDir md[10];
    int dirCount = 0;
    int choice;
    char dname[20], fname[20];

    while (1) {
        printf("\n--- TWO LEVEL DIRECTORY STRUCTURE ---\n");
        printf("1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display Directory Structure\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (dirCount >= 10) {
                    printf("Master directory is full!\n");
                } else {
                    printf("Enter directory name: ");
                    scanf("%s", dname);
                    int found = 0;
                    for (int i = 0; i < dirCount; i++) {
                        if (strcmp(md[i].dirname, dname) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (found) {
                        printf("Directory already exists!\n");
                    } else {
                        strcpy(md[dirCount].dirname, dname);
                        md[dirCount].fileCount = 0;
                        dirCount++;
                        printf("Directory created successfully.\n");
                    }
                }
                break;

            case 2:
                printf("Enter directory name: ");
                scanf("%s", dname);
                int dirIndex = -1;
                for (int i = 0; i < dirCount; i++) {
                    if (strcmp(md[i].dirname, dname) == 0) {
                        dirIndex = i;
                        break;
                    }
                }
                if (dirIndex == -1) {
                    printf("Directory not found!\n");
                } else {
                    if (md[dirIndex].fileCount >= 10) {
                        printf("Directory is full!\n");
                    } else {
                        printf("Enter file name: ");
                        scanf("%s", fname);
                        int fileFound = 0;
                        for (int i = 0; i < md[dirIndex].fileCount; i++) {
                            if (strcmp(md[dirIndex].files[i].filename, fname) == 0) {
                                fileFound = 1;
                                break;
                            }
                        }
                        if (fileFound) {
                            printf("File already exists in this directory!\n");
                        } else {
                            strcpy(md[dirIndex].files[md[dirIndex].fileCount].filename, fname);
                            md[dirIndex].fileCount++;
                            printf("File created successfully.\n");
                        }
                    }
                }
                break;

            case 3:
                printf("Enter directory name: ");
                scanf("%s", dname);
                dirIndex = -1;
                for (int i = 0; i < dirCount; i++) {
                    if (strcmp(md[i].dirname, dname) == 0) {
                        dirIndex = i;
                        break;
                    }
                }
                if (dirIndex == -1) {
                    printf("Directory not found!\n");
                } else {
                    printf("Enter file name to delete: ");
                    scanf("%s", fname);
                    int fileIndex = -1;
                    for (int i = 0; i < md[dirIndex].fileCount; i++) {
                        if (strcmp(md[dirIndex].files[i].filename, fname) == 0) {
                            fileIndex = i;
                            break;
                        }
                    }
                    if (fileIndex == -1) {
                        printf("File not found!\n");
                    } else {
                        for (int i = fileIndex; i < md[dirIndex].fileCount - 1; i++) {
                            strcpy(md[dirIndex].files[i].filename, md[dirIndex].files[i + 1].filename);
                        }
                        md[dirIndex].fileCount--;
                        printf("File deleted successfully.\n");
                    }
                }
                break;

            case 4:
                printf("Enter file name to search: ");
                scanf("%s", fname);
                int foundGlobal = 0;
                for (int i = 0; i < dirCount; i++) {
                    for (int j = 0; j < md[i].fileCount; j++) {
                        if (strcmp(md[i].files[j].filename, fname) == 0) {
                            printf("File found in directory: %s\n", md[i].dirname);
                            foundGlobal = 1;
                        }
                    }
                }
                if (!foundGlobal) {
                    printf("File not found!\n");
                }
                break;

            case 5:
                if (dirCount == 0) {
                    printf("Master directory is empty.\n");
                } else {
                    printf("\n--- DIRECTORY STRUCTURE ---\n");
                    for (int i = 0; i < dirCount; i++) {
                        printf("Directory: %s\n", md[i].dirname);
                        if (md[i].fileCount == 0) {
                            printf("  (Empty)\n");
                        } else {
                            for (int j = 0; j < md[i].fileCount; j++) {
                                printf("  ├── File: %s\n", md[i].files[j].filename);
                            }
                        }
                    }
                }
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}