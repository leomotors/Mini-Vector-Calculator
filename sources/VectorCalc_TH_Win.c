/**
 * * Project 「Vector Calculator」 Thai Version
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 */

#if defined(_WIN32)

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <io.h>
#include <wchar.h>

#include "SafeInput/SafeInput_TH.h"

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
void setColor(void);
void cls(void);
bool getConfirmation(const wchar_t *);

// * Vector management
void inputVector(void);
wchar_t *printvec(double *);
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
    setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"\nยินดีต้อนรับสู่ โปรแกรมคำนวณเวกเตอร์\n\n");
    wprintf(L"กดปุ่มใดๆ เพิ่อดำเนินการต่อ...\n");
    getchar();
    while (true)
    {
        cls();
        wprintf(L"=====|Vector Calculator V3.3 Thai Version|=====\n\n");
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
    wprintf(L"\nโปรดเลือกฟังก์ชันจากข้างล่างนี้\n");
    wprintf(L"[1] ป้อนเวกเตอร์ใหม่\n");
    wprintf(L"[2] คำนวณเกี่ยวกับเวกเตอร์\n");
    wprintf(L"[3] Lab: นำเข้าและส่งออกเวกเตอร์\n");
    wprintf(L"[4] ลบเวกเตอร์ทั้งหมด\n");
    wprintf(L"[5] การตั้งค่า\n");
    wprintf(L"[0] ออกจากโปรแกรม\n");
}

