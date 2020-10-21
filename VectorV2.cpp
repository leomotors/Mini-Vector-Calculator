/**
 * * Project 「Vector Calculator」
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 * * Version: 2.0-rc1
 * * Released on: 2020-10-21
 * ? Add Import and Export Function
 * ? Now able to select file names easily
 * ? SIMP(l)ed some code
 * TODO SIMP(lify) more code
 * TODO Make this resists against input from @Teproanyx
 * TODO Resistance against input error in part of String and Float
 */

#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define i 0
#define j 1
#define k 2

#define vectorSlotCount 100
float *vector[vectorSlotCount] = {NULL};

void vectorOperation();
void printMenu();
void inputVector();
void printvec(float *);
void saveVector(float *);
void setColor();
void cls();
void ShowAllVectors();

bool isVector(int);
void importVector();
void exportVector();
long long getlong(const char *);
int getInt(const char *);

//* Vector Operation
float vectorSize(float *);
float *scalarMult(float *, float);
float *addVector(float *, float *);
float dotProduct(float *, float *);
float *crossProduct(float *, float *);

int main()
{
    int choice;
    while (true)
    {
        cls();
        ShowAllVectors();
        printf("\nWhat do you want to do?\n");
        printf("[1] Input new vector!\n");
        printf("[2] Do operations!\n");
        printf("[3] Set terminal (command prompt)'s color\n");
        printf("[4] Lab: Import Vector\n");
        printf("[5] Lab: Export Vector\n");
        printf("[0] Exit\n");
        choice = getInt("Your Choice: ");
        switch (choice)
        {
        case 0:
            printf("Thanks for using this program! Press any to exit...");
            getchar();
            return 0;
        case 1:
            inputVector();
            break;
        case 2:
            vectorOperation();
            break;
        case 3:
            setColor();
            break;
        case 4:
            importVector();
            break;
        case 5:
            exportVector();
            break;
        default:
            printf("Invalid choice, please try again.\n");
            printf("Press any to continue...");
            getchar();
            break;
        }
    }
}

void vectorOperation()
{
    int choice, temp;
    int u, v;
    cls();
    printMenu();
    choice = getInt("Enter choice: ");
    if (choice == 0)
        return;
    if (choice < 0 || choice > 7)
    {
        printf("Invalid choice, try again!\nPress any to continue...");
        getchar();
        return;
    }
    ShowAllVectors();
    printf("\n");
    if (choice == 1 || choice == 2)
    {
        u = getInt("Select Vector: ");
        if (!isVector(u))
        {
            printf("Vector not available, Please any to continue...");
            getchar();
            return;
        }
    }
    else
    {
        u = getInt("Select First Vector: ");
        v = getInt("Select Second Vector: ");
        if (!(isVector(u) && isVector(v)))
        {
            printf("One or Both of vector not available, Please any to continue...");
            getchar();
            return;
        }
    }
    switch (choice)
    {
    case 1:
    {
        printf("Size of Vector is %.2f\n", vectorSize(vector[u]));
        break;
    }
    case 2:
    {
        temp = getInt("Enter scalar to multiply with: ");
        printvec(scalarMult(vector[u], temp));
        saveVector((scalarMult(vector[u], temp)));
        break;
    }
    case 3:
        printvec(addVector(vector[u], vector[v]));
        saveVector(addVector(vector[u], vector[v]));
        break;
    case 4:
        printf("Result is %.2f\n", dotProduct(vector[u], vector[v]));
        break;
    case 5:
        printvec(crossProduct(vector[u], vector[v]));
        saveVector(crossProduct(vector[u], vector[v]));
        break;
    case 6:
        printvec(scalarMult(vector[v], dotProduct(vector[u], vector[v]) / pow(vectorSize(vector[v]), 2)));
        saveVector(scalarMult(vector[v], dotProduct(vector[u], vector[v]) / pow(vectorSize(vector[v]), 2)));
        break;
    case 7:
        printf("Area is %.2f\n", vectorSize(crossProduct(vector[u], vector[v])));
        break;
    default:
        printf("Error 003: Default kicks in, function: vectorOperation\n");
    }
    printf("Operation done, Please any to continue...");
    getchar();
}

void printMenu()
{
    printf("==========================================\n");
    printf("Please select functions!\n");
    printf("\tOne Vector Operation\n");
    printf("[1] Find size of a Vector\n");
    printf("[2] Multiply Vector with scalar\n");
    printf("\tTwo Vectors Operation\n");
    printf("[3] Add 2 Vectors\n");
    printf("[4] Dot Product of 2 Vectors\n");
    printf("[5] Cross Product of 2 Vectors\n");
    printf("[6] Project a vector on another vector\n");
    printf("[7] Find area of parrallelogram from 2 vectors\n");
    printf("[0] Exit\n");
}

void ShowAllVectors()
{
    for (int m = 0; m < vectorSlotCount; m++)
    {
        if (vector[m] != NULL)
        {
            printf("Vector %d\n", m);
            printvec(vector[m]);
        }
    }
}

bool isVector(int u)
{
    return vector[u] != NULL;
}

void importVector()
{
    int slot = 0;
    float a1, a2, a3;
    char tmp[50], filename[100];
    FILE *inputFile;
    printf("Enter file name: ");
    scanf("%s", tmp);
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        printf("Error upon opening files, File may not exist.\n");
        printf("Press any to continue...");
        getchar();
        getchar();
        return;
    }
    while (true)
    {
        fscanf(inputFile, "%d %f %f %f", &slot, &a1, &a2, &a3);
        if (vector[slot] == NULL)
        {
            vector[slot] = new float[3];
            vector[slot][i] = a1;
            vector[slot][j] = a2;
            vector[slot][k] = a3;
        }
        else
            break;
    }
    fclose(inputFile);
}

