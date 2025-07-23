#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee_data.dat"

typedef struct {
    int id;
    char name[50];
    char designation[100];
    float salary;
} Employee;

void addEmployee();
void deleteEmployee();
void editEmployee();
void displayEmployeeById();
void displayAllEmployees();
void saveToFile(Employee emp, const char *mode);

int main() {
    int choice;

    while (1) {
        printf("\nEmployee Data Management System\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Edit Employee\n");
        printf("4. Display Employee by ID\n");
        printf("5. Display All Employees\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                editEmployee();
                break;
            case 4:
                displayEmployeeById();
                break;
            case 5:
                displayAllEmployees();
                break;
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addEmployee() {
    Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Employee Designation : ");
    scanf("%s",emp.designation);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    saveToFile(emp, "a");
    printf("Employee added successfully.\n");
}

void saveToFile(Employee emp, const char *mode) {
    FILE *file = fopen(FILENAME, mode);
    if (file == NULL) {
        perror("Error opening file.\n");
        return;
    }

    fwrite(&emp, sizeof(Employee), 1, file);
    fclose(file);
}

void deleteEmployee() {
    int id;
    Employee emp;
    int found = 0;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    FILE *file = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.txt", "wb");

    if (file == NULL || temp == NULL) {
        perror("Error opening file.\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
        } else {
            fwrite(&emp, sizeof(Employee), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Employee deleted successfully.\n");
    else
        printf("Employee with ID %d not found.\n", id);
}

void editEmployee() {
    int id;
    Employee emp;
    int found = 0;

    printf("Enter Employee ID to edit: ");
    scanf("%d", &id);

    FILE *file = fopen(FILENAME, "rb+" );
    if (file == NULL) {
        perror("Error opening file.\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
            printf("Enter new Employee Name: ");
            scanf(" %[^\n]", emp.name);
            printf("Enter new Employee designation : ");
            scanf("%s", emp.designation);
            printf("Enter new Employee Salary: ");
            scanf("%f", &emp.salary);
            fwrite(&emp, sizeof(Employee), 1, file);
            break;
        }
    }

    fclose(file);

    if (found)
        printf("Employee updated successfully.\n");
    else
        printf("Employee with ID %d not found.\n", id);
}

void displayEmployeeById() {
    int id;
    Employee emp;
    int found = 0;

    printf("Enter Employee ID to display: ");
    scanf("%d", &id);

    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file.\n");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
            printf("\nEmployee ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Designation : %s\n", emp.designation);
            printf("Salary: %.2f\n", emp.salary);
            break;
        }
    }

    fclose(file);

    if (!found)
        printf("Employee with ID %d not found.\n", id);
}

void displayAllEmployees() {
    Employee emp;

    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file or no employees found.\n");
        return;
    }

    printf("\nEmployee List:\n");
    printf("----------------------------------\n");
    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("ID: %d | Name: %s | Designation: %s | Salary: %.2f\n", emp.id, emp.name, emp.designation, emp.salary);
    }
    printf("----------------------------------\n");

    fclose(file);
}