#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 200

/*pig latin program requirements:
-read in paragraph to be translated
-maintain capital letters in their respective word (Cat -> Atcay)
-break at first vowel of a word
-put leading  constonants at end of the word followed by 'ay' (frog -> ogfray)
-if first letter of a word is a vowel, put 'hay' at end of word (ant -> anthay)
*/

void intialize(char englishString[], char piglatinString[]);
int wordCount (char englishString[]);
int findFirstVowel(char words[]);
int isVowel(char i);
char* translate(int words, char englishString[]);

int main(int argc, char *argv[])
{

   char *inBuf = NULL;
   char englishString[MAX];
   char* piglatinString = malloc(50);

   int i = 0;
   int position = 0;
   int words;

   intialize(englishString, piglatinString);

   inBuf = malloc(MAX * sizeof(char));
   if (inBuf == NULL)
   {
       printf("malloc failed\n");
       return 1;
   }

   FILE  * ofp;
   ofp = fopen(argv[1], "r"); 

   fgets(englishString, MAX, ofp);

   words = wordCount(englishString);

   if(words >= 0)
   {
     piglatinString = translate(words, englishString);
   }

   printf("%s\n\n", englishString);
   printf("%s\n", piglatinString);

   free(inBuf);

   return 0;
}

void intialize(char englishString[], char piglatinString[]) // intialize char arrays w/ blank spaces
{
    int i = 0;

    for (i = 0; i < MAX; i++)
    {
        englishString[i] = piglatinString[i] = ' ';
        return;
    }
}

int wordCount (char englishString[]) // count number of words
{
    int j = 0;
    int words = 0;
    for (j = 0; j < MAX; j++)
    {
        if(englishString[j] == ' ' && englishString[j + 1] != ' '){
            words++;
        }
    }
    return (words);
}

int findFirstVowel(char word[])
{
  int i = 0;

  for(i = 0; i < strlen(word); i++)
  {
    if(isVowel(word[i])){
      return i;
    }
  }
  return -1;
}

int isVowel(char i)
{
  i = toupper((unsigned) i);
  if(i == 'A' || i ==  'E' || i == 'I' || i == 'O' || i == 'U')
      {
      return 1;
  }
  return 0;
}


char* wordToPiglatin(char* word)
{
    int caps = 0;
    char* output = malloc(500);
    int vp = findFirstVowel(word);
    if (isupper(word[0]))
    {
        word[0] = tolower(word[0]);
        caps = 1;
    }
    if ( vp == -1 )
    {
        return word;
    }
    else if ( vp == 0 )
    {
        strcpy (output, word);
        strcat (output, "hay");
        return output;
    }
    else
    {
        char* head  = malloc(500);
        strncpy(head, word, vp);
        char* tail  = malloc(500);
        strncpy(tail, word + vp, strlen(word) - vp );
        int len =  (strlen(word) - vp);
        tail[len] = '\0';
        head[vp] = '\0';
        strcpy (output, tail);
        strcat (output, head);
        strcat (output, "ay");
        output[strlen(tail) + strlen(head) + 2] = '\0';
        if (caps)
        {
            output[0] = toupper(output[0]);
        }
        return output;
    }
}

char* translate(int words, char englishString[])
{
    char* newWord = malloc(50);
    char* outputString = malloc(5000);
    outputString[0] = '\0';
    int start = -1;
    int i;
    int limit = strlen(englishString);

    for ( i=0; i < limit; ++i )
    {
        char ch = englishString[i];

        if ( isalpha(ch) )
        {
            if ( start == -1 ) start = i;
        }
        else
        {
            if ( start >= 0 )
            {

                strncpy(newWord, englishString + start, i - start);
                int len =  (i - start);
                newWord[len] = '\0';
                strcat(outputString, wordToPiglatin(newWord));
                start = -1;
            }

            size_t len = strlen(outputString);
            outputString[len] = ch;
            outputString [len + 1] = '\0';

        }
    }
    
    if ( start >= 0 )
    {
        char* newWord = malloc(500);
        strncpy(newWord, englishString, start);
        newWord[start] = '\0';
        strcat(outputString, newWord);
    }

    return outputString;
}