void exportVector()
{
    char tmp[50], filename[100];
    char choice[10];
    FILE *outputFile;
    printf("Enter file name: ");
    scanf("%s", tmp);
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        do
        {
            printf("File already exists, Overwrite? [Y/N]: ");
            scanf("%s", choice);
            if (choice[0] == 'N')
            {
                return;
            }
        } while (choice[0] != 'Y');
    }
    outputFile = fopen(filename, "w");
    for (int c = 0; c < vectorSlotCount; c++)
    {
        if (vector[c] != NULL)
            fprintf(outputFile, "%d %f %f %f\n", c, vector[c][i], vector[c][j], vector[c][k]);
    }
    fclose(outputFile);
}

long getLong(const char *prompt) // * By @Teproanyx Modified by @Leomotors
{
    while (true)
    {
        printf("%s", prompt);
        char buffer[21];
        if (scanf("%20s", buffer) == EOF)
        {
            printf("Input error, please try again!\n");
            continue;
        }

        if (getchar() != '\n')
        {
            getchar();
            printf("Input error, please try again!\n");
            continue;
        }

        bool error = false;
        for (int c = 0, n = strlen(buffer); c < n; c++)
        {
            if (c == 0)
            {
                if (buffer[c] != '-' && !isdigit(buffer[c]))
                {
                    error = true;
                    break;
                }
            }
            else if (!isdigit(buffer[c]))
            {
                error = true;
                break;
            }
        }
        if (error)
        {
            printf("Input error, please try again!\n");
            continue;
        }

        errno = 0;
        long n = strtol(buffer, NULL, 10);
        if (errno == ERANGE)
        {
            printf("Value too large\n");
            printf("Input error, please try again!\n");
            continue;
        }

        return n;
    }
}

int getInt(const char *prompt) // * By @Teproanyx Modified by @Leomotors
{
    while (true)
    {
        long n = getLong(prompt);
        if (n > INT_MAX || n < INT_MIN)
        {
            printf("Input error, please try again!\n");
            continue;
        }
        return (int)n;
    }
}

void inputVector()
{
    int slot;
    char confirm[10];
    slot = getInt("Which slot you want? : ");
    if (slot >= 0 && slot < vectorSlotCount)
    {
        if (vector[slot] != NULL)
        {
            do
            {
                printf("Vector already exists, Overwrite? [Y/N]: ");
                scanf("%s", confirm);
                if (confirm[0] == 'N')
                    return;
            } while (confirm[0] != 'Y');
        }
        float *u = new float[3];
        printf("Enter Vector (i,j,k): ");
        scanf("%f %f %f", &u[i], &u[j], &u[k]);
        vector[slot] = u;
    }
    else
    {
        printf("Invalid index!\nPress any to continue!");
        getchar();
    }
}

void printvec(float *u)
{
    printf("Result Vector: ( %.2f , %.2f , %.2f )\n", u[i], u[j], u[k]);
}

void saveVector(float *u)
{
    int w;
    char choice[10];
    do
    {
        printf("Do you want to save vector? [Y/N]: ");
        scanf("%s", choice);
        if (choice[0] == 'N')
            return;
    } while (choice[0] != 'Y');
    w = getInt("Where you want to save vector? : ");
    if (vector[w] != NULL)
    {
        do
        {
            printf("This slot already has vector in it. Overwrite? [Y/N]: ");
            scanf("%s", choice);
            if (choice[0] == 'N')
            {
                saveVector(u);
                return;
            }
        } while (choice[0] != 'Y');
    }
    vector[w] = u;
}

void setColor()
{
#if defined(_WIN32)
    char col[10], syn[10];
    printf(
        "\nColor attributes are specified by TWO hex digits -- the first "
        "corresponds to the background; the second the foreground."
        "\nEach digit can be any of the following values:\n\n"
        "\t0 = Black       8 = Gray\n"
        "\t1 = Blue        9 = Light Blue\n"
        "\t2 = Green       A = Light Green\n"
        "\t3 = Aqua        B = Light Aqua\n"
        "\t4 = Red         C = Light Red\n"
        "\t5 = Purple      D = Light Purple\n"
        "\t6 = Yellow      E = Light Yellow\n"
        "\t7 = White       F = Bright White\n");
    printf("Enter color: ");
    scanf("%s", col);
    sprintf(syn, "color %s", col);
    system(syn);
#else
    printf("This is only supported on Windows!\n");
    printf("Press any to continue...");
    getchar();
    getchar();
#endif
    cls();
}

void cls() // * By @Teproanyx
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}

float vectorSize(float *u)
{
    float result = u[i] * u[i] + u[j] * u[j] + u[k] * u[k];
    result = sqrt(result);
    return result;
}

float *scalarMult(float *u, float num)
{
    float *w = new float[3];
    w[i] = num * u[i];
    w[j] = num * u[j];
    w[k] = num * u[k];
    return w;
}

float *addVector(float *u, float *v)
{
    float *w = new float[3];
    w[i] = u[i] + v[i];
    w[j] = u[j] + v[j];
    w[k] = u[k] + v[k];
    return w;
}

float dotProduct(float *u, float *v)
{
    float result;
    result = u[i] * v[i] + u[j] * v[j] + u[k] * v[k];
    return result;
}

float *crossProduct(float *u, float *v)
{
    float *w = new float[3];
    w[i] = u[j] * v[k] - u[k] * v[j];
    w[j] = u[k] * v[i] - v[k] * u[i];
    w[k] = u[i] * v[j] - v[i] * u[j];
    return w;
}
