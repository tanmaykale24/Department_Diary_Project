#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "diary.dat"

typedef struct {
    char name[100];
    char address[200];
    char date[20];
    char time[20];
    char duration[50];
} DiaryRecord;

// Function declarations
void addRecord();
void viewRecords();
void editRecord();
void deleteRecord();

int main() {
    int choice;

    printf("\n==============================================\n");
    printf(" INFORMATION TECHNOLOGY DEPARTMENT DIARY\n");
    printf("==============================================\n");

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Add Record\n");
        printf("2. View Records\n");
        printf("3. Edit Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // Clear input buffer

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: editRecord(); break;
            case 4: deleteRecord(); break;
            case 5:
                printf("\nExiting Diary System...\n");
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

// -----------------------------------------------------------
// ADD RECORD
// -----------------------------------------------------------
void addRecord() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    DiaryRecord dr;

    printf("\nEnter Name of Activity: ");
    fgets(dr.name, 100, stdin);

    printf("Enter Address/Venue: ");
    fgets(dr.address, 200, stdin);

    printf("Enter Date (DD/MM/YYYY): ");
    fgets(dr.date, 20, stdin);

    printf("Enter Time (HH:MM): ");
    fgets(dr.time, 20, stdin);

    printf("Enter Duration: ");
    fgets(dr.duration, 50, stdin);

    fwrite(&dr, sizeof(dr), 1, fp);
    fclose(fp);

    printf("\nRecord Added Successfully!\n");
}

// -----------------------------------------------------------
// VIEW RECORDS
// -----------------------------------------------------------
void viewRecords() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nNo records found!\n");
        return;
    }

    DiaryRecord dr;
    int count = 1;

    printf("\n=============== IT DEPARTMENT ACTIVITIES ===============\n");

    while (fread(&dr, sizeof(dr), 1, fp)) {
        printf("\nRecord #%d\n", count++);
        printf("Name      : %s", dr.name);
        printf("Address   : %s", dr.address);
        printf("Date      : %s", dr.date);
        printf("Time      : %s", dr.time);
        printf("Duration  : %s", dr.duration);
        printf("--------------------------------------------------------\n");
    }

    fclose(fp);
}

// -----------------------------------------------------------
// EDIT RECORD
// -----------------------------------------------------------
void editRecord() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("\nNo records to edit!\n");
        return;
    }

    viewRecords();

    int recNo, count = 0;
    printf("\nEnter record number to edit: ");
    scanf("%d", &recNo);
    getchar();

    DiaryRecord dr;

    while (fread(&dr, sizeof(dr), 1, fp)) {
        count++;
        if (count == recNo) {
            printf("\nEditing Record #%d\n", recNo);

            printf("Enter Name of Activity: ");
            fgets(dr.name, 100, stdin);

            printf("Enter Address/Venue: ");
            fgets(dr.address, 200, stdin);

            printf("Enter Date (DD/MM/YYYY): ");
            fgets(dr.date, 20, stdin);

            printf("Enter Time (HH:MM): ");
            fgets(dr.time, 20, stdin);

            printf("Enter Duration: ");
            fgets(dr.duration, 50, stdin);

            fseek(fp, -sizeof(dr), SEEK_CUR);
            fwrite(&dr, sizeof(dr), 1, fp);

            printf("\nRecord Updated Successfully!\n");
            fclose(fp);
            return;
        }
    }

    printf("\nRecord not found!\n");
    fclose(fp);
}

// -----------------------------------------------------------
// DELETE RECORD
// -----------------------------------------------------------
void deleteRecord() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nNo records to delete!\n");
        return;
    }

    viewRecords();

    int recNo, count = 0;
    printf("\nEnter record number to delete: ");
    scanf("%d", &recNo);

    FILE *temp = fopen("temp.dat", "wb");
    DiaryRecord dr;

    while (fread(&dr, sizeof(dr), 1, fp)) {
        count++;
        if (count != recNo) {
            fwrite(&dr, sizeof(dr), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    printf("\nRecord Deleted Successfully!\n");
}

