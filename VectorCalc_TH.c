/**
 * * Project 「Vector Calculator」 Thai Version
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 */

#if defined(_WIN32)

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

#include <fcntl.h>
#include <io.h>

#define i 0
#define j 1
#define k 2

int floatingPoint = 2;

#define vectorArraySize 100
float *vector[vectorArraySize] = {NULL};

// * Menu's Stuff
void printMainMenu(void);
bool programCore(void);
void printOperationMenu(void);
void vectorOperation(void);
void settingsMenu(void);
void setColor(void);
void cls(void);

// * Vector management
void inputVector(void);
const wchar_t *printvec(float *);
void ShowAllVectors(void);
void saveVector(float *);
bool isVector(int);
bool deleteAllVectors(void);

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
long long getlong(const wchar_t *);
int getInt(const wchar_t *);
float getFloat(const wchar_t *);
double getDouble(const wchar_t *);
char *getString(const wchar_t *);
void memoryError(const void *);

int main(void)
{
    setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"\nยินดีต้อนรับสู่ โปรแกรมคำนวณเวกเตอร์\n\n");
    wprintf(L"กดปุ่มใดๆ เพิ่อดำเนินการต่อ...\n");
    getchar();
    while (true)
    {
        cls();
        wprintf(L"=====|Vector Calculator V3.0 Thai Version|=====\n\n");
        ShowAllVectors();
        printMainMenu();
        if (!programCore())
            return 0;
    }
}

