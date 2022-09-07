#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
struct qna //Question and Answers Structure
{
    char qn[500], A[500], B[500], C[500], D[500], Ans[1];
};
struct userdet //User Credentials Structure
{
    char uname[50], upas[50];
};
struct userperf //User Performance Structure
{
    char uname[50];
    int score;
};
int addqns() //Function to add questions to questions.bin
{
    system("cls");
    /*Opens a file stream*/
    FILE *fp;
    /*Opening file in appending mode*/
    fp = fopen("questions.bin", "ab");
    /*Implementing a flag*/
    char userin;
    /*Dynamically declaring a question-structure 'qn' to accept user input*/
    struct qna qn;
    do
    {

        system("cls");
        /*Accepting user input for the Question and Answers*/
        printf("Enter the question\n");
        fgets(qn.qn, 499, stdin);
        printf("\nEnter Option A\n");
        fgets(qn.A, 499, stdin);
        printf("\nEnter Option B\n");
        fgets(qn.B, 499, stdin);
        printf("\nEnter Option C\n");
        fgets(qn.C, 499, stdin);
        printf("\nEnter Option D\n");
        fgets(qn.D, 499, stdin);
        printf("\nEnter correct option(A/B/C/D)\n");
        fgets(qn.Ans, 9, stdin);
        /*Writing the procured data into the file*/
        fwrite(&qn, sizeof(struct qna), 1, fp);
        /*Giving user choice to add more questions*/
        printf("\nWould you like to add another question? (Y/N)\n");
        scanf("%c", &userin);
        /*Flushing output buffer of stream so that fgets() in the next iteration does not consume a newline*/
        fflush(stdin);
    } while (userin == 'Y' || userin == 'y');
    /*Closing file*/
    fclose(fp);
    return 1;
}

void randomqn(struct qna qarr[], int n) //function to randomize questions
{
    struct qna *a, *b, temp;
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {

        int j = rand() % (i + 1);
        a = &qarr[i];
        b = &qarr[j];
        temp = *a;
        *a = *b;
        *b = temp;
    }
}
void takequiz(char username[50]) //Take quiz function

