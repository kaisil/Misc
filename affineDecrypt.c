#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nullCheck( ptr ); if( ptr == NULL ) { printf("\n\nFailed to allocate memory!! Issue on line %d! Closing program... \n", __LINE__); exit(EXIT_FAILURE); }

int calcInv(int a);
int main() {

char *cipherString = NULL;

//allocate memory and check if successful, arbitrary numbers chosen for memory size
cipherString = malloc(sizeof(256 + 1));
nullCheck(cipherString);

//hardcoded cipher string TODO accept user inputted ciphertext
cipherString = "jbdeaxeadzeixkxdfszkbzvazvfxmkvaxszkhxmvadsbzvircjzkxhduixkaxgabzvhzvocyvfavfxskxpvxehbrerobfdf";

int a;
int b;
int i;

for(a = 1; a <= 25; a++){
  if ( a % 2 != 0 && a != 13) // only operate when a is an odd number, and not 13
  {
    int length = strlen(cipherString);

	  char decryptionString[length];

    int aInverse = 0;
    aInverse = calcInv(a);

    for(b = 0; b <= 25; b++){ //b can be any value up to 26
      strncpy(decryptionString, cipherString, length + 1); //copy the cipher into decryptionString

      for (i = 0; i < strlen(decryptionString); i++) //run for the entire length of the cipher text
      {
          decryptionString[i] = (aInverse * ((cipherString[i] -'a') - b)) % 26;

              if (decryptionString[i] < 0) //if decryptionString comes back negative...
              {
                 decryptionString[i] = (decryptionString[i] + 26); //make it positive
               }

        decryptionString[i]  += 'a'; //convert back to chars
      }

    printf("\n%s \t a = %d, b = %d \n", decryptionString, a, b);
    }
  }
}

return 0;
}

int calcInv(int a)
{
  int mi = 0;
  while (mi <= 26) //make sure it is in range
  {
    if ((a * mi) % 26 == 1) //can only use a value as inverse if the gcd is 1
    {
      return mi;
    }
    mi++;
  }
}
