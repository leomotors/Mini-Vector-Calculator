/**
 * * Safe Input Module
 * * Original Work: @Teproanyx
 * * Customed for this Vector Calculator: @Leomotors
 */

#ifndef TEPROANYX_SAFE_INPUT
#define TEPROANYX_SAFE_INPUT

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_BUFFER 8

#ifndef SAFE_INPUT_LANGUAGE_FILE_IMPORTED
#include "SI_EN.h"
#endif

// * Function Prototype (Declaration) * //

long long getlong(const char *);
int getInt(const char *);
double getDouble(const char *);
char *getString(const char *);
void memoryError(const void *);

// * Function Definition * //

long getLong(const char *prompt)
{
    char *buffer = getString(prompt);
    if (buffer[0] == '\0')
    {
        free(buffer);
        printf(SI_INPUT_ERROR);
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    long n = strtol(buffer, &end, 10);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        printf(SI_INPUT_ERROR);
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
        printf(SI_INPUT_ERROR);
        return getInt(prompt);
    }
    return (int)n;
}

double getDouble(const char *prompt)
{
    char *buffer = getString(prompt);
    if (buffer[0] == '\0')
    {
        free(buffer);
        printf(SI_INPUT_ERROR);
        return getLong(prompt);
    }

    char *end = NULL;
    errno = 0;

    double n = strtod(buffer, &end);
    if (errno || *end != '\0')
    {
        free(buffer);
        fprintf(stderr, "Value conversion error\n");
        printf(SI_INPUT_ERROR);
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
        printf(SI_MEMORY_FULL);
        exit(EXIT_FAILURE);
    }
}

#endif
