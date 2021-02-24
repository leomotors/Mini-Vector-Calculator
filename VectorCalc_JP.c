/**
 * * Project 「Vector Calculator」 Japanese Version
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 * ! Translation might not be 100% correct. Author is just at N5.
 * ! 翻訳が全部正しくない可能性があります。 作者はただN5です。
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
#include <wchar.h>

#define i 0
#define j 1
#define k 2

int floatingPoint = 2;

#define VECTOR_ARRAY_SIZE 100
float *vector[VECTOR_ARRAY_SIZE] = {NULL};

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
const wchar_t *printvec(float *);
void ShowAllVectors(void);
void saveVectorToSlot(float *);
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
    wprintf(L"\nベクトル計算機へいらっしゃいませ！\n\n");
    wprintf(L"続行するには任意のボタンを押してください。\n");
    getchar();
    while (true)
    {
        cls();
        wprintf(L"=====|Vector Calculator V3.0 Japanese Version|=====\n\n");
        ShowAllVectors();
        printMainMenu();
        if (!programCore())
            return 0;
    }
}

// * Menu's Stuff
void printMainMenu(void)
{
    wprintf(L"\n下の機能を選んでください。\n");
    wprintf(L"[1] 新ベクトルを入力する\n");
    wprintf(L"[2] ベクトルについて計算\n");
    wprintf(L"[3] インポート・エクスポートベクトル\n");
    wprintf(L"[4] すべてのベクトルを削除する\n");
    wprintf(L"[5] 設定\n");
    wprintf(L"[0] プログラムを終了する\n");
}

bool programCore(void)
{
    int choice = getInt(L"選んでいる選択: ");
    switch (choice)
    {
    case 0:
        wprintf(L"プログラムを使ってありがとうございます 出るには任意のボタンを押してください。");
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
        wprintf(L"選択無効 もう一度やり直してください\n");
        wprintf(L"続行するには任意のボタンを押してください。");
        getchar();
        break;
    }
    return true; // * User didn't wish to exit program
}

void printOperationMenu(void)
{
    wprintf(L"==========================================\n");
    wprintf(L"機能を選んでください\n");
    wprintf(L"\t一つのベクトル演算\n");
    wprintf(L"[1] ベクトルのサイズを計算する\n");
    wprintf(L"[2] ベクトルにスカラーを掛ける\n");
    wprintf(L"\t二つのベクトル演算\n");
    wprintf(L"[3] 二つのベクトルをプラスする\n");
    wprintf(L"[4] 二つのベクトルのドット積\n");
    wprintf(L"[5] 二つのベクトルの外積\n");
    wprintf(L"[6] 別のベクトルにベクトルを射影する\n");
    wprintf(L"[7] 二つのベクトルからの平行四辺形の面積を計算する\n");
    wprintf(L"[0] 出る\n");
}

void vectorOperation(void)
{
    int choice, temp;
    int u, v;
    cls();
    printOperationMenu();
    choice = getInt(L"選んでいる機能: ");
    if (choice == 0)
        return;
    if (choice < 0 || choice > 7)
    {
        wprintf(L"選択無効 もう一度やり直してください\n");
        wprintf(L"続行するには任意のボタンを押してください。。。");
        getchar();
        return;
    }
    wprintf(L"\n");
    ShowAllVectors();
    wprintf(L"\n");
    if (choice == 1 || choice == 2)
    {
        u = getInt(L"ベクトルを選ぶ: ");
        if (!isVector(u))
        {
            wprintf(L"このベクトルはありません、 続行するには任意のボタンを押してください。。。");
            getchar();
            return;
        }
    }
    else
    {
        u = getInt(L"第1ベクトルを選ぶ: ");
        v = getInt(L"第2ベクトルを選ぶ: ");
        if (!(isVector(u) && isVector(v)))
        {
            wprintf(L"一方または両方のベクトルが存在しません、 続行するには任意のボタンを押してください。。。");
            getchar();
            return;
        }
    }

    wchar_t *format = calloc(10, sizeof(wchar_t));
    swprintf(format, 10, L"%%.%df", floatingPoint);
    switch (choice)
    {
    case 1:
        wprintf(L"ベクトル #%d　のサイズは ", u);
        wprintf(format, vectorSize(vector[u]));
        wprintf(L"\n");
        break;
    case 2:
        temp = getInt(L"持って掛けるスカラー量を入力してください: ");
        saveVectorToSlot((scalarMult(vector[u], temp)));
        break;
    case 3:
        saveVectorToSlot(addVector(vector[u], vector[v]));
        break;
    case 4:
        wprintf(L"ドット積は ");
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
        wprintf(L"面積は ", vectorSize(crossProduct(vector[u], vector[v])));
        wprintf(format, vectorSize(crossProduct(vector[u], vector[v])));
        wprintf(L" 平方ユニット\n");
        break;
    default:
        wprintf(L"Error 003: Default kicks in, function: vectorOperation\n");
    }
    wprintf(L"機能完了しました、 続行するには任意のボタンを押してください。。。");
    free(format);
    getchar();
}

void settingsMenu(void)
{
    int choice;
    wprintf(L"\n=====|設定|=====\n\n");
    wprintf(L"[1] 画面の色を変化する\n");
    wprintf(L"[2] 数値精度を設定する\n");
    wprintf(L"[0] 戻る\n");
    choice = getInt(L"選ぶ： ");
    switch (choice)
    {
    case 1:
        setColor();
        break;
    case 2:
        while (true)
        {
            floatingPoint = getInt(L"小数点以下の桁数 ： ");
            if (floatingPoint >= 0 && floatingPoint <= 6)
                break;
            else
                wprintf(L"桁数は0から6の間でなければなりません。もう一度やり直してください\n");
        }
        break;
    case 0:
        wprintf(L"続行するには任意のボタンを押してください。");
        getchar();
        break;
    default:
        wprintf(L"選択無効 もう一度やり直してください\n");
        wprintf(L"続行するには任意のボタンを押してください。");
        getchar();
        break;
    }
}

void fileMenu(void)
{
    int choice;
    wprintf(L"\n=====|ファイルメニュー|=====\n\n");
    wprintf(L"[1] インポート・ベクトル\n");
    wprintf(L"[2] エクスポート・ベクトル\n");
    wprintf(L"[0] 戻る\n");
    choice = getInt(L"選ぶ： ");
    switch (choice)
    {
    case 1:
        importVector();
        break;
    case 2:
        exportVector();
        break;
    case 0:
        wprintf(L"続行するには任意のボタンを押してください。");
        getchar();
        break;
    default:
        wprintf(L"選択無効 もう一度やり直してください\n");
        wprintf(L"続行するには任意のボタンを押してください。");
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
    col = getString(L"選ぶ色: ");
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
    slot = getInt(L"どのスロットでベクトルを入れますか？ : ");
    if (slot >= 0 && slot < VECTOR_ARRAY_SIZE)
    {
        if (vector[slot] != NULL)
        {
            if (!getConfirmation(L"このスロットはすでにベクトルがあります。 上書きしますか？ [Y/N]: "))
            {
                return;
            }
            free(vector[slot]);
        }
        float *u = malloc(sizeof(*u) * 3);
        char *buffer = getString(L"(i , j , k)でベクトルを入力してください: ");
        sscanf(buffer, "%f %f %f", &u[i], &u[j], &u[k]);
        vector[slot] = u;
        free(buffer);
    }
    else
    {
        wprintf(L"そのスロットはありません、続行するには任意のボタンを押してください。。。");
        getchar();
    }
}

const wchar_t *printvec(float *u)
{
    int d = floatingPoint;
    char *format = calloc(100, sizeof(*format));
    sprintf(format, "( %%.%df , %%.%df , %%.%df )", d, d, d);
    char *str = calloc(100, sizeof(*str));
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
    free(format);
    free(str);
    return wstr;
}

void ShowAllVectors(void)
{
    wchar_t *tmp;
    for (int m = 0; m < VECTOR_ARRAY_SIZE; m++)
    {
        if (vector[m] != NULL)
        {
            tmp = printvec(vector[m]);
            wprintf(L"ベクトル #%d : %s\n", m, tmp);
            free(tmp);
        }
    }
}

void saveVectorToSlot(float *u)
{
    int w;
    wchar_t *tmp = printvec(u);
    wprintf(L"結果のベクトルは %s\n", tmp);
    free(tmp);
    if (!getConfirmation(L"ベクトルを保存しますか？ [Y/N]: "))
    {
        return;
    }

    w = getInt(L"どこで保存しますか？ : ");
    if (w < 0 || w >= VECTOR_ARRAY_SIZE)
    {
        wprintf(L"こので存在できないで、インデックスが範囲外です。\n");
        saveVectorToSlot(u);
        return;
    }
    if (vector[w] != NULL)
    {
        if (!getConfirmation(L"このスロットはすでにベクトルがあります 上書きしますか？ [Y/N]: "))
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
    if (!getConfirmation(L"警告： このアクションはすべてのベクトルを削除します。 継続しますか? [Y/N]: "))
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
    wprintf(L"すべてのベクトルを削除しました、続行するには任意のボタンを押してください。。。");
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
    float a1, a2, a3;
    char *tmp;
    char filename[100];
    FILE *inputFile;
    tmp = getString(L"ファイル名を入力してください : ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    if ((inputFile = fopen(filename, "r")) == NULL)
    {
        wprintf(L"このファイルを開けることができないで、存在しない可能性があります。\n");
        wprintf(L"続行するには任意のボタンを押してください。。。");
        free(tmp);
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
    free(tmp);
    fclose(inputFile);
}

void exportVector(void)
{
    char *tmp;
    char filename[100];
    FILE *outputFile;
    tmp = getString(L"ファイル名を入力してください : ");
    sprintf(filename, "VectorSave/%s.txt", tmp);
    free(tmp);
    if ((outputFile = fopen(filename, "r")) != NULL)
    {
        if (!getConfirmation(L"このファイルはすでに存在します。 上書きしますか？ [Y/N]: "))
        {
            fclose(outputFile);
            return;
        }
    }

    outputFile = fopen(filename, "w");
    for (int c = 0; c < VECTOR_ARRAY_SIZE; c++)
    {
        if (vector[c] != NULL)
            fprintf(outputFile, "%d %f %f %f\n", c, vector[c][i], vector[c][j], vector[c][k]);
    }
    free(tmp);
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
        wprintf(L"入力エラー もう一度やり直してください。\n");
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    long n = strtol(buffer, &end, 10);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        wprintf(L"入力エラー もう一度やり直してください。\n");
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
        wprintf(L"入力エラー もう一度やり直してください。\n");
        return getInt(prompt);
    }
    return (int)n;
}

float getFloat(const wchar_t *prompt)
{
    double temp = getDouble(prompt);
    if (temp > FLT_MAX || temp < FLT_MIN)
    {
        wprintf(L"エラー : オーバーフロー。\n");
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
        wprintf(L"入力エラー もう一度やり直してください。\n");
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    double n = strtod(buffer, &end);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        wprintf(L"入力エラー もう一度やり直してください。\n");
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
        wprintf(L"エラー、もう一度やり直してください。\n");
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
        wprintf(L"RAMは十分ではありません プログラムを終了しています...\n");
        exit(EXIT_FAILURE);
    }
}

#else
#include <stdio.h>
int main(void)
{
    printf("Japanese version doesn't support in Linux!\n");
    return 0;
}
#endif