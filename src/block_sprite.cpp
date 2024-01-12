#include "block_sprite.h"
#include <fstream>
#include <string>

// class BlockSprite {

// private:
//     int r_size;
//     int c_size;

//     char **alpha;
//     char **tex;

// public:
//     int getRowSize();
//     int getColSize();
//     char **getAlpha();
//     char **getTex();

//     char getAlphaAt(int r, int c);
//     char getTexAt(int r, int c);

//     BlockSprite(std::string filename);
// };

int BlockSprite::getRowSize() { return r_size; }

int BlockSprite::getColSize() { return c_size; }

char **BlockSprite::getAlpha() { return alpha; }

char **BlockSprite::getTex() { return tex; }

char BlockSprite::getAlphaAt(int r, int c) { return alpha[r][c]; }

char BlockSprite::getTexAt(int r, int c) { return tex[r][c]; }

BlockSprite::BlockSprite(std::string filename) {

    std::string line;
    std::ifstream def_file(filename);

    if (def_file.is_open()) {

        def_file >> line;

        if (line != "type0") {
            return;
        }

        std::string _r, _c;

        def_file >> _r >> _c;
        r_size = stoi(_r);
        c_size = stoi(_c);

        alpha = new char *[r_size];
        tex = new char *[r_size];

        for (int i = 0; i < r_size; i++) {
            alpha[i] = new char[c_size];
            tex[i] = new char[c_size];
        }

        for (int i = 0; i < r_size; i++) {

            std::getline(def_file,line);

            for (int j = 0; j < c_size; j++) {
                alpha[i][j] = line[j];
            }
        }

        for (int i = 0; i < r_size; i++) {

            std::getline(def_file,line);

            for (int j = 0; j < c_size; j++) {
                tex[i][j] = line[j];
            }
        }
    }

    def_file.close();
}
