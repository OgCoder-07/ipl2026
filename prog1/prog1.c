#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[30];
    float marks;
} Student;

/* Function Prototypes */
void storeRecords(char *filename, int n);
void displayMthRecord(char *filename, int m);
void deleteRecord(char *filename, int delPos);
void displayAll(char *filename);

int main() {
    int n, m, delPos;

    printf("Enter number of records: ");
    scanf("%d", &n);

    /* Store records */
    storeRecords("student.dat", n);

    printf("\nAll Records:\n");
    displayAll("student.dat");

    /* Get mth record */
    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    displayMthRecord("student.dat", m);

    /* Delete record */
    printf("\nEnter record number to delete: ");
    scanf("%d", &delPos);

    deleteRecord("student.dat", delPos);

    printf("\nRecords after deletion:\n");
    displayAll("student.dat");

    return 0;
}

/* Function to store records in binary file */
void storeRecords(char *filename, int n) {
    FILE *fp;
    Student s;

    fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter ID:\n");
        scanf("%d", &s.id);

        printf("Enter Name:\n");
        scanf("%s", s.name);

        printf("Enter Marks:\n");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(Student), 1, fp);
    }

    fclose(fp);
}

/* Function to display mth record using fseek */
void displayMthRecord(char *filename, int m) {
    FILE *fp;
    Student s;

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    /* Move pointer to mth record */
    fseek(fp, (m - 1) * sizeof(Student), SEEK_SET);

    if (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("\nRecord %d Details:\n", m);
        printf("ID    : %d\n", s.id);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
    } else {
        printf("Record not found!\n");
    }

    fclose(fp);
}

/* Function to delete a record */
void deleteRecord(char *filename, int delPos) {
    FILE *fp, *temp;
    Student s;
    int count = 1;

    fp = fopen(filename, "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    /* Copy all records except deleted one */
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (count != delPos) {
            fwrite(&s, sizeof(Student), 1, temp);
        }
        count++;
    }

    fclose(fp);
    fclose(temp);

    /* Replace old file with new file */
    remove(filename);
    rename("temp.dat", filename);

    printf("Record deleted successfully.\n");
}

/* Function to display all records */
void displayAll(char *filename) {
    FILE *fp;
    Student s;
    int count = 1;

    fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("\nRecord %d\n", count);
        printf("ID    : %d\n", s.id);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);

        count++;
    }

    fclose(fp);
}
