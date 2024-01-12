#include <fstream>
#include <string>

class BlockSprite {

  private:
	int r_size;
	int c_size;

	char **alpha;
	char **tex;

  public:
	int getRowSize();
	int getColSize();
	char **getAlpha();
	char **getTex();

	char getAlphaAt(int r, int c);
	char getTexAt(int r, int c);
    
	BlockSprite(std::string filename);
};