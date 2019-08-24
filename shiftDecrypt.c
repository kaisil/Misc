#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nullCheck( ptr ); if( ptr == NULL ) { printf("\n\nFailed to allocate memory!! Issue on line %d! Closing program... \n", __LINE__); exit(EXIT_FAILURE); }

int main() {

char *cipherString = NULL;

//allocate memory and check if successful, arbitrary numbers chosen for memory size
cipherString = malloc(sizeof(256 + 1));
nullCheck(cipherString);

//get string from user
printf("Please enter string to decrypt:\n");
fgets(cipherString, (256 + 1), stdin);



//manually terminate the string after the last letter
if ((strlen(cipherString) > 0) && (cipherString[strlen (cipherString - 1)] != '\n')){
          cipherString[strlen (cipherString) - 1] = '\0';
    }


int shift = 0;
int j = 0;
char temp;

for(shift = 0; shift < 26; shift++)
{
  for(j = 0; j < strlen(cipherString); j++)
  {
    //temp is used to adjust a single letter at a time
    temp = cipherString[j];

    if (temp >= 'a' && temp <= 'z')
      {
        temp += 1;
        if (temp > 'z')
        {
            //allow temp to wrap back around to the beginning of the alphabet
            temp = temp - 'z' + 'a' - 1;
        }
          //put the adjusted letter back into its original spot
          cipherString[j] = temp;
        }

   }
   printf("Shifted by %d: %s\n\n", shift + 1, cipherString);
}

return 0;
}