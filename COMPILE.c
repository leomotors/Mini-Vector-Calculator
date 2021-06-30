/**
 * * Project 「Vector Calculator」
 * * 総制作　@Leomotors
 * * Honor contributor @Teproanyx
 * 
 * * Compilation Helper
 * ? Note: Direct compilation works, this project use simple stuff.
 * ? This file is to make it more convenience and make program look simpler.
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
const char *SRC_FILES[] = {
    "VectorCalc", "VectorCalc_TH_Win", "VectorCalc_JP_Win"};

#else
const bool WINDOWS = 0;
const char *SRC_FILES[] = {
    "VectorCalc", "VectorCalc_TH", "VectorCalc_JP"};

#endif

int please_choose_lang(void);

int main(void)
{
    printf("Operating System (Family): %s\n", WINDOWS ? "Windows" : "Unix");
    printf("\nWelcome to Vector Calculator Compilation Assistant!\n");

    int user_lang = please_choose_lang();
    printf("\n");

    char toexec[100] = "";
    sprintf(toexec, "gcc ./sources/%s.c -o %s -lm",
            SRC_FILES[user_lang - 1], FILE_NAME);

    printf("Executing \"%s\"...\n", toexec);

    system(toexec);

    printf("\nDone! If the compilation is success, you can now run "
           "'Vector_Calculator' to enjoy the program!\n");
}

int please_choose_lang(void)
{
    printf("Please Choose Language to Compile\n");
    printf("[1] English\n[2] Thai\n[3] Japanese\n");
    int user_lang = getInt("Your Choice: ");

    if (user_lang > 3 || user_lang < 0)
    {
        printf("Invalid Choice!\n\n");
        return please_choose_lang();
    }
    return user_lang;
}