#pragma once
#include "utils.h"

uint8_t bus_read(uint16_t addr);
void bus_write(uint16_t addr, uint8_t val);