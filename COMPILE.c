/**
 * * Project 「Vector Calculator」
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 * 
 * * Compilation Assistant
 * 
 * ? Note: Direct compilation also works, this project use simple single source code.
 * ? This file is to make it more convenience to choose language 
 * ? and make program look simpler by hiding junks.
 */

#include "SafeInput/SafeInput.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// * Static Data

const char *SRC_FOLDER = "sources";
const char *FILE_NAME = "Vector_Calculator";

#if defined(_WIN32)
const bool WINDOWS = 1;
const char SLASH = '\\';

#else
const bool WINDOWS = 0;
const char SLASH = '/';

#endif

const char *SRC_FILES[] = {"EN", "TH", "JP"};

int menu_options(void);

int main(void)
{
    printf("Your Operating System (Family): %s\n", WINDOWS ? "Windows" : "Unix");
    printf("\nWelcome to Vector Calculator Compilation Assistant!\n");

    int user_lang = menu_options();
    printf("\n");

    char toexec[100] = "";
    sprintf(toexec, "gcc ./sources/%s.c -o %s -lm",
            SRC_FILES[user_lang - 1], FILE_NAME);

    printf("Executing \"%s\"...\n", toexec);

    system(toexec);

    printf("\nDone! Starting program...\n");

    sprintf(toexec, ".%c%s", SLASH, FILE_NAME);
    system(toexec);

    printf("\n[COMPILATION ASSISTANT FEEDBACK] Program executed, "
           "The program should have show up, otherwise there might be some problem.\n");
}

int menu_options(void)
{
    if (WINDOWS)
    {
        printf("Your language is automatically set to English because that is the only option you have in this OS\n");
        printf("Note: From Build 282 (Version 4.2+), Thai and Japanese on Windows have been deprecated\n");
        printf("To use it, please use previous version (4.1 Recommended)");
        return 1;
    }

    printf("Please Choose Your Options\n");
    printf("[1] Compile & Run English Version\n"
           "[2] Compile & Run Thai Version\n"
           "[3] Compile & Run Japanese Version\n");

    int user_lang = getInt("Your Choice: ");

    if (user_lang > 3 || user_lang < 0)
    {
        printf("Invalid Choice!\n\n");
        return menu_options();
    }

    return user_lang;
}