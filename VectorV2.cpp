/*  
    * Project 「Vector Calculator」
    * 総制作　Leomotors
    * Version: 20w44a
    ? Change Log: Now Fully functional
    TODO Simp(lify) code
    TODO Make this resists against human error
    TODO Make this resists against input from Teproanyx
    ! Add .vscode for VSCode compilation via mingw g++
    ! Also add formatting style to settings
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define i 0
#define j 1
#define k 2

float *vector[100] = {NULL};

void vectorOperation();
void printMenu();
void inputVector();
void printvec(float *);
void saveVector(float *);
void setColor();
void cls();
void ShowAllVectors();

void importVector();

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
        printf("Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
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
        default:
            printf("Error\n");
            break;
        }
    }
}

void vectorOperation()
{
    int choice, temp;
    int u, v, w;
    cls();
    printMenu();
    printf("Enter choice: ");
    scanf("%d", &choice);
    if (choice == 0)
        return;
    if (choice < 0 || choice > 7)
    {
        printf("Invalid choice, try again!\nPress any to continue...");
        getchar();
        getchar();
        return;
    }
    if (choice == 1 || choice == 2)
    {
        printf("Select Vector: ");
        scanf("%d", &u);
    }
    else
    {
        printf("Select Two Vectors: ");
        scanf("%d %d", &u, &v);
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
        printf("Enter scalar to multiply with: ");
        scanf("%d", &temp);
        printvec(scalarMult(vector[u], temp));
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
    getchar();
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
    for (int m = 0; m < 100; m++)
    {
        if (vector[m] != NULL)
        {
            printf("Vector %d\n", m);
            printvec(vector[m]);
        }
    }
}

void importVector()
{
    int slot = 0;
    float a1, a2, a3;
    FILE *inputFile;
    if ((inputFile = fopen("Data1.txt", "r")) == NULL)
    {
        printf("Error! opening file");
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

void inputVector()
{
    int slot;
    char confirm;
    printf("Which slot you want? : ");
    scanf("%d", &slot);
    if (slot >= 0 && slot < 100)
    {
        if (vector[slot] != NULL)
        {
            printf(
                "Vector already exists, Overwrite?\n Press 'N' to decline,"
                " otherwise any key: ");
            scanf(" %c", &confirm);
            if (confirm == 'N')
                return;
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
        getchar();
    }
}

void printvec(float *u)
{
    printf("Result Vector: ( %.2f , %.2f , %.2f )\n", u[i], u[j], u[k]);
}

void saveVector(float *u)
{
    int w, choice;
    printf("Where you want to save vector? : ");
    scanf("%d", &w);
    if (vector[w] != NULL)
    {
        printf("This slot already has vector in it. Overwrite? : ");
        scanf(" %c", &choice);
        if (choice == 'N')
            return;
    }
    vector[w] = u;
}

void setColor()
{
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
    printf("Enter color (Only works in Windows through cmd!): ");
    scanf("%s", col);
    sprintf(syn, "color %s", col);
    system(syn);
    cls();
}

void cls() // * By Teproanyx
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
