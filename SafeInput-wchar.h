/**
 * * Safe Input Module wchar_t as prompt version
 * * Original Work: @Teproanyx
 * * Customed for this Vector Calculator: @Leomotors
 */

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#define INITIAL_BUFFER 8

// * Function Prototype (Declaration) * //

long long getlong(const wchar_t *);
int getInt(const wchar_t *);
double getDouble(const wchar_t *);
char *getString(const wchar_t *);
void memoryError(const void *);

// * Function Definition * //

long getLong(const wchar_t *prompt)
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

int getInt(const wchar_t *prompt)
{
    long n = getLong(prompt);
    if (n > INT_MAX || n < INT_MIN)
    {
        printf("Input error, please try again!\n");
        return getInt(prompt);
    }
    return (int)n;
}

double getDouble(const wchar_t *prompt)
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

char *getString(const wchar_t *prompt)
{
    size_t size = INITIAL_BUFFER;
    wprintf(L"%s", prompt);
    char *buffer = (char *)malloc((size + 1) * sizeof(*buffer));
    memoryError(buffer);
    if (fgets(buffer, size + 1, stdin) == NULL)
    {
        free(buffer);
        printf("Error, try again!\n");
        return getString(prompt);
    }
    while (buffer[strlen(buffer) - 1] != '\n')
    {
        char *subBuffer = (char *)malloc((size + 1) * sizeof(*subBuffer));
        memoryError(subBuffer);

        if (fgets(subBuffer, size + 1, stdin) == NULL)
        {
            free(buffer);
            free(subBuffer);
            printf("Read Error(WTF HOW), try again MTFKER!\n");
            return getString(prompt);
        }

        size *= 2;
        buffer = (char *)realloc(buffer, size + 1);
        memoryError(buffer);

        strncat(buffer, subBuffer, size / 2);
        free(subBuffer);
    }
    buffer[strlen(buffer) - 1] = '\0';
    buffer = (char *)realloc(buffer, strlen(buffer) + 1);
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
