#include "REXSpeeder.h"
#include <iostream>
#include <ncursesw/curses.h>


int main(){

    RexImage cat("cat.rxp");

    initscr();

    // for(int i = 0; i < 64; i++){
    //     init_color(i, i * 1000 / 64, 1000, 1000);
    // }

    start_color();
    endwin();

    

    std::cout << cat.height << " " << cat.width << std::endl;
    std::cout << COLORS << " " << COLOR_PAIRS << " " << COLORS << std::endl;
    return 0;

    




}