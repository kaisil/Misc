#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE_MAX 512

char* appendString(char *inputString, char *inputKey);
void printCipher(char *label, char *inputString);

int main (int argc, char *argv[])
{
    char *inBuf = NULL; // input buffer
    char *keyString = NULL;
    char *plainTextString = NULL;
    char *cipherString = NULL;


    int i = 0; //iterators
    int j = 0;

    FILE * keyfp = NULL;
    FILE * plainTextfp = NULL;
    keyfp = fopen(argv[1], "r"); // Open both files
    plainTextfp = fopen(argv[2], "r");

    inBuf = malloc(SIZE_MAX * 2);
    keyString = malloc(SIZE_MAX * 2);
    plainTextString = malloc(SIZE_MAX * 2);
    cipherString = malloc(SIZE_MAX * 2);

    int keyflag = 0;
    while (fscanf(keyfp, "%s", inBuf) != EOF)
    {
        if (keyflag < 1)
        {
            strcpy(keyString, inBuf);
            keyflag ++;
        }
        else{
        strcat(keyString, inBuf); //Add the inbuf to our keystring
        }
    }

    int ptflag = 0;
    while (fscanf(plainTextfp, "%s", inBuf) != EOF)
    {
           if (ptflag < 1)
        {
            strcpy(plainTextString, inBuf);
            ptflag ++;
        }
        else {
        strcat(plainTextString, inBuf);  //Add the inbuf to our keystring
        }
    }

    /*Take alphabet only from keyString and convert all to lowercase*/
    for (i = 0; keyString[i] != '\0'; ++i)
    {
        while (!((keyString[i] >= 'a' && keyString[i] <= 'z') || (keyString[i] >= 'A' && keyString[i] <= 'Z') || keyString[i] == '\0'))
        {
            for (j = i; keyString[j] != '\0'; ++j)
            {
                keyString[j] = keyString[j+1];
            }
        }
    }

    for (i = 0;  keyString[i]; i++)
    {
        keyString[i] = tolower(keyString[i]);
    }

    char outKeyString[strlen(keyString)];
    strcpy(outKeyString, keyString); // Copy keystring to another var to use when we print output

    /*Take alphabet only from plainTextString and convert all to lowercase*/
    for (i = 0; plainTextString[i] != '\0'; ++i)
    {
        while (!((plainTextString[i] >= 'a' && plainTextString[i] <= 'z') || (plainTextString[i] >= 'A' && plainTextString[i] <= 'Z') || plainTextString[i] == '\0'))
        {
            for (j = i; plainTextString[j] != '\0'; ++j)
            {
                plainTextString[j] = plainTextString[j+1];
            }
        }
    }

    if (strlen(plainTextString) > 512) //Clip plaintext to 512 if it's too long
    {
        plainTextString[512] = '\0';

    }

    for (i = 0;  plainTextString[i]; ++i)
    {
        plainTextString[i] = tolower(plainTextString[i]);

    }

    while(strlen(plainTextString) > strlen(keyString))
    {
        char * temp = NULL;
        temp =  malloc((size_t)SIZE_MAX * 2);
        strcpy(temp, keyString );
        strcat(temp,keyString);
        keyString = temp;
    }

    if(strlen(plainTextString) < strlen(keyString))
    {
        plainTextString = appendString(plainTextString, keyString);
    }

/*
    /*encrypt plainTextString using keyString*/
    /*vigenere formula: C[i] = (p[i] + k[i mod klength]) mod 26 */

    int paddedCharCount = strlen(plainTextString);
    for(i = 0; i < paddedCharCount; ++i)
    {
       cipherString[i] = ((int)plainTextString[i]-97 + (int)keyString[i % strlen(keyString)]-97) % 26 + 97;

   }
    cipherString[i] = '\0';


    printCipher("Vigenere Key:", outKeyString);
    printf("\n");
    printCipher("Plaintext:", plainTextString);
    printf("\n");
    printCipher("Ciphertext:",cipherString);
    printf("\n");

    free(inBuf);
    //free(plainTextString);
    //free(cipherString);

    if(keyfp)fclose(keyfp);
    if(plainTextfp)fclose(plainTextfp);

    return 0;
}


char* appendString(char *inputString, char *inputKey)
{
    size_t PTLen = strlen(inputString);
    size_t KeyLen = strlen(inputKey);
    char * padString = "x";

    while(PTLen % KeyLen != 0 && PTLen < SIZE_MAX)
    {
        inputString = strcat(inputString, padString);
        PTLen = strlen(inputString);
    }
    return inputString;
}

void printCipher(char *label, char *inputString)
{
    int i = 0;
    int j = 0;
    int rowMax = 80; //only 80 chars per line
    int lastChar = 0; //save char index after line wrap
    int wrapLoc = 0; //location for next char wrap

    for (i = 0; inputString[i] != '\0'; ++i, ++wrapLoc)
    {
        if (wrapLoc >= rowMax) {
            for (j = strlen(inputString); j >= i; --j)
            {
                inputString[j + 1] = inputString[j];
                if (j == i)
                {
                    inputString[j] = '\n';
                    lastChar = j + 1;
                    break;
                }
            }
        wrapLoc = 0;
        i = i + 1;
        }
    }
    printf("\n\n%s\n\n%s", label, inputString);
}
