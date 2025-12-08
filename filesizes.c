#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#define MAX_LINE_LENGTH 255


char lista;
char line[MAX_LINE_LENGTH] = {0};
FILE *f;
char osv[MAX_LINE_LENGTH] = {0};
int xx;
int i;

void listdir(char *path, size_t size) {
    DIR *dir;
    FILE *q;
    struct dirent *entry;
    size_t len = strlen(path);

    if (!(dir = opendir(path))) {
        fprintf(stderr, "path not found: %s: %s\n", path, strerror(errno));
        return;
    }

//    puts(path);
    while ((entry = readdir(dir)) != NULL) {
        char *name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            if (!strcmp(name, ".") || !strcmp(name, ".."))
                continue;
            if (len + strlen(name) + 2 > size) {
              fprintf(stderr, "path too long: %s/%s\n", path, name);
            } else {
                path[len] = '/';
                strcpy(path + len + 1, name);
                listdir(path, size);
                path[len] = '\0';
            }
        } else {
            q=fopen("/storage/emulated/0/Documents/result.txt","ab");
            if (q) {
             fprintf(q,"%s/%s\n", path, name);
             fclose(q);
            }
        }
    }
    closedir(dir);
}


int main(void) {

 
    
    f=fopen("/storage/emulated/0/Documents/rootdir.txt","r");
    if (f) {
    fseek (f, 0, SEEK_SET);
    fgets(osv, MAX_LINE_LENGTH, f);
    fclose(f);
    }
    for(i=0;osv[i]!='\0';i++)
    {
//         printf("%i %c\n",line[i],line[i]);
     if(osv[i]==10)
     {
      osv[i] = 0;
     }
     if(osv[i]==13)
     {
      osv[i] = 0;
      }
    }
    f=fopen("/storage/emulated/0/Documents/result.txt","wb");
    if (f) {
   fclose(f);
    }
    printf("rootdir.txt Osveny : %s",osv); 
    listdir(osv, sizeof(osv));
    return 0;
}
