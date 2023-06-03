#pragma once 
#include "utils.h"

typedef struct 
{
    uint8_t entry_point[0x4]; //the entry point of any gb program it is often filled with nop or jmp instructiosn
    uint8_t logo[0x30]; //this stores the nintendo logo
    uint8_t sgb_flag; //super gameboy flag
    uint8_t rom_size; //the size of the rom
    uint8_t ram_size; //the size of the ram. 0 if doesn't have any ram
    uint8_t dest_code; //destenation code
    uint8_t lic_code;  // old liceenxe code
    uint8_t version; //version
    uint8_t checksum; //checksum
    uint8_t rom_type; //the rom type, this is notable in the mapper
    uint16_t new_lic_code; //the new licensee code
    uint16_t global_checksum; //global checksum
    char title[16]; //this crossponds to the game title written in upper case

}rom_header;

bool cart_load(char *rom_name);
uint8_t cart_read(uint16_t addr);
void cart_write(uint16_t addr, uint8_t value);
