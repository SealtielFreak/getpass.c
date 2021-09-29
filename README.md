# getpass.c

## How to use it?
It is just a function that returns a string of characters without showing it on the screen

## Example
```C
#include <stdio.h>
#include "getpass.h"

#define LEN     16

int main() {
    printf("password: ");
    const char* pass = getpass('*', LEN);

    if(pass) {
        printf("\nYour password: %s", pass);
    } else {
        printf("Please enter a password");
    }

    return 0;
}
```

## References
```C
const char* getpass(char e, size_t size);
```

### Arguments
`e` for the character that you want to be printed on the screen, if you want it to be invisible use the macro `GHOST_PASS`

`size` it establishes the limit size of the user's input, if the established input is exceeded, it ends


# License
[WTFPL](http://www.wtfpl.net/)
