![mandel](file.png)
# mandel

## Dependancies:
```
sudo apt install -y plotutils libplot-dev
```
## Build commands:
```
gcc -O2 -pipe -c mandel.c
gcc -o mandel mandel.o -lplot
```
## Usage:
```
./mandel > file.png
```
