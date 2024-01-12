#define _XOPEN_SOURCE_EXTENDED
#include <string>
#include <ncursesw/curses.h>
#include <stddef.h>
#include "block_sprite.h"

int main(){

    initscr();
    resizeterm(125, 250);
    refresh();
    box(stdscr,0, 0);

    int tra_r = 4;
    int lat_r = 3;
    int lat_c = 7;

    int offset_r = 30;
    int offset_c = 125;

    BlockSprite block = BlockSprite("block3.def");

   
    int ch = 0;
    do{

        wclear(stdscr);

        

        for(int z = 0; z < 20; z++){
            for(int x = z-21; x < 21-z; x++){
                for(int y = z-21; y < 21-z; y++){

                    for(int i = 0; i < block.getRowSize(); i++){
                        for(int j = 0; j < block.getColSize(); j++){
                            if(block.getAlphaAt(i, j) != '1') continue;
                            mvwaddch(stdscr, lat_r * x + lat_r * y - tra_r * z + offset_r + i, lat_c * x - lat_c * y + offset_c + j, block.getTexAt(i, j));
                        }
                    }
                }
            }
        }
        mvwaddwstr(stdscr, 5, 5, L"█");
        ch = getch();
        
        switch (ch) {

            case 'w':
                offset_r += lat_r;
                offset_c -= lat_c;
                break;

            case 's':
                offset_r -= lat_r;
                offset_c += lat_c;
                break;

            case 'a':
                offset_r += lat_r;
                offset_c += lat_c;
                break;
            
            case 'd':
                offset_r -= lat_r;
                offset_c -= lat_c;
                break;

            default:
                break;
        }
    }while(ch != 'q');

    endwin();
    return 0;
}