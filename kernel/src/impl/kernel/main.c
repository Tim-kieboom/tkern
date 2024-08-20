#include "print.h"

void startup()
{
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("tkern_64 is up!!");
}

void kernel_main()
{
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    
}