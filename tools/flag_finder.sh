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
