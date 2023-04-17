# pipex_final
This project will let you discover in detail a UNIX mechanism that you already know by using it in your program.


The program will be executed as follows: <br>
./pipex file1 cmd1 cmd2 file2

It must take 4 arguments: <br>
• file1 and file2 are file names. <br>
• cmd1 and cmd2 are shell commands with their parameters. <br>

It must behave exactly the same as the shell command below: <br>
$> < file1 cmd1 | cmd2 > file2 <br>

Examples <br>
$> ./pipex infile "ls -l" "wc -l" outfile <br>
Should behave like: < infile ls -l | wc -l > outfile <br>
$> ./pipex infile "grep a1" "wc -w" outfile <br>
Should behave like: < infile grep a1 | wc -w > outfile <br>

Bonus part <br>
• Handle multiple pipes. <br>
This: <br>
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2 <br>
Should behave like: <br>
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2 <br>
• Support « and » when the first parameter is "here_doc". <br>
This: <br>
$> ./pipex here_doc LIMITER cmd cmd1 file <br>
Should behave like: <br>
cmd << LIMITER | cmd1 >> file <br>
