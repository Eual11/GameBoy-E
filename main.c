#include "bus.h"
#include "cart.h"
#include "cpu.h"
#include "emu.h"
#include "ppu.h"

int main(int argc, char **argv){
    cart_load("roms/tetris.gb");


    return 0;
}