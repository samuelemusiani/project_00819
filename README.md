# Jump king

## Progetto realizzato per il corso di Programmazione

## Clone
As this project use submodules, in order to clone the full repo you must run:
```sh
$ git clone --recursive https://github.com/musianisamuele/project_00819.git
```

## Music
In order hear the music in game we have to download the file from the binaries
section on Github and place it in the same directory as the **JumpKing** 
executable.

## Build from source

Il progetto utilizza `cmake` come sistema di build. La compilazione dovrebbe
quindi essere triviale e necessitare solo sei comandi seguenti seguiti nella
directory `build/`:
```sh
$ cmake ..
$ make
```
Il progetto fa un uso estensivo della libraria `ncurses`, è perciò necessario
installarla con il metodo che si preferisce:

### MacOS

```sh
$ brew install ncurses
```

### Debian

```sh
$ apt install ncurses-dev
```

### Arch

```sh
$ Arch pacman -S ncurses
```
