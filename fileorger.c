#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH 1024

void copy_until_underscore(char *dest, const char *src) {
    int i = 0;

    // Loop through the source until we hit '_', the end of string '\0', 
    // or a buffer limit (optional but recommended)
    while (src[i] != '_' && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    // Crucial: Null-terminate the destination string
    dest[i] = '\0';
}

void list_directory(const char *path, const char *li, const char *ba) {
    DIR *dir = opendir(path);
    char result[255];
    char cmd[255];
    char pad1[255];
    char pad2[255];

    if (dir == NULL) {
        printf("\n--- Could not open directory: %s ---\n", path);
        return;
    }

    printf("\n--- Contents of '%s' ---\n", path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        if (strchr(entry->d_name, ' ') == NULL)	{	
//            printf("  %s\n", entry->d_name);
        copy_until_underscore(result,entry->d_name);
        if (strlen(result)>2) {
                strcpy(cmd,"mkdir ");
		strcpy(pad1,li);
		strcat(pad1,"/");
		strcat(pad1,result);
		strcat(cmd,pad1);
		printf("%s\n",cmd);
		strcpy(cmd,"mv -v ");
		strcpy(pad2,path);
		strcat(pad2,"/");
		strcat(pad2,entry->d_name);
		strcat(cmd,pad1);
		strcat(cmd," ");
		strcat(cmd,pad2);
		printf("%s\n",cmd);

	}	
	}
	}	
    }
    closedir(dir);
}

int main() {
    char base_path[512];
    char line[512];
    char full_path[MAX_PATH];
    char res[255];

    FILE *fp = fopen("/storage/emulated/0/Documents/fileorg.txt", "r");

    if (!fp) {
        perror("Error opening oooo.txt");
        return 1;
    }

    // Read directory prefix from stdin
    printf("Enter the base directory path: ");
    if (scanf("%511s", base_path) != 1) return 1;

    // Process each line in oooo.txt
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character from fgets result
        line[strcspn(line, "\r\n")] = 0;

        if (strlen(line) == 0) continue;

        // Concatenate base path and line
        // Assuming base_path ends with '/' or add one if missing
        snprintf(full_path, sizeof(full_path), "%s/%s", line, base_path);

        list_directory(full_path, line,base_path);
    }

    fclose(fp);
    return 0;
}
