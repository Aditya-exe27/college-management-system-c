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

int main()
{
    int value;
    while (1)
    {
        printf("---------Collage Management System-----------\n");
        printf("Enter your choice\n");
        printf("1.Add Student\n");
        printf("2.Find Student by:\n");
        printf("3.Add Course\n");
        printf("4.Fees Details\n");
        printf("5.View Student Details\n");
        printf("6.Exit the program\n");
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
            printf("Exiting program...");
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
struct student
{
    int id;
    char name[50];
    int cID;
};
struct course
{
    int cID;
    char cname[50];
    float cfees;
};
struct fees
{
    float pfees;
    int sID;
};

void StudentManagement()
{
    struct student s;
    FILE *f = fopen("student.dat", "ab");
    printf("Enter ID : ");
    scanf("%d", &s.id);
    printf("Enter name : ");
    scanf("%s", s.name);
    printf("Enter couse ID : ");
    scanf("%d", &s.cID);
    fwrite(&s, sizeof(s), 1, f);
    fclose(f);
    printf("========= Student added successfully ========\n");
}
void CourseManagement()
{
    struct course c;
    FILE *f = fopen("course.dat", "ab");
    printf("Enter course ID: ");
    scanf("%d", &c.cID);
    printf("Enter course name: ");
    scanf("%s", c.cname);
    printf("Enter course fees: ");
    scanf("%f", &c.cfees);
    fwrite(&c, sizeof(c), 1, f);
    fclose(f);
    printf("=========Course added successfully==========\n");
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
    printf("========Fees updated successfully==========\n");
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
    float totalFees = 0, paidfees = 0;
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
    if (found == 0)
    {
        printf("No Student Found\n");
        fclose(fs), fclose(fc), fclose(ff);
        return;
    }
    while (fread(&c, sizeof(c), 1, fc))
    {
        if (c.cID == s.cID)
        {
            totalFees = c.cfees;
            break;
        }
    }
    while (fread(&fe, sizeof(fe), 1, ff))
    {
        if (fe.sID == s.id)
        {
            paidfees += fe.pfees;
        }
    }
    printf("\n===== STUDENT FULL DETAILS =====\n");
    printf("Student ID   : %d\n", s.id);
    printf("Name         : %s\n", s.name);
    printf("Course ID    : %d\n", c.cID);
    printf("Course Name  : %s\n", c.cname);
    printf("Total Fees   : %.2f\n", totalFees);
    printf("Fees Paid    : %.2f\n", paidfees);
    printf("Pending Fees : %.2f\n", totalFees - paidfees);
    printf("================================\n");
    fclose(fs), fclose(fc), fclose(ff);
}
void Find()
{
    int val;
    printf("1.ID\n");
    printf("2.First name\n");
    printf("3.Course\n");
    scanf("%d", &val);
    switch (val)
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
        break;
    }
}
void byID()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    int id, found = 0;
    printf("Enter Student ID:  ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.id == id)
        {
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("No Student Found\n");
        fclose(fs);
        return;
    }
    else
    {
        printf("Name         : %s\n", s.name);
        printf("Course ID    : %d\n", s.cID);
    }
    fclose(fs);
}
void byname()
{
    struct student s;
    int found = 0;
    FILE *fs = fopen("student.dat", "rb");
    char FirstName[50];
    printf("Enter First name:   ");
    scanf("%s", FirstName);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (strcmp(s.name, FirstName) == 0)
        {
            found = 1;
            printf("Student ID   : %d\n", s.id);
            printf("Name         : %s\n", s.name);
            printf("Course ID    : %d\n", s.cID);
        }
    }
    if (found == 0)
    {
        printf("Student not found\n");
    }
    fclose(fs);
}
void bycourse()
{
    struct student s;
    FILE *fs = fopen("student.dat", "rb");
    int id;
    int found = 0;
    printf("Enter Course ID:   \n");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fs))
    {
        if (s.cID == id)
        {
            found = 1;
            printf("Student ID   : %d\n", s.id);
            printf("Name         : %s\n", s.name);
            printf("Course ID    : %d\n", s.cID);
        }
    }
    if (found == 0)
    {
        printf("Invalid Course ID\n");
    }
    fclose(fs);
}