#ifndef GETPASS_H
#define GETPASS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#define GHOST_PASS      ' '

#ifdef __cplusplus
extern "C"
#endif
const char* getpass(char e, size_t size);

#endif // GETPASS_H