bool programCore(void)
{
    int choice = getInt(L"ตัวเลือกที่เลือก: ");
    switch (choice)
    {
    case 0:
        wprintf(L"ขอบคุณสำหรับการใช้งานโปรแกรม กดปุ่มใดๆ เพื่อปิดโปรแกรม");
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
        wprintf(L"ตัวเลือกไม่ถูกต้อง โปรดลองอีกครั้ง\n");
        wprintf(L"กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
        getchar();
        break;
    }
    return true; // * User didn't wish to exit program
}

void printOperationMenu(void)
{
    wprintf(L"==========================================\n");
    wprintf(L"กรุณาเลือกฟังก์ชันที่ต้องการใช้งาน\n");
    wprintf(L"\tการดำเนินการที่ใช้เวกเตอร์อันเดียว\n");
    wprintf(L"[1] หาขนาดของเวกเตอร์\n");
    wprintf(L"[2] คูณเวกเตอร์ด้วยสเกลาร์\n");
    wprintf(L"\tการดำเนินการที่ใช้เวกเตอร์สองอัน\n");
    wprintf(L"[3] บวก 2 เวกเตอร์\n");
    wprintf(L"[4] หาผลคูณเชิงสเกลาร์ของ 2 เวกเตอร์\n");
    wprintf(L"[5] หาผลคูณเชิงเวกเตอร์ของ 2 เวกเตอร์\n");
    wprintf(L"[6] โพรเจกเวกเตอร์ลงไปที่อีกเวกเตอร์\n");
    wprintf(L"[7] หาพื้นที่ของสี่เหลี่ยมด้านขนานที่เกิดจากสองเวกเตอร์\n");
    wprintf(L"[0] ออก\n");
}

void vectorOperation(void)
{
    int choice, temp;
    int u, v;
    cls();
    printOperationMenu();
    choice = getInt(L"ฟังก์ชันการดำเนินการที่เลือก: ");
    if (choice == 0)
        return;
    if (choice < 0 || choice > 7)
    {
        wprintf(L"ตัวเลือกไม่ถูกต้อง โปรดลองอีกครั้ง\nกดปุ่มใดๆ เพื่อดำเนินการต่อ...");
        getchar();
        return;
    }
    wprintf(L"\n");
    ShowAllVectors();
    wprintf(L"\n");
    if (choice == 1 || choice == 2)
    {
        u = getInt(L"เลือกเวกเตอร์: ");
        if (!isVector(u))
        {
            wprintf(L"ไม่มีเวกเตอร์นี้, กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
            getchar();
            return;
        }
    }
    else
    {
        u = getInt(L"เลือกเวกเตอร์อันแรก: ");
        v = getInt(L"เลือกเวกเตอร์อันที่สอง: ");
        if (!(isVector(u) && isVector(v)))
        {
            wprintf(L"หนึ่งหรือทั้งสองเวกเตอร์ไม่มี, กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
            getchar();
            return;
        }
    }

    wchar_t *format = calloc(10, sizeof(wchar_t));
    swprintf(format, 10, L"%%.%dlf", numberPrecision);
    switch (choice)
    {
    case 1:
        wprintf(L"ขนาดของเวกเตอร์หมายเลข %d คือ ", u);
        wprintf(format, vectorSize(vector[u]));
        wprintf(L"\n");
        break;
    case 2:
        temp = getDouble(L"ใส่ค่าสเกลาร์ที่จะนำไปคูณ: ");
        saveVectorToSlot((scalarMult(vector[u], temp)));
        break;
    case 3:
        saveVectorToSlot(addVector(vector[u], vector[v]));
        break;
    case 4:
        wprintf(L"ผลคูณเชิงสเกลาร์คือ ");
        wprintf(format, dotProduct(vector[u], vector[v]));
        wprintf(L"\n");
        break;
    case 5:
        saveVectorToSlot(crossProduct(vector[u], vector[v]));
        break;
    case 6:
        saveVectorToSlot(scalarMult(vector[v], dotProduct(vector[u], vector[v]) / pow(vectorSize(vector[v]), 2)));
        break;
    case 7:
        wprintf(L"พื้นที่คือ \n");
        wprintf(format, vectorSize(crossProduct(vector[u], vector[v])));
        wprintf(L" ตารางหน่วย\n");
        break;
    default:
        wprintf(L"Error 003: Default kicks in, function: vectorOperation\n");
    }
    wprintf(L"การดำเนินการเสร็จสิ้น กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
    free(format);
    getchar();
}

void settingsMenu(void)
{
    int choice;
    wprintf(L"\n=====|การตั้งค่า|=====\n\n");
    wprintf(L"[1] เปลี่ยนสีหน้าจอ\n");
    wprintf(L"[2] Lab: เลือกความละเอียดของตัวเลข\n");
    wprintf(L"[0] กลับ\n");
    choice = getInt(L"ตัวเลือกที่เลือก: ");
    switch (choice)
    {
    case 1:
        setColor();
        break;
    case 2:
        while (true)
        {
            if(!getConfirmation(L"คำเตือน: ฟังก์ชันนี้ไม่เสถียรและอาจทำให้โปรแกรมค้างได้ ดำเนินการต่อ? [Y/N]: "))
            {
                return;
            }
            numberPrecision = getInt(L"จำนวนหลักหลังทศนิยม: ");
            if (numberPrecision >= 0 && numberPrecision <= 6)
                break;
            else
                wprintf(L"จำนวนหลักต้องอยู่ระหว่าง 0 ถึง 6 โปรดลองอีกครั้ง\n");
        }
        break;
    case 0:
        wprintf(L"กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
        getchar();
        break;
    default:
        wprintf(L"ตัวเลือกไม่ถูกต้อง โปรดลองอีกครั้ง\n");
        wprintf(L"กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
        getchar();
        break;
    }
}

void fileMenu(void)
{
    int choice;
    wprintf(L"\n=====|เมนูไฟล์|=====\n\n");
    wprintf(L"คำเตือน: ฟังก์ชันนี้ไม่เสถียรและอาจทำให้โปรแกรมค้างได้\n");
    wprintf(L"[1] นำเข้าเวกเตอร์\n");
    wprintf(L"[2] ส่งออกเวกเตอร์\n");
    wprintf(L"[0] กลับ\n");
    choice = getInt(L"ตัวเลือกที่เลือก: ");
    switch (choice)
    {
    case 1:
        importVector();
        break;
    case 2:
        exportVector();
        break;
    case 0:
        wprintf(L"กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
        getchar();
        break;
    default:
        wprintf(L"ตัวเลือกไม่ถูกต้อง โปรดลองอีกครั้ง\n");
        wprintf(L"กดปุ่มใดๆ เพื่อดำเนินการต่อ...");
        getchar();
        break;
    }
}
void setColor(void) // ! Only supported on Windows
{
    char *col;
    char syn[10];
    wprintf(
        L"\nColor attributes are specified by TWO hex digits -- the first "
        L"corresponds to the background; the second the foreground."
        L"\nEach digit can be any of the following values:\n\n"
        L"\t0 = Black       8 = Gray\n"
        L"\t1 = Blue        9 = Light Blue\n"
        L"\t2 = Green       A = Light Green\n"
        L"\t3 = Aqua        B = Light Aqua\n"
        L"\t4 = Red         C = Light Red\n"
        L"\t5 = Purple      D = Light Purple\n"
        L"\t6 = Yellow      E = Light Yellow\n"
        L"\t7 = White       F = Bright White\n");
    col = getString(L"เลือกสี: ");
    sprintf(syn, "color %s", col);
    system(syn);
    cls();
    free(col);
}

void cls(void) // * By @Teproanyx
{
    system("cls");
}

bool getConfirmation(const wchar_t *prompt)
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
    slot = getInt(L"ต้องการใส่เวกเตอร์ที่ช่องไหน? : ");
    if (slot >= 0 && slot < VECTOR_ARRAY_SIZE)
    {
        if (vector[slot] != NULL)
        {
            if (!getConfirmation(L"เวกเตอร์มีอยู่แล้ว ต้องการแทนที่? [Y/N]: "))
            {
                return;
            }
            free(vector[slot]);
        }
        double *u = malloc(sizeof(*u) * 3);
        char *buffer = getString(L"กรุณาใส่เวกเตอร์ในรูปแบบของ i,j,k: ");
        sscanf(buffer, "%lf %lf %lf", &u[i], &u[j], &u[k]);
        vector[slot] = u;
        free(buffer);
    }
    else
    {
        wprintf(L"ไม่มีช่องนั้นอยู่ กดปุ่มใดๆเพื่อดำเนินการต่อ");
        getchar();
    }
}

wchar_t *printvec(double *u)
{
    int d = numberPrecision;
    char *format = malloc(sizeof(*format) * 40);
    strcpy(format, "");
    sprintf(format, "( %%.%dlf , %%.%dlf , %%.%dlf )", d, d, d);
    char *str = malloc(sizeof(*str) * 100);
    strcpy(str, "");
    sprintf(str, format, u[i], u[j], u[k]);
    wchar_t *wstr = calloc(strlen(str), sizeof(*wstr));
    int tstrlen = (int)(strlen(str));
    for (int lc = 0; lc < tstrlen; lc++)
    {
        wstr[lc] = (wchar_t)(str[lc]);
    }
    // * Forcing '\0' to stop string from printing
    wstr[tstrlen] = '\0';
    return wstr;
}

void ShowAllVectors(void)
{
    for (int m = 0; m < VECTOR_ARRAY_SIZE; m++)
    {
        if (vector[m] != NULL)
        {
            wprintf(L"เวกเตอร์ หมายเลข %d : %s\n", m, printvec(vector[m]));
        }
    }
}

void saveVectorToSlot(double *u)
{
    int w;
    wprintf(L"เวกเตอร์ผลลัพธ์คือ %s\n", printvec(u));
    if (!getConfirmation(L"ต้องการบันทึกเวกเตอร์หรือไม่? [Y/N]: "))
    {
        free(u);
        return;
    }

    w = getInt(L"ต้องการบันทึกเวกเตอร์ที่ไหน? : ");
    if (w < 0 || w >= VECTOR_ARRAY_SIZE)
    {
        wprintf(L"ไม่สามารถบันทึกที่นี่ได้ ช่องนั้นอยู่นอกขอบเขต\n");
        saveVectorToSlot(u);
        return;
    }
    if (vector[w] != NULL)
    {
        if (!getConfirmation(L"ช่องนี้มีเวกเตอร์อยู่แล้ว บันทึกทับ? [Y/N]: "))
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
    if (!getConfirmation(L"คำเตือน: การดำเนินการนี้จะลบเวกเตอร์ทั้งหมด ดำเนินการต่อ? [Y/N]: "))
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
    wprintf(L"เวกเตอร์ทั้งหมดถูกลบแล้ว กดปุ่มใดๆเพื่อดำเนินการต่อ...");
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
    tmp = getString(L"โปรดใส่ชื่อไฟล์: ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        wprintf(L"ไม่สามารถเปิดไฟล์ได้ ไฟล์นี้อาจไม่มีอยู่\n");
        wprintf(L"กดปุ่มใดๆเพื่อดำเนินการต่อ");
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
    tmp = getString(L"โปรดใส่ชื่อไฟล์ : ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    free(tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        fclose(outputFile);
        if (!getConfirmation(L"ไฟล์นี้มีอยู่แล้ว เขียนทับ? [Y/N]: "))
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

#else
#include <stdio.h>
int main(void)
{
    printf("This is for Windows Version. Please run Linux Version!\n");
}
#endif