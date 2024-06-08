#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(){
	printf("Finding flags...\n");
    system("find / -name \"*flag.txt\" -o -name \".flag*\" -exec cat {} \\; 2>/dev/null > temp_flags.txt");
    system("find / -name \".flag\" -o -name \"flag\" -exec cat {} \\; 2>/dev/null >> temp_flags.txt");
    system("find / -name \"user.txt\" -exec cat {} \\; 2>/dev/null >> temp_flags.txt");
    system("grep -r \"THM{\" / >> temp_flags.txt 2>/dev/null");
    FILE *flagsFile = fopen("temp_flags.txt", "r");
    if (flagsFile) {
        fseek(flagsFile, 0, SEEK_END);
        long fileSize = ftell(flagsFile);
        fclose(flagsFile);

        if (fileSize > 0) {
            printf("All flags Found\n");
        } else {
            printf("No flags found\n");
        }
    } else {
        printf("Error opening temp_flags.txt\n");
    }
    printf("Here is your flags.\n");
    system("cat temp_flags.txt");
}
