# To run the shell:

1. Run the command `make`
2. Run `./a.out`
3. To exit from the shell, use the command `quit`

# Commands implemented:

# 1. cd:
Changes directory to the directory specified, throws an error if the directory does not exist.<br>
Variations implemented are:<br>
<code>cd<br>
cd ..<br>
cd .<br>
cd ~<br>
cd [directory]<br>
cd - </code>(this changes into the previous working directory)


# 2. pwd :
Displays the name of the present working directory.

# 3. echo:
Prints the specified message on the terminal.

# 4. ls: 
Lists the contents of the directory.<br>
Variations implemented are:<br>
<code>ls<br>
ls .<br>
ls ..<br>
ls -l<br>
ls -a<br>
ls -al<br>
ls -la<br>
ls [directory]<br>
ls ~</code>
	

# 5. background :
Runs a process specified by & in background.
		

# 6. foreground:
Runs a process in foreground.
		

# 7. pinfo:
Prints the process information of process with specified pid, given an argument `pid`.<br>
Prints the process information of current shell with no arguments

# 8. environment variables:
setenv : to set the environment variable to a given value
<br>unsetenv : to destroy the variable

# 9. bg :
Changes a stopped background job to a running background job

# 10. fg :
Brings a running or a stopped background job with given job number to foreground

# 11. jobs :
Prints a list of all existing background processes.

# 12. kjobs :
Takes the job id of a running job and sends a signal value to that process.
	
# 13. overkill :
Kills all background processes at once.

# 13. Piping with redirection:
One or more commands can be piped. Pipe can be combined with redirection.

# 14.Redirection:
Output can be redirected to another file and input can be taken from a given file.

# Additional features:
`ctrl+C` : Sends SIGINT to the foreground processes of the shell.
<br>`ctrl+Z` : Sends SIGINT and SIGTSTP to foreground process and makes it background process.
  
