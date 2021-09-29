#include "getpass.h"


#if defined(__MINGW32__) || defined(__MINGW64__)

#include <conio.h>

#define ENTER       13
#define BREAK       8
#define TABULATE    9

#elif defined(_MSC_VER)

#define ENTER       13
#define BREAK       8
#define TABULATE    9

#define getch() _getch()

#elif defined(__GNUC__) || defined(__clang__) || defined(__CYGWIN__)

#include <termios.h>
#include <stdio.h>

#define ENTER       10
#define BREAK       127
#define TABULATE    9

static struct termios old, new;

void TERM_begin(int echo) {
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &new);
}

void TERM_end(void) {
    tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) {
    char ch;

    TERM_begin(echo);
    ch = getchar();
    TERM_end();

    return ch;
}

int getch(void) {
    return (int) getch_(0);
}
#else

#define ENTER       0
#define BREAK       0
#define TABULATE    0

#define getch() getchar()

#endif

const char *getpass(char e, size_t size) {
    char *pass = NULL;
    size_t i;

    pass = calloc(sizeof(char), size);
    if (!pass) {
        return NULL;
    }

    memset(pass, 0, size);

    for (i = 0; i < size; i++) {
        int c = getch();

        if (c == '\r' || c == EOF || c == ENTER || c == BREAK || c == TABULATE) {
            break;
        }

        if(!(c == ENTER || c == BREAK || c == TABULATE)) {
            if (e != GHOST_PASS) {
                printf("%c", e);
            }

            pass[i] = (char) c;
        }
    }

    pass[i] = '\0';

    if(strlen(pass) > 0) {
        return (const char *) pass;
    }

    return NULL;
}