{
    system("cls");
    int n, y, z, attempt = 0, qns = 0, att = 0;
    struct qna qarr[50];
    FILE *fin;
    int i = 0;
    fin = fopen("questions.bin", "rb");
    if (fin == NULL) //Checking if file exists
        printf("File does not exist and cannot be opened");

    else
    {
        while (fread(&qarr[i], sizeof(struct qna), 1, fin))
        {
            ++i;
        }
    }
    n = i;
    randomqn(qarr, n);
    while (attempt < 2)
    {
        if (attempt == 1)
        {
            y = n / 2;
            z = n;
        }
        else
        {
            y = 0;
            z = n / 2;
        }
        qns = 0;
        att = 0;
        system("cls");
        int flag = 0; //var for storing number of correct ans
        int galf = 0; //var for storing number of incorrect ans for negative marking
        int unatt = 0;
        int glaf = 0;
        char userinp = 'N';
        int userin;
        int ans;
        for (int i = y; i < z; i++) //n is the total number of questions
        {
            ++qns;
            do
            {
                printf("\nEnter a valid answer\n");
                userinp = 'X';
                printf("Q%d)", i - y + 1);
                printf("%s", qarr[i].qn); //where q is the question inside array of question structs
                printf("A)%s\nB)%s\nC)%s\nD)%s\n", qarr[i].A, qarr[i].B, qarr[i].C, qarr[i].D);
                printf("Enter your answer: ");
                scanf(" %c", &userinp);
                tolower(userinp);
                if (userinp == qarr[i].Ans[0] || userinp == tolower(qarr[i].Ans[0]))
                {
                    flag++;
                }
                else if ((userinp) == 'N' || userinp == 'n')
                    unatt++;
                else
                {
                    printf("%d", glaf);
                    glaf++;
                }
                system("cls");
            } while (userinp != 'a' && userinp != 'b' && userinp != 'c' && userinp != 'd' && userinp != 'n');
        }
        att = qns - unatt;
        printf("Quiz results:\n");
        printf("Total questions:%d\nQuestions attempted:%d\nQuestions unattempted:%d\nQuestions correct:%d\nQuestions incorrect:%d\n", qns, att, unatt, flag, glaf); //Displaying after quiz statistics
        getchar();
        perfrec(username, flag);
        char userinp2;
        printf("\nWould you like to reattempt ?(Y/N) ");
        scanf(" %c", &userinp2);
        if (userinp2 == 'Y' || userinp2 == 'y')
        {
            attempt = attempt + 1;
        }
        else
        {
            exit(1);
        }
    }
    if (attempt == 2)
        printf("Too bad, no more reattempts for you :) ! Press any key to exit..");
    getch();
    return 1;
}
int perfrec(char username[50], int score) //For storing student performance results
{
    FILE *infile;
    infile = fopen("performance.bin", "ab");
    struct userperf input;
    strcpy(input.uname, username);
    input.score = score;
    fwrite(&input, sizeof(struct userperf), 1, infile);
    fclose(infile);
}
void trimleadingandTrailing(char *s) //For clearing whitespaces from inputs
{
    int i, j;

    for (i = 0; s[i] == ' ' || s[i] == '\t'; i++)
        ;

    for (j = 0; s[i]; i++)
    {
        s[j++] = s[i];
    }
    s[j] = '\0';
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != ' ' && s[i] != '\t')
            j = i;
    }
    s[j + 1] = '\0';
}
int registration() //User registration function
{
    system("cls");
    struct userdet user1, userc;
    printf("Enter username (no space)\t");
    fgets(user1.uname, 49, stdin);
    trimleadingandTrailing(user1.uname);
    printf("\nEnter password (no space)\t");
    fgets(user1.upas, 49, stdin);
    trimleadingandTrailing(user1.upas);
    FILE *f;
    FILE *fc;
    fc = fopen("registration.bin", "rb");

    while (fread(&userc, sizeof(struct userdet), 1, fc))
    {
        if (strcmp(user1.uname, userc.uname) == 0)
        {
            printf("This username already exists.");
            printf("Would you like to try again? (Y/N) ");
            char op;
            scanf("%c", &op);
            fflush(stdin);
            if (op == 'Y' || op == 'y')
            {
                fclose(fc);
                registration();
            }
            else
            {   
                exit(1);
                return 1;
            }
        }
    }
    fclose(fc);
    f = fopen("registration.bin", "ab");

    fwrite(&user1, sizeof(struct userdet), 1, f);
    fflush(stdin);
    fclose(f);
    printf("Enter any key to exit..");
    getch();
    exit(1);
    return 1;
}
int login() //User Login function
{
    system("cls");
    int flagger = 0;
    struct userdet user1, userc;
    printf("Enter username\t\t");
    fgets(user1.uname, 49, stdin);
    FILE *f;
    char c = 'y';
    f = fopen("registration.bin", "rb");
    trimleadingandTrailing(user1.uname);
    while (fread(&userc, sizeof(struct userdet), 1, f))
    {
        if (strcmp(user1.uname, userc.uname) == 0 && (c == 'y' || c == 'Y'))
        {
            flagger = 1;
            printf("\nEnter password now\t");
            fgets(user1.upas, 49, stdin);
            trimleadingandTrailing(user1.upas);
            if ((strcmp(user1.upas, userc.upas) == 0))
            {
                usermenu(user1.uname);
                exit(1);
            }
            else
            {
                printf("\n Looks like you just entered the wrong password !\n");
                printf("\n Enter Y to try again\t");
                scanf("%c", &c);
                if (c != 'Y' && c != 'y')
                {
                    exit(1);
                    return 1;
                }
                else
                {
                    printf("\nEnter password now \t");
                    char op;
                    scanf("%c",&op);
                    fgets(user1.upas, 49, stdin);
                    trimleadingandTrailing(user1.upas);
                    if ((strcmp(user1.upas, userc.upas) == 0))
                    {
                        usermenu(user1.uname);
                        exit(1);
                    }
                }
            }
        }
    }
    if (flagger == 0)
    {
        printf("Username does not exist.\n Would you like to register ? (Y/N)\n");
        char opt[3];
        fgets(opt, sizeof(opt), stdin);
        if (opt[0] == 'Y' || opt[0] == 'y')
        {
            fclose(f);
            registration();
            exit(1);
        }
        else
        {
            fclose(f);
            exit(1);
            return 1;
        }
    }
    return 1;
}
int removeqns() //Question Removal function
{
    struct qna qarr[40];
    system("cls");
    printf("\nQuestions will be displayed one by one. You can decide whether to keep them or remove them\n");
    FILE *infile;
    FILE *infilev2;
    struct qna input;
    char flagger;
    infile = fopen("questions.bin", "rb");
    infilev2 = fopen("temp.bin", "wb");
    if (infile == NULL)
    {
        printf("You have not added any questions ! Exiting..");
        fclose(infile);
        fclose(infilev2);
        exit(1);
    }
    int i = 0;
    while (fread(&qarr[i], sizeof(struct qna), 1, infile))
    {
        ++i;
    }
    int n = i;
    for (i = 0; i < n; i++)
    {
        printf("%s\n", qarr[i].qn);
        printf("\n Enter y to delete and any other character to keep question \n");
        scanf(" %c", &flagger);
        if (flagger != 'Y' && flagger != 'y')
        {
            fwrite(&qarr[i], sizeof(struct qna), 1, infilev2);
            system("cls");
        }
    }
    fclose(infile);
    fclose(infilev2);
    int value;
    remove("questions.bin");                     //Removing the old file
    value = rename("temp.bin", "questions.bin"); //Renaming temp while with needed questions to questions.bin
    printf("The process is completed. Press any key to continue..");
    getch();
    return 1;
}
int adminlogin() //admin login function
{
    system("cls");
    char c;
    struct userdet adminlogger, userc;
    strcpy(adminlogger.uname, "admin\n"); //\n is added because username has a newline at the end of it already in the file
    printf("Enter password\t");
    fgets(adminlogger.upas, 49, stdin);
    trimleadingandTrailing(adminlogger.upas); //trimleadingandTrailing(); only clears string of whitespaces
    FILE *f;
    f = fopen("admin.bin", "rb");
    fread(&userc, sizeof(struct userdet), 1, f);
    if (strcmp(adminlogger.upas, userc.upas) == 0)
    {
        fclose(f);
        adminfns();
    }
    else
    {
        printf("\nAdmin password incorrect !! Press any key to continue..\n");
        scanf("%c", &c);
        fflush(stdin);
        fclose(f);
        return 1;
    }
    return 1;
}
int usermenu(char username[50]) //Student user menu function
{
    system("cls");
    int userin;
    printf("\nHEY THERE, %s\n", username);
    printf("\n1.Take quiz\n");
    printf("\n2.View past performance\n");
    scanf("%d", &userin);
    switch (userin)
    {
    case 1:
        takequiz(username);
        exit(1);
        break;
    case 2:
        pastper(username);
        exit(1);
        break;
    default:
        return 1;
    }
}
int adminfns() //Administrative functions
{
    char admin[50];
    int userin;
    strcpy(admin, "admin"); //Mock Test also stores admin marks inside the pastperformance file
    printf("\nWelcome to admin section\n");
    printf("\n1.Take mock quiz\n");
    printf("\n2.Add questions\n");
    printf("\n3.Remove Questions\n");
    printf("\n4.Edit Questions\n");
    printf("\nEnter any other number to exit\n");
    scanf("%d", &userin);
    fflush(stdin);
    switch (userin)
    {
    case 1:
        takequiz(admin);
        exit(1);
        break;
    case 2:
        userin = addqns();
        exit(1);
        break;
    case 3:
        userin = removeqns();
        exit(1);
        break;
    case 4:
        userin = editqns();
        exit(1);
        break;
    default:
        exit(1);
    }
}
int editqns() //Edit questions function
{
    char userin;
    system("cls");
    printf("\nQuestions will be displayed one by one\n");
    printf("\nEnter Y to edit, N to not edit and any other character to skip to main menu\n");
    printf("\nEnter any key to continue..\n");
    getch();
    struct qna qarr[40];
    system("cls");
    printf("\nQuestions will be displayed one by one. You can decide whether to keep them or remove them\n");
    FILE *infile;
    FILE *infilev2;
    struct qna input;
    char flagger;
    infile = fopen("questions.bin", "rb");
    infilev2 = fopen("temp.bin", "wb");
    if (infile == NULL)
    {
        printf("You have not added any questions ! Exiting..");
        fclose(infile);
        fclose(infilev2);
        exit(1);
    }
    int i = 0;
    while (fread(&qarr[i], sizeof(struct qna), 1, infile))
    {
        ++i;
    }
    int n = i;
    for (i = 0; i < n; i++)
    {
        printf("%s\n", qarr[i].qn);
        printf("\n Enter Y to edit and N to not edit and any other character to exit\n");
        scanf(" %c", &flagger);
        if (flagger == 'N' || flagger == 'n')
        {
            fwrite(&qarr[i], sizeof(struct qna), 1, infilev2);
            system("cls");
        }
        else if (flagger == 'y' || flagger == 'Y')
        {
            fflush(stdin);
            /*Accepting user input for the Question and Answers*/
            printf("Enter the question\n");
            fgets(qarr[i].qn, 499, stdin);
            printf("\nEnter Option A\n");
            fgets(qarr[i].A, 499, stdin);
            printf("\nEnter Option B\n");
            fgets(qarr[i].B, 499, stdin);
            printf("\nEnter Option C\n");
            fgets(qarr[i].C, 499, stdin);
            printf("\nEnter Option D\n");
            fgets(qarr[i].D, 499, stdin);
            printf("\nEnter correct option(A/B/C/D)\n");
            fgets(qarr[i].Ans, 9, stdin);
            /*Writing the procured data into the file*/
            fwrite(&qarr[i], sizeof(struct qna), 1, infilev2);
            system("cls");
            /*Flushing output buffer of stream so that fgets() in the next iteration does not consume a newline*/
            fflush(stdin);
        }
        else
        {
            for (; i < n; i++)
            {
                fwrite(&qarr[i], sizeof(struct qna), 1, infilev2);
                system("cls");
            }
            fclose(infile);
            fclose(infilev2);
            int value;
            remove("questions.bin");                     //Removing the old file
            value = rename("temp.bin", "questions.bin"); //Renaming temp while with needed questions to questions.bin
            printf("The process is completed. Press any key to continue..");
            getch();
            return 1;
        }
    }
    fclose(infile);
    fclose(infilev2);
    int value;
    remove("questions.bin");                     //Removing the old file
    value = rename("temp.bin", "questions.bin"); //Renaming temp while with needed questions to questions.bin
    printf("The process is completed. Press any key to continue..");
    getch();
    return 1;
}
int pastper(char username[50]) //Past performance checker
{
    FILE *infile;
    infile = fopen("performance.bin", "rb");
    struct userperf input;
    int flagger = 0;
    printf("\nYour past performances have been : \n");
    while (fread(&input, sizeof(struct userperf), 1, infile))
    {
        if (strcmp(username, input.uname) == 0)
        {
            printf("%d,", input.score);
            flagger++;
        }
    }
    if (flagger == 0)
    {
        system("cls");
        printf("\nNo records found. Press any key to continue..");
        getch();
        fclose(infile);
        return 1;
    }
    else
    {
        fclose(infile);
        printf("\nPress any key to continue.. ");
        getch();
        return 1;
    }
}
int main() //Main Function
{
    system("cls");
    int userin;
    printf("\nWelcome to our Quiz App !!\n");
    printf("\n1.Admin Login\n");
    printf("\n2.Student login\n");
    printf("\n3.New User Registration\n");
    printf("\n4.Exit\n");
    printf("\nEnter any of the above options\n");
    scanf("%d", &userin);
    fflush(stdin);
    for (int i = 0;;)

    {
        switch (userin)
        {
        case 1:
            userin = adminlogin();
            exit(1);
            break;
        case 2:
            userin = login();
            exit(1);
            break;
        case 3:
            userin = registration();
            exit(1);
            break;
        case 4:
            exit(1);
            break;
        }
    }
}