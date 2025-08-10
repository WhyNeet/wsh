# W-Shell
A very simple shell I wrote in C to learn the language.
It can:
- Run binary files.
```bash
echo hello world
# output: hello world
```
- Execute built-in commands (cd, pwd, exit).
```bash
cd /this/probably/works
pwd
# output: /this/probably/works
```
- Redirect standard output to a file.
```bash
echo hello world > hello.txt
cat hello.txt
# output: hello world
```