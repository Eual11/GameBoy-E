#include "cart.h"

typedef struct
{
    char filename[1024]; //filename;
    uint64_t rom_size;
    uint8_t *rom_data; 
    rom_header *header;
} cart_context;

static cart_context ctx;
static const char *rom_type[] =
{
    "ROM ONLY", 
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0X4 ??",
    "MBC2",
    "MBC2+BATTERY",
    "0x7 ??",
    "MBC2+BATTERY",
    "ROM+RAM+BATTERY",
    "0x0A ??",
    "MMM01", 
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0X0E ??",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY",
    "MBC3",
    "MBC3+RAM",
    "MBC3+RAM+BATTERY",
    "0x14 ??",
    "0x15 ??",
    "0x16 ??",
    "0x17 ??",
    "0x18 ??",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0X1F ??",
    "MBC6",
    "0x21 ??",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    "POCKET CAMERA",
    "BANDAI TAMA5",
    "HuC3",
    "HuC1+RAM+BATTERY"

};

void get_rom_type(uint8_t code)
{
    if(code <0xFC)
    {
        printf("ROM TYPE: %s\n",rom_type[code]);
    }
    else
    {
        printf("Unmarked Rom type\n");
    }

    return;
}


bool cart_load(char *rom_name)
{
    FILE *fptr = fopen(rom_name,"r");
    if(!fptr)
    {
        fprintf(stderr,"coulnd't load rom %s \n",rom_name);
        return false;
    }
    printf("Emulator Running with %s file\n", rom_name);
    printf("ROM OPENED \n");
    fseek(fptr,0,SEEK_END);
    ctx.rom_size = ftell(fptr);
    rewind(fptr);
    ctx.rom_data = malloc(ctx.rom_size);
   
    fread(ctx.rom_data,sizeof(*ctx.rom_data),ctx.rom_size,fptr);
    ctx.header = malloc(sizeof(rom_header));
    ctx.header->rom_size = ctx.rom_data[0x148];
    ctx.header->ram_size = ctx.rom_data[0x149];
    ctx.header->dest_code = ctx.rom_data[0x14A];
    ctx.header->lic_code = ctx.rom_data[0x14B];
    ctx.header->version = ctx.rom_data[0X14C];
    ctx.header->checksum = ctx.rom_data[0x14D];
    ctx.header->sgb_flag = ctx.rom_data[0x146];
    ctx.header->rom_type = ctx.rom_data[0x147];
    ctx.header->global_checksum = (ctx.rom_data[0x14E]<<8)|ctx.rom_data[0x14F];
    ctx.header->new_lic_code = (ctx.rom_data[0x144]<<8)|ctx.rom_data[0x145];

    //entry point
    for(uint16_t i=0x100; i <0x104;i++)
    {
        ctx.header->entry_point[i] = ctx.rom_data[i];
    }
    //title
    for(int i=0; i < 16; i++)
    {
        ctx.header->title[i] = ctx.rom_data[i+308];
    }
    //logo
    for(int i=0; i <0x30;i++)
    {
        ctx.header->entry_point[i] = ctx.rom_data[i+0x104];
    }

    printf("ROM TITLE: %s\n", ctx.header->title);
    printf("ROM SIZE: %dkb\n", (32<<ctx.header->rom_size));
    get_rom_type(ctx.header->rom_type);
    printf("RAM SIZE %dkb\n ",ctx.header->ram_size*8);
    printf("%s\n", (ctx.header->sgb_flag==0x3)?"SGBA": "NSGBA");
    printf("Version: %d\n", ctx.header->version);
    uint16_t x;
    for(uint16_t addr =0x134; addr<=0x14c; addr++)
    {
        x = x-ctx.rom_data[addr]-1;
    }
    printf("CHECKSUM: %s \n", (x&0xFF)?"PASSED":"FAILED" );

    return true;

}
