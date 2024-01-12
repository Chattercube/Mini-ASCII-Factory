#define _XOPEN_SOURCE_EXTENDED
#include <string>
#include <ncursesw/curses.h>
#include <codecvt>
#include <stddef.h>
#include <iostream>
#include <fstream>


int main(){


    std::wstring line;
    std::wifstream myfile("widechar.txt");
    myfile.imbue(std::locale(myfile.getloc(), new std::codecvt_utf8<wchar_t>));
    

    initscr();
    myfile >> line;
    // std::wcout << line << std::endl;
    
    addnwstr(line.c_str(),10);

    getch();
    
    myfile >> line;
    
    addnwstr(line.c_str(),10);

    getch();


    myfile.close();
    endwin();
    return 0;
    
}