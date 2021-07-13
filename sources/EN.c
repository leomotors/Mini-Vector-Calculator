/**
 * * Project 「Vector Calculator」
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../SafeInput/SafeInput.h"

#ifndef LANGUAGE_FILE_IMPORTED
// * Set to Default Language, In case users run from main (or error occur)
#include "../Language/EN.h"
#endif

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
void freeAllVectors(void);

// * Import and Export
void importVector(void);
void exportVector(void);

// * Vector Operation Part
double vectorSize(double *);
double *scalarMult(double *, double);
double *addVector(double *, double *);
double dotProduct(double *, double *);
double *crossProduct(double *, double *);

int main(void)
{
    printf(IRASSHAI_1);
    printf(PRESS_ANY_KEY_TO_CONTINUE);
    getchar();
    while (true)
    {
        cls();
        printf(PROGRAM_TITLE);
        ShowAllVectors();
        printMainMenu();
        if (!programCore())
        {
            freeAllVectors();
            return 0;
        }
    }
}

// * Menu's Stuff
void printMainMenu(void)
{
    printf(PLEASE_SELECT_FUNC);
    printf(MENU_1);
    printf(MENU_2);
    printf(MENU_3);
    printf(MENU_4);
    printf(MENU_5);
    printf(EXIT_PROGRAM);
}

bool programCore(void)
{
    int choice = getInt(YOUR_CHOICE);
    switch (choice)
    {
    case 0:
        printf(EXIT_THANK_YOU);
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
        printf(INVALID_CHOICE);
        printf(PRESS_ANY_KEY_TO_CONTINUE);
        getchar();
        break;
    }
    return true; // * User didn't wish to exit program
}

void printOperationMenu(void)
{
    printf("==========================================\n");
    printf(PLEASE_SELECT_FUNC);
    printf(ONE_VEC_OP);
    printf(VEC_OP_1);
    printf(VEC_OP_2);
    printf(TWO_VEC_OP);
    printf(VEC_OP_3);
    printf(VEC_OP_4);
    printf(VEC_OP_5);
    printf(VEC_OP_6);
    printf(VEC_OP_7);
    printf(MENU_EXIT);
}

void vectorOperation(void)
{
    int choice, temp;
    int u, v = -1;
    cls();
    printOperationMenu();
    choice = getInt(SELECTED_OP);
    if (choice == 0)
        return;
    if (choice < 0 || choice > 7)
    {
        printf(INVALID_CHOICE);
        printf(PRESS_ANY_KEY_TO_CONTINUE);
        getchar();
        return;
    }
    printf("\n");
    ShowAllVectors();
    printf("\n");
    if (choice == 1 || choice == 2)
    {
        u = getInt(SELECT_VECTOR);
        if (!isVector(u))
        {
            printf(VECTOR_NOT_AVAILABLE);
            getchar();
            return;
        }
    }
    else
    {
        u = getInt(SEL_FIRST_VEC);
        v = getInt(SEL_SECOND_VEC);
        if (!(isVector(u) && isVector(v)))
        {
            printf(ONE_OR_BOTH_NOT_AVAILABLE);
            getchar();
            return;
        }
    }

    char *format = calloc(10, sizeof(char));
    sprintf(format, "%%.%dlf", numberPrecision);
    switch (choice)
    {
    case 1:
        printf(SIZE_OF_VEC_IS, u);
        printf(format, vectorSize(vector[u]));
        printf("\n");
        break;
    case 2:
        temp = getDouble(ENTER_SCALAR);
        saveVectorToSlot((scalarMult(vector[u], temp)));
        break;
    case 3:
        saveVectorToSlot(addVector(vector[u], vector[v]));
        break;
    case 4:
        printf(DOT_PROD_IS);
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
        printf(AREA_IS);
        printf(format, vectorSize(crossProduct(vector[u], vector[v])));
        printf(SQ_UNIT);
        break;
    default:
        printf("Error 003: Default kicks in, function: vectorOperation\n");
    }
    printf(OP_DONE_AND_PRESS_ANY_KEY);
    free(format);
    getchar();
}

void settingsMenu(void)
{
    int choice;
    printf(SETTINGS_TITLE);
    printf(SETTINGS_1);
    printf(SETTINGS_2);
    printf(BACK_0);
    choice = getInt(YOUR_CHOICE);
    switch (choice)
    {
    case 1:
        setColor();
        break;
    case 2:
        while (true)
        {
            numberPrecision = getInt(N_DIGITS_A_DECIMAL);
            if (numberPrecision >= 0 && numberPrecision <= 6)
                break;
            else
                printf(N_DIGITS_TRACEBACK);
        }
        break;
    case 0:
        printf(PRESS_ANY_KEY_TO_CONTINUE);
        getchar();
        break;
    default:
        printf(INVALID_CHOICE);
        printf(PRESS_ANY_KEY_TO_CONTINUE);
        getchar();
        break;
    }
}

void fileMenu(void)
{
    int choice;
    printf(FILE_MENU);
    printf(FILE_1);
    printf(FILE_2);
    printf(BACK_0);
    choice = getInt(YOUR_CHOICE);
    switch (choice)
    {
    case 1:
        importVector();
        break;
    case 2:
        exportVector();
        break;
    case 0:
        printf(PRESS_ANY_KEY_TO_CONTINUE);
        getchar();
        break;
    default:
        printf(INVALID_CHOICE);
        printf(PRESS_ANY_KEY_TO_CONTINUE);
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
    printf(ONLYWINDOWS);
    printf(PRESS_ANY_KEY_TO_CONTINUE);
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
    slot = getInt(WHICH_SLOT);
    if (slot >= 0 && slot < VECTOR_ARRAY_SIZE)
    {
        if (vector[slot] != NULL)
        {
            if (!getConfirmation(VECTOR_ALR_EXIST))
            {
                return;
            }
            free(vector[slot]);
        }
        double *u = malloc(sizeof(*u) * 3);
        char *buffer = getString(ENTER_VECTOR);
        sscanf(buffer, "%lf %lf %lf", &u[i], &u[j], &u[k]);
        vector[slot] = u;
        free(buffer);
    }
    else
    {
        printf(INVALID_INDEX_PAKTC);
        getchar();
    }
}

char *printvec(double *u)
{
    int d = numberPrecision;
    char *format = malloc(sizeof(*format) * 40);
    strcpy(format, "");
    sprintf(format, "( %%.%dlf , %%.%dlf , %%.%dlf )", d, d, d);
    char *str = malloc(sizeof(*str) * 100);
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
            printf(VECTOR_N, m, tmp);
            free(tmp);
        }
    }
}

void saveVectorToSlot(double *u)
{
    int w;
    char *tmp = printvec(u);
    printf(RESULT_VECTOR_IS, tmp);
    free(tmp);
    if (!getConfirmation(DO_YOU_WANT_TO_SAVE))
    {
        free(u);
        return;
    }

    w = getInt(WHERE_TO_SAVE);
    if (w < 0 || w >= VECTOR_ARRAY_SIZE)
    {
        printf(INDEX_OUT_OF_RANGE);
        saveVectorToSlot(u);
        return;
    }
    if (vector[w] != NULL)
    {
        if (!getConfirmation(ALREADY_EXIST))
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
    if (!getConfirmation(THIS_WILL_DELETE_ALL_VEC))
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
    printf(ALL_VEC_DELETED);
    getchar();
    return true;
}

void freeAllVectors(void)
{
    for (int lc = 0; lc < VECTOR_ARRAY_SIZE; lc++)
    {
        if (vector[lc] != NULL)
            free(vector[lc]);
    }
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
    tmp = getString(ENTER_FNAME);
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        printf(ERROR_OPENING_FILE);
        printf(PRESS_ANY_KEY_TO_CONTINUE);
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
    tmp = getString(ENTER_FNAME);
    sprintf(filename, "VectorSave/%s.txt", tmp);
    free(tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        fclose(outputFile);
        if (!getConfirmation(F_ALREADY_EXIST))
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
