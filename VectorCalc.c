/**
 * * Project 「Vector Calculator」
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 */

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#define INITIAL_BUFFER 8

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define i 0
#define j 1
#define k 2

#define vectorArraySize 100
int floatingPoint = 2;
float *vector[vectorArraySize] = {NULL};

// * Menu's Stuff
void printMainMenu(void);
bool programCore(void);
void printOperationMenu(void);
void vectorOperation(void);
void settingsMenu(void);
void setColor(void); // ! Only supported on Windows
void cls(void);

// * Vector management
void inputVector(void);
const char *printvec(float *);
void ShowAllVectors(void);
void saveVector(float *);
bool isVector(int);
void deleteAllVectors(void);

// * Import and Export
void importVector(void);
void exportVector(void);

// * Vector Operation Part
float vectorSize(float *);
float *scalarMult(float *, float);
float *addVector(float *, float *);
float dotProduct(float *, float *);
float *crossProduct(float *, float *);

// * Safe input by @Teproanyx
// * Modified to fit this program by @Leomotors
long long getlong(const char *);
int getInt(const char *);
float getFloat(const char *);
double getDouble(const char *);
char *getString(const char *);
void memoryError(const void *);

int main(void)
{
    printf("\nWelcome to Vector Calculator Program!\n\n");
    printf("Press any key to continue...");
    getchar();
    while (true)
    {
        cls();
        printf("=====|Vector Calculator V3.0|=====\n\n");
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
    printf("[3] Lab: Import Vector from file\n");
    printf("[4] Lab: Export Vector to file\n");
    printf("[5] Delete all Vectors\n");
    printf("[6] Settings\n");
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
        importVector();
        break;
    case 4:
        exportVector();
        break;
    case 5:
        deleteAllVectors();
        break;
    case 6:
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
    switch (choice)
    {
    case 1:
    {
        printf("Size of Vector #%d is %.2f\n", u, vectorSize(vector[u]));
        break;
    }
    case 2:
    {
        temp = getInt("Enter scalar to multiply with: ");
        saveVector((scalarMult(vector[u], temp)));
        break;
    }
    case 3:
        saveVector(addVector(vector[u], vector[v]));
        break;
    case 4:
        printf("Dot Product is %.2f\n", dotProduct(vector[u], vector[v]));
        break;
    case 5:
        saveVector(crossProduct(vector[u], vector[v]));
        break;
    case 6:
        saveVector(scalarMult(vector[v], dotProduct(vector[u], vector[v]) / pow(vectorSize(vector[v]), 2)));
        break;
    case 7:
        printf("Area is %.2f Sq.Unit\n", vectorSize(crossProduct(vector[u], vector[v])));
        break;
    default:
        printf("Error 003: Default kicks in, function: vectorOperation\n");
    }
    printf("Operation done, Please any to continue...");
    getchar();
}

void settingsMenu(void)
{
    int choice;
    printf("\n=====|Settings|=====\n\n");
    printf("[1] Set terminal (command prompt)'s color\n");
    printf("[2] Set Number Precision\n");
    choice = getInt("Your option: ");
    switch (choice)
    {
    case 1:
        setColor();
        break;
    case 2:
        floatingPoint = getInt("Number of floating point: ");
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

// * Vector management
void inputVector(void)
{
    int slot;
    char *confirm = malloc(sizeof(char) * 100);
    slot = getInt("Which slot you want? : ");
    if (slot >= 0 && slot < vectorArraySize)
    {
        if (vector[slot] != NULL)
        {
            do
            {
                confirm = getString("Vector already exists, Overwrite? [Y/N]: ");
                if (confirm[0] == 'N')
                    return;
            } while (confirm[0] != 'Y');
            free(vector[slot]);
        }
        float *u = malloc(sizeof(*u) * 3);
        char *buffer = getString("Please enter vector (i,j,k): ");
        sscanf(buffer, "%f %f %f", &u[i], &u[j], &u[k]);
        vector[slot] = u;
    }
    else
    {
        printf("Invalid index!\nPress any to continue!");
        getchar();
    }
    free(confirm);
}

const char *printvec(float *u)
{
    int d = floatingPoint;
    char *format = malloc(sizeof(char) * 30);
    strcpy(format, "");
    sprintf(format, "( %%.%df , %%.%df , %%.%df )", d, d, d);
    char *str = malloc(sizeof(char) * 100);
    strcpy(str, "");
    sprintf(str, format, u[i], u[j], u[k]);
    return str;
}

void ShowAllVectors(void)
{
    for (int m = 0; m < vectorArraySize; m++)
    {
        if (vector[m] != NULL)
        {
            printf("Vector #%d : %s\n", m, printvec(vector[m]));
        }
    }
}

void saveVector(float *u)
{
    int w;
    printf("Result Vector is %s\n", printvec(u));
    char *choice = malloc(sizeof(char) * 100);
    do
    {
        choice = getString("Do you want to save vector? [Y/N]: ");
        if (choice[0] == 'N')
            return;
    } while (choice[0] != 'Y');
    w = getInt("Where you want to save vector? : ");
    if (vector[w] != NULL)
    {
        do
        {
            choice = getString("This slot already has vector in it. Overwrite? [Y/N]: ");
            if (choice[0] == 'N')
            {
                saveVector(u);
                return;
            }
        } while (choice[0] != 'Y');
        free(vector[w]);
    }
    vector[w] = u;
    free(choice);
}

bool isVector(int u)
{
    return vector[u] != NULL;
}

void deleteAllVectors(void)
{
    char *choice = malloc(sizeof(char) * 100);
    do
    {
        choice = getString("Warning: This action will delete all vector. Continue? [Y/N]: ");
        if (choice[0] == 'N')
            return;
    } while (choice[0] != 'Y');

    for (int c = 0; c < vectorArraySize; c++)
    {
        if (vector[c] != NULL)
        {
            free(vector[c]);
            vector[c] = NULL;
        }
    }
    free(choice);
    printf("All vectors have been deleted, press any to continue...");
    getchar();
}

// * Import and Export
void importVector(void)
{
    bool started = false;
    char *choice = malloc(sizeof(char) * 100);
    for (int c = 0; c < vectorArraySize; c++)
    {
        if (isVector(c))
            started = true;
    }
    if (started)
    {
        do
        {
            choice = getString("Using this function will remove all existing vector, continue? [Y/N]: ");
            if (choice[0] == 'N')
                return;
        } while (choice[0] != 'Y');
        deleteAllVectors();
    }
    free(choice);

    int slot = 0;
    float a1, a2, a3;
    char *tmp;
    char filename[100];
    FILE *inputFile;
    tmp = getString("Enter file name: ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        printf("Error upon opening files, File may not exist.\n");
        printf("Press any key to continue...");
        getchar();
        return;
    }
    while (true)
    {
        fscanf(inputFile, "%d %f %f %f", &slot, &a1, &a2, &a3);
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
    fclose(inputFile);
}

void exportVector(void)
{
    char *tmp = malloc(sizeof(char) * 100);
    char *choice = malloc(sizeof(char) * 100);
    char filename[100];
    FILE *outputFile;
    tmp = getString("Enter file name: ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    free(tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        do
        {
            choice = getString("File already exists, Overwrite? [Y/N]: ");
            if (choice[0] == 'N')
            {
                free(choice);
                return;
            }
        } while (choice[0] != 'Y');
    }
    free(choice);

    outputFile = fopen(filename, "w");
    for (int c = 0; c < vectorArraySize; c++)
    {
        if (vector[c] != NULL)
            fprintf(outputFile, "%d %f %f %f\n", c, vector[c][i], vector[c][j], vector[c][k]);
    }
    fclose(outputFile);
}

// * Vector Operation Part
float vectorSize(float *u)
{
    float result = u[i] * u[i] + u[j] * u[j] + u[k] * u[k];
    result = sqrt(result);
    return result;
}

float *scalarMult(float *u, float num)
{
    float *w = malloc(sizeof(*w) * 3);
    w[i] = num * u[i];
    w[j] = num * u[j];
    w[k] = num * u[k];
    return w;
}

float *addVector(float *u, float *v)
{
    float *w = malloc(sizeof(*w) * 3);
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
    float *w = malloc(sizeof(*w) * 3);
    w[i] = u[j] * v[k] - u[k] * v[j];
    w[j] = u[k] * v[i] - v[k] * u[i];
    w[k] = u[i] * v[j] - v[i] * u[j];
    return w;
}

// * Safe input by @Teproanyx
// * Modified to fit this program by @Leomotors
long getLong(const char *prompt)
{
    char *buffer = getString(prompt);
    if (buffer[0] == '\0')
    {
        free(buffer);
        printf("Input error, please try again!\n");
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    long n = strtol(buffer, &end, 10);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        printf("Input error, please try again!\n");
        return getLong(prompt);
    }

    free(buffer);

    return n;
}

int getInt(const char *prompt)
{
    long n = getLong(prompt);
    if (n > INT_MAX || n < INT_MIN)
    {
        printf("Input error, please try again!\n");
        return getInt(prompt);
    }
    return (int)n;
}

float getFloat(const char *prompt)
{
    double temp = getDouble(prompt);
    if (temp > FLT_MAX || temp < FLT_MIN)
    {
        printf("Error! Overflowed!\n");
        return getFloat(prompt);
    }
    return (float)temp;
}

double getDouble(const char *prompt)
{
    char *buffer = getString(prompt);
    if (buffer[0] == '\0')
    {
        free(buffer);
        printf("Input error, please try again!\n");
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    double n = strtod(buffer, &end);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        printf("Input error, please try again!\n");
        return getDouble(prompt);
    }

    free(buffer);

    return n;
}

char *getString(const char *prompt)
{
    size_t size = INITIAL_BUFFER;
    printf("%s", prompt);
    char *buffer = malloc((size + 1) * sizeof(*buffer));
    memoryError(buffer);
    if (fgets(buffer, size + 1, stdin) == NULL)
    {
        free(buffer);
        printf("Error, try again!\n");
        return getString(prompt);
    }
    while (buffer[strlen(buffer) - 1] != '\n')
    {
        char *subBuffer = malloc((size + 1) * sizeof(*subBuffer));
        memoryError(subBuffer);

        if (fgets(subBuffer, size + 1, stdin) == NULL)
        {
            free(buffer);
            free(subBuffer);
            printf("Read Error(WTF HOW), try again MTFKER!\n");
            return getString(prompt);
        }

        size *= 2;
        buffer = realloc(buffer, size + 1);
        memoryError(buffer);

        strncat(buffer, subBuffer, size / 2);
        free(subBuffer);
    }
    buffer[strlen(buffer) - 1] = '\0';
    buffer = realloc(buffer, strlen(buffer) + 1);
    memoryError(buffer);
    return buffer;
}

void memoryError(const void *pointer)
{
    if (pointer == NULL)
    {
        printf("Not enough RAM. Terminating program...\n");
        exit(EXIT_FAILURE);
    }
}
