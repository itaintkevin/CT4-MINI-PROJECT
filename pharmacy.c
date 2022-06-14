#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void insert();
void search();
void update();

struct medicines
{
    int mfccode;
    int mfcdate;
    int expdate;
    char mfcname[20];
    char medname[20];
    float price;
};
struct medicines medicine;

void main()
{
    int choice;
    while (choice != 4)
    {
        printf("\t**********************************\n");
        printf("\t'WELCOME TO SRM PHARMACY DATABASE'\n");
        printf("\t**********************************\n\n\n");
        printf("\t****What would you like to do?****\n\n");
        printf("\t~1: Insert Medicine record~\n");
        printf("\t~2: Search Medicine record~\n");
        printf("\t~3: Update Medicine record~\n");
        printf("\t~4: Exit~\n\n");
        printf("\tEnter Your Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // system("cls");
            insert();
            break;
        case 2:
            // system("cls");
            search();
            break;
        case 3:
            // system("cls");
            update();
            break;
        case 4:
            exit(1);
            break;

        default:
            printf("\n\t\t!!! You Entered The Wrong Choice !!!\n\n");
        }
        getchar();
    }
}

void insert()
{
    FILE *fp;
    fp = fopen("pharmacy.txt", "a+");
    printf("\n\n\t~~~ENTER NEW MEDICINE DATA~~~");
    printf("\n\n\tEnter Manufacturing Code : ");
    scanf("%d", &medicine.mfccode);

    printf("\n\tEnter Manufacturing Date : ");
    scanf("%d", &medicine.mfcdate);

    printf("\n\tEnter Expiration Date : ");
    scanf("%d", &medicine.expdate);
    fflush(stdin);

    printf("\n\tEnter Manufacture Name : ");
    gets(medicine.mfcname);

    printf("\n\tEnter Medicine Name : ");
    gets(medicine.medname);

    printf("\n\tEnter Price : ");
    scanf("%f", &medicine.price);

    fwrite(&medicine, sizeof(medicine), 1, fp);
    {
        printf("\n\n\tMedicine Details Recorded Sucessfully !!!\n");
    }
    fclose(fp);
    fflush(stdin);
    printf("\n\t\tRecord Updated !!!\n\n");
}

void search()
{
    int code, flag = 0;

    FILE *fp;
    fp = fopen("pharmacy.txt", "r");

    if (fp == NULL)
    {
        printf("\n\t\tError : File Does Not Exist !!! ");
        return;
    }

    printf("\n\n\tEnter Manufacturing Code To Search : ");
    scanf("%d", &code);
    while (fread(&medicine, sizeof(medicine), 1, fp) > 0 && flag == 0)
    {
        if (medicine.mfccode == code)
        {
            flag = 1;
            printf("\n\tSearch Sucessfull And Medicine Details Is as follows");
            printf("\n\n\tMFC Code\tMFC Date\tEXP Date\tMFC Name\tMedicine Name\t\tPrice\n");
            printf("\t%d\t\t%d\t\t%d\t\t%s\t\t%s\t\t\t%.4f\n\n\n", medicine.mfccode, medicine.mfcdate, medicine.expdate, medicine.mfcname, medicine.medname, medicine.price);
        }
    }
    if (flag == 0)
    {
        printf("\n\n\t\t!!! No Record Found !!!\n\n");
    }
    fclose(fp);
}
void update()
{
    int code, flag = 0;

    FILE *fp;
    fp = fopen("pharmacy.txt", "r+");
    if (fp == NULL)
    {
        printf("\n\t\tError : File Does Not Exist");
        return;
    }

    printf("\n\n\tEnter Manufacturing Code of the Medicine Details To Update : ");
    scanf("%d", &code);

    printf("\n\n\t\t *** Previously Stored Medicine Details for the Manufacturing Code ***\n");
    while (fread(&medicine, sizeof(medicine), 1, fp) > 0 && flag == 0)
    {
        if (medicine.mfccode == code)
        {
            flag = 1;
            printf("\n\n\tMFC Code\tMFC Date\tEXP Date\tMFC Name\tMedicine Name\t\tPrice\n");
            printf("\t%d\t\t%d\t\t%d\t\t%s\t\t%s\t\t\t%.4f\n\n", medicine.mfccode, medicine.mfcdate, medicine.expdate, medicine.mfcname, medicine.medname, medicine.price);

            printf("\n\t\t*** Update the Medicine Details ***\n\n");
            printf("\n\tEnter Manufacturing Code : ");
            scanf("%d", &medicine.mfccode);

            printf("\n\tEnter Manufacturing Date : ");
            scanf("%d", &medicine.mfcdate);

            printf("\n\tEnter Expiration Date : ");
            scanf("%d", &medicine.expdate);
            fflush(stdin);

            printf("\n\tEnter Manufacture Name : ");
            gets(medicine.mfcname);

            printf("\n\tEnter Medicine Name : ");
            gets(medicine.medname);

            printf("\n\tEnter Price : ");
            scanf("%.4f", &medicine.price);

            fseek(fp, -(long)sizeof(medicine), 1);

            fwrite(&medicine, sizeof(medicine), 1, fp);
            printf("\n\n\t\tDetails Updated\n\n\n");
        }
    }
    if (flag == 0)
    {
        printf("\n\t\tError : Something Went Wrong !!!\n\n");
    }
    fclose(fp);
    fflush(stdin);
}
