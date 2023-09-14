# Only jump

## Progetto realizzato per il corso di Programmazione

## Clone
Il progetto utilizza i sottomoduli di git. È quindi necessario clonare la 
repository tramite il seguente comando.
```sh
$ git clone --recursive https://github.com/musianisamuele/project_00819.git
```
Se si è già clonata la repository si possono sempre aggiornare i sottomoduli 
tramite il comando:
```sh
$ git submodule init && git submodule update
```

## Music
Nel gioco è presente della musica, che però non è inclusa direttamente con git.
Essa va scaricata manualmente dalla apposita sezione su Github riguardante i 
binari.

## Build from source

Il progetto utilizza `cmake` come sistema di build. La compilazione dovrebbe
quindi essere triviale e necessitare solo dei seguenti comandi:
```sh
$ cd build
$ cmake .. $ make
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
$ pacman -S ncurses
```

## Comandi di gioco
Di seguito sono riportati i comandi predefiniti di gioco. Si noti che è sempre
possibile personalizzarli entrando nello specifico menù che si trova nelle
impostazioni.

- `s`: Muove il giocatore a sinistra
- `d`: Muove il giocatore a destra
- `a`: Salto a sinistra
- `f`: Salta a destra
- `w`: Sparo a sinistra
- `e`: Sparo a destra
- `m`: Abilità
- `ESC`: Mette in pausa il gioco
