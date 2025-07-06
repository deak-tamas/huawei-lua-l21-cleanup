#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 255

char filt[300];
char pad[300];
char line2x[500];
char sor1[500];
char sor2[500];
char line1x[500];
char pp[500];
int i;
FILE *f;

char* clrcrlf(char *line)
{
       for(i=0;line[i]!='\0';i++)
         {
//         printf("%i %c\n",line[i],line[i]);
         if(line[i]==10)
          {
          line[i] = 0;
         }
         if(line[i]==13)
          {
          line[i] = 0;
         }
        }
 return(line);
}


int main (void) {
printf("movefoto.txt Filter: ");
scanf("%s",filt);
if (strlen(filt)>2) {
f=fopen("/storage/emulated/0/Documents/movefoto.txt","rb");
  if (f)
  {
   fseek (f, 0, SEEK_SET);
   while (!feof(f)) {

   fgets(sor1, MAX_LINE_LENGTH, f);
   fgets(sor2, MAX_LINE_LENGTH, f);

   strcpy(line1x,clrcrlf(sor1));
   strcpy(line2x,clrcrlf(sor2));
   strcpy(pad,"mv  ");
   strcat(pad,line1x);
   strcat(pad,"*");
   strcat(pad,filt);
   strcat(pad,"* ");
   strcat(pad,sor2);
   strcpy(pp,"mkdir  ");
   strcat(pp,sor2);
   printf("\n%s\n",pp);
   system(pp);
   printf("\n%s\n",pad);
   system (pad);

   }

   fclose(f);
   printf("\nRemelhetoleg kesz\n");
 }
 else
 {
  printf("Gyik van");
 }
}
else
{
	printf("3hossz");
}
}
