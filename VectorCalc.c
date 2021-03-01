/**
 * * Project 「Vector Calculator」
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "SafeInput.h"

#define i 0
#define j 1
#define k 2

int numberPrecision = 2;

#define VECTOR_ARRAY_SIZE 100
double *vector[VECTOR_ARRAY_SIZE] = {NULL};

// * Menu's Stuff
void printMainMenu(void);
bool programCore(void);
void printOperationMenu(void);
void vectorOperation(void);
void settingsMenu(void);
void fileMenu(void);
void setColor(void); // ! Only supported on Windows
void cls(void);
bool getConfirmation(const char *);

// * Vector management
void inputVector(void);
char *printvec(double *);
void ShowAllVectors(void);
void saveVectorToSlot(double *);
bool isVector(int);
bool deleteAllVectors(void);

// * Import and Export
void importVector(void);
void exportVector(void);

// * Vector Operation Part
double vectorSize(double *);
double *scalarMult(double *, double);
double *addVector(double *, double *);
double dotProduct(double *, double *);
double *crossProduct(double *, double *);

// * Safe input by @Teproanyx
// * Modified to fit this program by @Leomotors

int main(void)
{
    printf("\nWelcome to Vector Calculator Program!\n\n");
    printf("Press any key to continue...");
    getchar();
    while (true)
    {
        cls();
        printf("=====|Vector Calculator V3.2|=====\n\n");
        ShowAllVectors();
        printMainMenu();
        if (!programCore())
            return 0;
    }
}

// * Menu's Stuff
void printMainMenu(void)
{
    printf("\nPlease select Function from below list.\n");
    printf("[1] Input new vector!\n");
    printf("[2] Do operations!\n");
    printf("[3] Import & Export Vectors\n");
    printf("[4] Delete all Vectors\n");
    printf("[5] Settings\n");
    printf("[0] Exit\n");
}

bool programCore(void)
{
    int choice = getInt("Your Choice: ");
    switch (choice)
    {
    case 0:
        printf("Thanks for using this program! Press any key to exit...");
        getchar();
        return false; // * Tell next code in main to Exit program
    case 1:
        inputVector();
        break;
    case 2:
        vectorOperation();
        break;
    case 3:
        fileMenu();
        break;
    case 4:
        deleteAllVectors();
        break;
    case 5:
        settingsMenu();
        break;
    default:
        printf("Invalid choice, please try again.\n");
        printf("Press any key to continue...");
        getchar();
        break;
    }
    return true; // * User didn't wish to exit program
}

void printOperationMenu(void)
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

void vectorOperation(void)
{
    int choice, temp;
    int u, v;
    cls();
    printOperationMenu();
    choice = getInt("Selected Operation: ");
    if (choice == 0)
        return;
    if (choice < 0 || choice > 7)
    {
        printf("Invalid choice, try again!\nPress any key to continue...");
        getchar();
        return;
    }
    printf("\n");
    ShowAllVectors();
    printf("\n");
    if (choice == 1 || choice == 2)
    {
        u = getInt("Select Vector: ");
        if (!isVector(u))
        {
            printf("This vector not available, Press any key to continue...");
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
            printf("One or Both of vector not available, Press any key to continue...");
            getchar();
            return;
        }
    }

    char *format = calloc(10, sizeof(char));
    sprintf(format, "%%.%dlf", numberPrecision);
    switch (choice)
    {
    case 1:
        printf("Size of Vector #%d is ", u);
        printf(format, vectorSize(vector[u]));
        printf("\n");
        break;
    case 2:
        temp = getInt("Enter scalar to multiply with: ");
        saveVectorToSlot((scalarMult(vector[u], temp)));
        break;
    case 3:
        saveVectorToSlot(addVector(vector[u], vector[v]));
        break;
    case 4:
        printf("Dot Product is ");
        printf(format, dotProduct(vector[u], vector[v]));
        printf("\n");
        break;
    case 5:
        saveVectorToSlot(crossProduct(vector[u], vector[v]));
        break;
    case 6:
        saveVectorToSlot(scalarMult(vector[v], dotProduct(vector[u], vector[v]) / pow(vectorSize(vector[v]), 2)));
        break;
    case 7:
        printf("Area is ");
        printf(format, vectorSize(crossProduct(vector[u], vector[v])));
        printf(" Sq.Unit\n");
        break;
    default:
        printf("Error 003: Default kicks in, function: vectorOperation\n");
    }
    printf("Operation done, Please any to continue...");
    free(format);
    getchar();
}

void settingsMenu(void)
{
    int choice;
    printf("\n=====|Settings|=====\n\n");
    printf("[1] Set terminal (command prompt)'s color\n");
    printf("[2] Set Number Precision\n");
    printf("[0] Back\n");
    choice = getInt("Your option: ");
    switch (choice)
    {
    case 1:
        setColor();
        break;
    case 2:
        while (true)
        {
            numberPrecision = getInt("Number of digits after decimal: ");
            if (numberPrecision >= 0 && numberPrecision <= 6)
                break;
            else
                printf("Number of digits must be between 0 and 6!\n");
        }
        break;
    case 0:
        printf("Press any key to continue...");
        getchar();
        break;
    default:
        printf("Invalid choice, please try again.\n");
        printf("Press any key to continue...");
        getchar();
        break;
    }
}

void fileMenu(void)
{
    int choice;
    printf("\n=====|File Menu|=====\n\n");
    printf("[1] Import Vector\n");
    printf("[2] Export Vector\n");
    printf("[0] Back\n");
    choice = getInt("Your option: ");
    switch (choice)
    {
    case 1:
        importVector();
        break;
    case 2:
        exportVector();
        break;
    case 0:
        printf("Press any key to continue...");
        getchar();
        break;
    default:
        printf("Invalid choice, please try again.\n");
        printf("Press any key to continue...");
        getchar();
        break;
    }
}

void setColor(void) // ! Only supported on Windows
{
#if defined(_WIN32)
    char *col;
    char syn[10];
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
    col = getString("Enter color: ");
    sprintf(syn, "color %s", col);
    system(syn);
    free(col);
#else
    printf("This is only supported on Windows!\n");
    printf("Press any to continue...");
    getchar();
#endif
    cls();
}

void cls(void) // * By @Teproanyx
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}

bool getConfirmation(const char *prompt)
{
    char *confirm;
    char tempc;
    do
    {
        confirm = getString(prompt);
        tempc = confirm[0];
        free(confirm);
        if (tempc == 'N')
        {
            return false;
        }
    } while (tempc != 'Y');
    return true;
}

// * Vector management
void inputVector(void)
{
    int slot;
    slot = getInt("Which slot you want? : ");
    if (slot >= 0 && slot < VECTOR_ARRAY_SIZE)
    {
        if (vector[slot] != NULL)
        {
            if (!getConfirmation("Vector already exists, Overwrite? [Y/N]: "))
                return;
            free(vector[slot]);
        }
        double *u = malloc(sizeof(*u) * 3);
        char *buffer = getString("Please enter vector (i,j,k): ");
        sscanf(buffer, "%lf %lf %lf", &u[i], &u[j], &u[k]);
        vector[slot] = u;
        free(buffer);
    }
    else
    {
        printf("Invalid index!\nPress any to continue!");
        getchar();
    }
}

char *printvec(double *u)
{
    int d = numberPrecision;
    char *format = malloc(sizeof(char) * 40);
    strcpy(format, "");
    sprintf(format, "( %%.%dlf , %%.%dlf , %%.%dlf )", d, d, d);
    char *str = malloc(sizeof(char) * 100);
    strcpy(str, "");
    sprintf(str, format, u[i], u[j], u[k]);
    free(format);
    return str;
}

void ShowAllVectors(void)
{
    char *tmp;
    for (int m = 0; m < VECTOR_ARRAY_SIZE; m++)
    {
        if (vector[m] != NULL)
        {
            tmp = printvec(vector[m]);
            printf("Vector #%d : %s\n", m, tmp);
            free(tmp);
        }
    }
}

void saveVectorToSlot(double *u)
{
    int w;
    char *tmp = printvec(u);
    printf("Result Vector is %s\n", tmp);
    free(tmp);
    if (!getConfirmation("Do you want to save vector? [Y/N]: "))
    {
        free(u);
        return;
    }

    w = getInt("Where you want to save vector? : ");
    if (w < 0 || w >= VECTOR_ARRAY_SIZE)
    {
        printf("Can't save here, Index out of range\n");
        saveVectorToSlot(u);
        return;
    }
    if (vector[w] != NULL)
    {
        if (!getConfirmation("This slot already has vector in it. Overwrite? [Y/N]: "))
        {
            saveVectorToSlot(u);
            return;
        }
        free(vector[w]);
    }
    vector[w] = u;
}

bool isVector(int u)
{
    if (u < 0 || u >= VECTOR_ARRAY_SIZE)
        return false;
    return vector[u] != NULL;
}

bool deleteAllVectors(void)
{
    if (!getConfirmation("Warning: This action will delete all vector. Continue? [Y/N]: "))
    {
        return false;
    }

    for (int c = 0; c < VECTOR_ARRAY_SIZE; c++)
    {
        if (vector[c] != NULL)
        {
            free(vector[c]);
            vector[c] = NULL;
        }
    }
    printf("All vectors have been deleted, press any to continue...");
    getchar();
    return true;
}

// * Import and Export
void importVector(void)
{
    bool started = false;
    for (int c = 0; c < VECTOR_ARRAY_SIZE; c++)
    {
        if (isVector(c))
            started = true;
    }
    if (started && !deleteAllVectors())
    {
        return;
    }

    int slot = 0;
    double a1, a2, a3;
    char *tmp;
    char filename[100];
    FILE *inputFile;
    tmp = getString("Enter file name: ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        printf("Error upon opening files, File may not exist.\n");
        printf("Press any key to continue...");
        free(tmp);
        getchar();
        return;
    }
    while (true)
    {
        fscanf(inputFile, "%d %lf %lf %lf", &slot, &a1, &a2, &a3);
        if (vector[slot] == NULL)
        {
            vector[slot] = malloc(sizeof(*vector) * 3);
            vector[slot][i] = a1;
            vector[slot][j] = a2;
            vector[slot][k] = a3;
        }
        else
            break;
    }
    free(tmp);
    fclose(inputFile);
}

void exportVector(void)
{
    char *tmp;
    char filename[100];
    FILE *outputFile;
    tmp = getString("Enter file name: ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    free(tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        fclose(outputFile);
        if (!getConfirmation("File already exists, Overwrite? [Y/N]: "))
        {
            return;
        }
    }

    outputFile = fopen(filename, "w");
    for (int c = 0; c < VECTOR_ARRAY_SIZE; c++)
    {
        if (vector[c] != NULL)
            fprintf(outputFile, "%d %lf %lf %lf\n", c, vector[c][i], vector[c][j], vector[c][k]);
    }
    free(tmp);
    fclose(outputFile);
}

// * Vector Operation Part
double vectorSize(double *u)
{
    double result = u[i] * u[i] + u[j] * u[j] + u[k] * u[k];
    result = sqrt(result);
    return result;
}

double *scalarMult(double *u, double num)
{
    double *w = malloc(sizeof(*w) * 3);
    w[i] = num * u[i];
    w[j] = num * u[j];
    w[k] = num * u[k];
    return w;
}

double *addVector(double *u, double *v)
{
    double *w = malloc(sizeof(*w) * 3);
    w[i] = u[i] + v[i];
    w[j] = u[j] + v[j];
    w[k] = u[k] + v[k];
    return w;
}

double dotProduct(double *u, double *v)
{
    double result;
    result = u[i] * v[i] + u[j] * v[j] + u[k] * v[k];
    return result;
}

double *crossProduct(double *u, double *v)
{
    double *w = malloc(sizeof(*w) * 3);
    w[i] = u[j] * v[k] - u[k] * v[j];
    w[j] = u[k] * v[i] - v[k] * u[i];
    w[k] = u[i] * v[j] - v[i] * u[j];
    return w;
}
