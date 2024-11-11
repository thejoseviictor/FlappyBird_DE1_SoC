// Faz as chamadas das funções Assembly do VGA

#ifndef VGA_H
#define VGA_H

// Definindo as Cores:
#define COLOR_RED 0x07
#define COLOR_GREEN 0x38
#define COLOR_BLUE 0x1C0
#define COLOR_YELLOW 0x3F
#define COLOR_CYAN 0x1F8
#define COLOR_MAGENTA 0x1C7
#define COLOR_WHITE 0x1FF
#define COLOR_BLACK 0x00
#define COLOR_SILVER 0x16D
#define COLOR_GRAY 0xDB

// Instruções do VGA:
extern void physical_to_virtual();                                                         // Syscalls "open" e "mmap2"
extern void unmap_memory();                                                                // Syscall "munmap"
extern void background_color(int color);                                                   // Instrução WBR;
extern void background_drawing(int row, int column, int color);                            // Instrução WBM;
extern void background_block_erase(int row, int column);                                   // Instrução WBM;
extern void draw_polygon(int address, int row, int column, int size, int color, int type); // Instrução DP;
extern void set_sprite(int address, int offset, int row, int column, int sp);              // Instrução WBR;
extern void buffer_overflow();                                                             // Verifica o registrador "WRFULL"

#endif // VGA_H
