@echo off
echo Finding flags...
> temp_flags.txt (
    for /r %i in (*flag.txt .flag* .flag flag user.txt) do @type "%i" 2>NUL
)
powershell -Command "Get-ChildItem -Recurse -Include *flag.txt,.flag*,.flag,flag,user.txt | ForEach-Object { Get-Content $_.FullName } 2>$null" >> temp_flags.txt
powershell -Command "Select-String -Path * -Pattern 'THM{' -Recurse -CaseSensitive" >> temp_flags.txt 2>NUL

if exist temp_flags.txt (
    for /f %%i in (temp_flags.txt) do (
        echo All flags Found
        goto :showflags
    )
    echo No flags found
)

:showflags
echo Here are your flags.
type temp_flags.txt
