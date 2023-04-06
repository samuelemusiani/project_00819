# HOW TO USE `logs` FUNCTIONS
With ncurses you cannot print on the screen, so if you want to debug you can 
include the library `logs.hpp`, that is in this directory: 
```
{PROJECT_DIR}/etc/logs/
```
You can call the 
`deb::debug(...)` function to print in the `logs.txt` file, in the same directory 
as the `./game` file. The function takes in input data that you want to print
in the logs and an identificator (default is `no_id`) so it's easier to read
the file.