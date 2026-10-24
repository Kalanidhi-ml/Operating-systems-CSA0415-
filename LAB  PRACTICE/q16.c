#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

int main() {
    FILE *fp;
    struct Employee emp;
    int choice, id, found;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
    }

    while (1) {
        printf("\n--- RANDOM ACCESS EMPLOYEE DATABASE ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID (Random Access)\n");
        printf("4. Update Employee Salary by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.id);
                printf("Enter Name: ");
                scanf("%s", emp.name);
                printf("Enter Salary: ");
                scanf("%f", &emp.salary);

                fseek(fp, 0, SEEK_END);
                fwrite(&emp, sizeof(struct Employee), 1, fp);
                printf("Employee record added successfully.\n");
                break;

            case 2:
                rewind(fp);
                printf("\n--- EMPLOYEE RECORDS ---\n");
                printf("ID\tName\t\tSalary\n");
                while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
                    printf("%d\t%s\t\t%.2f\n", emp.id, emp.name, emp.salary);
                }
                break;

            case 3:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                rewind(fp);
                found = 0;
                while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
                    if (emp.id == id) {
                        printf("\nRecord Found:\n");
                        printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.id, emp.name, emp.salary);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Employee with ID %d not found.\n", id);
                }
                break;

            case 4:
                printf("Enter Employee ID to update salary: ");
                scanf("%d", &id);
                rewind(fp);
                found = 0;
                while (fread(&emp, sizeof(struct Employee), 1, fp) == 1) {
                    if (emp.id == id) {
                        printf("Enter new salary: ");
                        scanf("%f", &emp.salary);
                        
                        fseek(fp, -sizeof(struct Employee), SEEK_CUR);
                        fwrite(&emp, sizeof(struct Employee), 1, fp);
                        fflush(fp);
                        
                        printf("Record updated successfully.\n");
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Employee with ID %d not found.\n", id);
                }
                break;

            case 5:
                fclose(fp);
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}