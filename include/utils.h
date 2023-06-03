#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define true 1
#define false 0

#define get_bit(b,n) {(b&(1<<n))>>n}
#define set_bit(b,n) {b|(1<<n)};

#define NO_IMP {fprintf(stderr,"NOT YET IMPLEMENTED !\n")}