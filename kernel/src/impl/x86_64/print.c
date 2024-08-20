#include "print.h"

#define videoMemory_address 0xb8000
#define NUM_COLS 80
#define NUM_ROWS 25

struct Char
{
    uint8_t letter;
    uint8_t color;
};

struct Char* buffer = (struct Char*)videoMemory_address;
size_t col = 0;
size_t row = 0;
uint8_t tkernColor = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row)
{
    struct Char empty = (struct Char)
    {
        letter: ' ',
        color: tkernColor
    };
    
    for (size_t x = 0; x < NUM_COLS; x++)
    {
        buffer[x + NUM_COLS * row] = empty;
    }
}

void print_clear()
{
    for (size_t y = 0; y < NUM_ROWS; y++)
    {
        clear_row(y);
    }
}

void print_newLine()
{
    col = 0;
    if(row < NUM_ROWS -1)
    {
        row++;
        return;
    }

    for(size_t row = 0; row < NUM_ROWS - 1; row++)
    {
        for(size_t col = 0; col < NUM_COLS; col++)
        {
            struct Char letter = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row-1)] = letter;
        }
    }

    clear_row(NUM_ROWS - 1);
}

void print_char(char letter)
{
    if(letter == '\n')
    {
        print_newLine();
        return;
    }

    if(col > NUM_COLS)
        print_newLine();

    buffer[col + NUM_COLS * row] = (struct Char)
    {
        letter: (uint8_t) letter,
        color: tkernColor
    };
    
    col++;
}

void print_str(char* string)
{
    size_t i = -1;
    while((uint8_t)string[++i] != '\0')
    {
        print_char((uint8_t)string[i]);
    }
}

void print_set_color(uint8_t color, uint8_t background)
{
    tkernColor = color | background << 4;
}