// * Menu's Stuff
void printMainMenu(void)
{
    wprintf(L"\nโปรดเลือกฟังก์ชันจากข้างล่างนี้\n");
    wprintf(L"[1] ป้อนเวกเตอร์ใหม่\n");
    wprintf(L"[2] คำนวณเกี่ยวกับเวกเตอร์\n");
    wprintf(L"[3] Lab: นำเข้าเวกเตอร์จากไฟล์\n");
    wprintf(L"[4] Lab: ส่งออกเวกเตอร์ไปยังไฟล์\n");
    wprintf(L"[5] ลบเวกเตอร์ทั้งหมด\n");
    wprintf(L"[6] การตั้งค่า\n");
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
    swprintf(format, 10, L"%%.%df", floatingPoint);
    switch (choice)
    {
    case 1:
        wprintf(L"ขนาดของเวกเตอร์หมายเลข %d คือ ", u);
        wprintf(format, vectorSize(vector[u]));
        wprintf(L"\n");
        break;
    case 2:
        temp = getInt(L"ใส่ค่าสเกลาร์ที่จะนำไปคูณ: ");
        saveVector((scalarMult(vector[u], temp)));
        break;
    case 3:
        saveVector(addVector(vector[u], vector[v]));
        break;
    case 4:
        wprintf(L"ผลคูณเชิงสเกลาร์คือ ");
        wprintf(format, dotProduct(vector[u], vector[v]));
        wprintf(L"\n");
        break;
    case 5:
        saveVector(crossProduct(vector[u], vector[v]));
        break;
    case 6:
        saveVector(scalarMult(vector[v], dotProduct(vector[u], vector[v]) / pow(vectorSize(vector[v]), 2)));
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
    getchar();
}

void settingsMenu(void)
{
    int choice;
    wprintf(L"\n=====|การตั้งค่า|=====\n\n");
    wprintf(L"[1] เปลี่ยนสีหน้าจอ\n");
    wprintf(L"[2] เลือกความละเอียดของตัวเลข\n");
    choice = getInt(L"ตัวเลือกที่เลือก: ");
    switch (choice)
    {
    case 1:
        setColor();
        break;
    case 2:
        while (true)
        {
            floatingPoint = getInt(L"จำนวนหลักหลังทศนิยม: ");
            if (floatingPoint >= 0 && floatingPoint <= 6)
                break;
            else
                wprintf(L"จำนวนหลักต้องอยู่ระหว่าง 0 ถึง 6 โปรดลองอีกครั้ง\n");
        }
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
}

void cls(void) // * By @Teproanyx
{
    system("cls");
}

// * Vector management
void inputVector(void)
{
    int slot;
    char *confirm = malloc(sizeof(char) * 100);
    slot = getInt(L"ต้องการใส่เวกเตอร์ที่ช่องไหน? : ");
    if (slot >= 0 && slot < vectorArraySize)
    {
        if (vector[slot] != NULL)
        {
            do
            {
                confirm = getString(L"เวกเตอร์มีอยู่แล้ว ต้องการแทนที่? [Y/N]: ");
                if (confirm[0] == 'N')
                    return;
            } while (confirm[0] != 'Y');
            free(vector[slot]);
        }
        float *u = malloc(sizeof(*u) * 3);
        char *buffer = getString(L"กรุณาใส่เวกเตอร์ในรูปแบบของ i,j,k: ");
        sscanf(buffer, "%f %f %f", &u[i], &u[j], &u[k]);
        vector[slot] = u;
    }
    else
    {
        wprintf(L"ไม่มีช่องนั้นอยู่ กดปุ่มใดๆเพื่อดำเนินการต่อ");
        getchar();
    }
    free(confirm);
}

const wchar_t *printvec(float *u)
{
    int d = floatingPoint;
    char *format = malloc(sizeof(char) * 30);
    strcpy(format, "");
    sprintf(format, "( %%.%df , %%.%df , %%.%df )", d, d, d);
    char *str = malloc(sizeof(char) * 100);
    strcpy(str, "");
    sprintf(str, format, u[i], u[j], u[k]);
    wchar_t *wstr = calloc(strlen(str), sizeof(wchar_t));
    for (int lc = 0; lc < strlen(str); lc++)
    {
        wstr[lc] = (wchar_t)(str[lc]);
    }
    free(str);
    return wstr;
}

void ShowAllVectors(void)
{
    for (int m = 0; m < vectorArraySize; m++)
    {
        if (vector[m] != NULL)
        {
            wprintf(L"เวกเตอร์ หมายเลข %d : %s\n", m, printvec(vector[m]));
        }
    }
}

void saveVector(float *u)
{
    int w;
    wprintf(L"เวกเตอร์ผลลัพธ์คือ %s\n", printvec(u));
    char *choice = malloc(sizeof(char) * 100);
    do
    {
        choice = getString(L"ต้องการบันทึกเวกเตอร์หรือไม่? [Y/N]: ");
        if (choice[0] == 'N')
            return;
    } while (choice[0] != 'Y');
    w = getInt(L"ต้องการบันทึกเวกเตอร์ที่ไหน? : ");
    if (vector[w] != NULL)
    {
        do
        {
            choice = getString(L"ช่องนี้มีเวกเตอร์อยู่แล้ว บันทึกทับ? [Y/N]: ");
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

bool deleteAllVectors(void)
{
    char *choice = malloc(sizeof(char) * 100);
    do
    {
        choice = getString(L"คำเตือน: การดำเนินการนี้จะลบเวกเตอร์ทั้งหมด ดำเนินการต่อ? [Y/N]: ");
        if (choice[0] == 'N')
            return false;
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
    wprintf(L"เวกเตอร์ทั้งหมดถูกลบแล้ว กดปุ่มใดๆเพื่อดำเนินการต่อ...");
    getchar();
    return true;
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
    if (started && !deleteAllVectors())
    {
        return;
    }
    free(choice);

    int slot = 0;
    float a1, a2, a3;
    char *tmp;
    char filename[100];
    FILE *inputFile;
    tmp = getString(L"โปรดใส่ชื่อไฟล์: ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        wprintf(L"ไม่สามารถเปิดไฟล์ได้ ไฟล์นี้อาจไม่มีอยู่\n");
        wprintf(L"กดปุ่มใดๆเพื่อดำเนินการต่อ");
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
    tmp = getString(L"โปรดใส่ชื่อไฟล์ : ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    free(tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        do
        {
            choice = getString(L"ไฟล์นี้มีอยู่แล้ว เขียนทับ? [Y/N]: ");
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
long getLong(const wchar_t *prompt)
{
    char *buffer = getString(prompt);
    if (buffer[0] == '\0')
    {
        free(buffer);
        wprintf(L"การป้อนข้อมูลผิดพลาด โปรดลองใหม่อีกครั้ง\n");
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    long n = strtol(buffer, &end, 10);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        wprintf(L"การป้อนข้อมูลผิดพลาด โปรดลองใหม่อีกครั้ง\n");
        return getLong(prompt);
    }

    free(buffer);

    return n;
}

int getInt(const wchar_t *prompt)
{
    long n = getLong(prompt);
    if (n > INT_MAX || n < INT_MIN)
    {
        wprintf(L"การป้อนข้อมูลผิดพลาด โปรดลองใหม่อีกครั้ง\n");
        return getInt(prompt);
    }
    return (int)n;
}

float getFloat(const wchar_t *prompt)
{
    double temp = getDouble(prompt);
    if (temp > FLT_MAX || temp < FLT_MIN)
    {
        wprintf(L"Error! Overflowed!\n");
        return getFloat(prompt);
    }
    return (float)temp;
}

double getDouble(const wchar_t *prompt)
{
    char *buffer = getString(prompt);
    if (buffer[0] == '\0')
    {
        free(buffer);
        wprintf(L"การป้อนข้อมูลผิดพลาด โปรดลองใหม่อีกครั้ง\n");
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    double n = strtod(buffer, &end);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        wprintf(L"การป้อนข้อมูลผิดพลาด โปรดลองใหม่อีกครั้ง\n");
        return getDouble(prompt);
    }

    free(buffer);

    return n;
}

char *getString(const wchar_t *prompt)
{
    size_t size = INITIAL_BUFFER;
    wprintf(L"%s", prompt);
    char *buffer = malloc((size + 1) * sizeof(*buffer));
    memoryError(buffer);
    if (fgets(buffer, size + 1, stdin) == NULL)
    {
        free(buffer);
        wprintf(L"Error, try again!\n");
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
            wprintf(L"Read Error(WTF HOW), try again MTFKER!\n");
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
        wprintf(L"RAM ไม่เพียงพอ กำลังปิดโปรแกรม...\n");
        exit(EXIT_FAILURE);
    }
}

#else
#include <stdio.h>
int main(void)
{
    printf("Thai version doesn't support in Linux!\n");
}
#endif