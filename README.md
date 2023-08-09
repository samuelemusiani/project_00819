# Jump king

## Progetto realizzato per il corso di Programmazione

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
