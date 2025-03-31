#ifndef maze_H
#define maze_H
struct Cell {
    bool isWall;
    bool isVisited;
};

class Maze {
public:
    //vector<vector<Cell>> cells;
    int width, height, begin_x, begin_y, finish_x, finish_y;

    // 參數化構造函數，可進行初始化
    Maze(int w, int h);
    int getBeginX() const;
    int getBeginY() const;
    int getFinishX() const;
    int getFinishY() const;
    void display(sf::RenderWindow& window, int player_x, int player_y);
    bool player_move(int& player_x, int& player_y, int new_player_x, int new_player_y);
    bool DFS(int start_x, int start_y);
};

#endif // maze_H
