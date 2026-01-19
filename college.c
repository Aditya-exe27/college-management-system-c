#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StudentManagement();
void CourseManagement();
void FeesManagement();
void ViewStudent();
void Find();
void byID();
void byname();
void bycourse();
void DeleteStudent();
void UpdateStudent();

struct student{
    int id;
    char name[50];
    int cID;
};

struct course{
    int cID;
    char cname[50];
    float cfees;
};

struct fees{
    float pfees;
    int sID;
};

int main()
{
    int value;
    while (1)
    {
        printf("\n---------College Management System-----------\n");
        printf("1. Add Student\n");
        printf("2. Find Student\n");
        printf("3. Add Course\n");
        printf("4. Fees Details\n");
        printf("5. View Student Details\n");
        printf("6. Delete Student\n");
        printf("7. Update Student\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &value);

        switch (value)
        {
        case 1:
            StudentManagement();
            break;
        case 2:
            Find();
            break;
        case 3:
            CourseManagement();
            break;
        case 4:
            FeesManagement();
            break;
        case 5:
            ViewStudent();
            break;
        case 6:
            DeleteStudent();
            break;
        case 7:
            UpdateStudent();
            break;
        case 8:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

void StudentManagement()
{
    struct student s;
    FILE *f = fopen("student.dat", "ab");
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Course ID: ");
    scanf("%d", &s.cID);
    fwrite(&s, sizeof(s), 1, f);
    fclose(f);
    printf("Student added successfully\n");
}

void CourseManagement()
{
    struct course c;
    FILE *f = fopen("course.dat", "ab");
    printf("Enter Course ID: ");
    scanf("%d", &c.cID);
    printf("Enter Course Name: ");
    scanf("%s", c.cname);
    printf("Enter Course Fees: ");
    scanf("%f", &c.cfees);
    fwrite(&c, sizeof(c), 1, f);
    fclose(f);
    printf("Course added successfully\n");
}

void FeesManagement()
{
    struct fees fe;
    FILE *f = fopen("fees.dat", "ab");
    printf("Enter Student ID: ");
    scanf("%d", &fe.sID);
    printf("Enter Fees Paid: ");
    scanf("%f", &fe.pfees);
    fwrite(&fe, sizeof(fe), 1, f);
    fclose(f);
    printf("Fees updated successfully\n");
}

void ViewStudent()
{
    struct student s;
    struct course c;
    struct fees fe;
    FILE *fs = fopen("student.dat", "rb");
    FILE *fc = fopen("course.dat", "rb");
    FILE *ff = fopen("fees.dat", "rb");
    int id, found = 0;
    float totalFees = 0, paidFees = 0;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.id == id)
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Student not found\n");
        fclose(fs);
        fclose(fc);
        fclose(ff);
        return;
    }
    while (fread(&c, sizeof(c), 1, fc))
    {
        if (c.cID == s.cID){
            totalFees = c.cfees;
            break;
        }
    }
    while (fread(&fe, sizeof(fe), 1, ff))
    {
        if (fe.sID == s.id)
            paidFees += fe.pfees;
    }
    printf("\n----- Student Details -----\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Course ID: %d\n", s.cID);
    printf("Total Fees: %.2f\n", totalFees);
    printf("Fees Paid: %.2f\n", paidFees);
    printf("Pending Fees: %.2f\n", totalFees - paidFees);
    fclose(fs);
    fclose(fc);
    fclose(ff);
}
void Find()
{
    int ch;
    printf("\n1. Find by ID\n");
    printf("2. Find by Name\n");
    printf("3. Find by Course\n");
    printf("Enter choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        byID();
        break;
    case 2:
        byname();
        break;
    case 3:
        bycourse();
        break;
    default:
        printf("Invalid choice\n");
    }
}
void byID()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    int id, found = 0;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.id == id)
        {
            found = 1;
            printf("Name: %s\n", s.name);
            printf("Course ID: %d\n", s.cID);
            break;
        }
    }
    if (!found)
        printf("Student not found\n");
    fclose(fs);
}
void byname()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    char name[50];
    int found = 0;
    printf("Enter name: ");
    scanf("%s", name);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (strcmp(s.name, name) == 0)
        {
            found = 1;
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Course ID: %d\n", s.cID);
        }
    }
    if (!found)
        printf("Student not found\n");
    fclose(fs);
}
void bycourse()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    int cid, found = 0;
    printf("Enter Course ID: ");
    scanf("%d", &cid);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.cID == cid)
        {
            found = 1;
            printf("ID: %d  Name: %s\n", s.id, s.name);
        }
    }
    if (!found)
        printf("No students found for this course\n");
    fclose(fs);
}
void DeleteStudent()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    FILE *ft = fopen("temp.dat", "wb");
    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.id == id)
            found = 1;
        else
            fwrite(&s, sizeof(s), 1, ft);
    }
    fclose(fs);
    fclose(ft);
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (found)
        printf("Student deleted successfully\n");
    else
        printf("Student not found\n");
}
void UpdateStudent()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    FILE *ft = fopen("temp.dat", "wb");
    int id, choice, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.id == id)
        {
            found = 1;
            printf("1. Update Name\n");
            printf("2. Update Course ID\n");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter new name: ");
                scanf("%s", s.name);
            }
            else if (choice == 2)
            {
                printf("Enter new Course ID: ");
                scanf("%d", &s.cID);
            }
        }
        fwrite(&s, sizeof(s), 1, ft);
    }
    fclose(fs);
    fclose(ft);
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (found)
        printf("Student updated successfully\n");
    else
        printf("Student not found\n");
}