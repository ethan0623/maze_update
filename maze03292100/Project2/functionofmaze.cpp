#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "maze.h"
using namespace std;


vector<vector<Cell>> cells;
    // 參數化構造函數，可進行初始化
Maze::Maze(int w, int h) : width(w), height(h) {
        //height 指的是迷宮的列數，vector<Cell>(width) 指的是每一列都有 width 個 Cell
        cells.resize(height, vector<Cell>(width));
        //srand 的 source code => void srand(unsigned int seed);
        //time(0) 的類型為 time_t，所以要先透過 static_cast<unsigned int>(time(0)) 轉成 unsigned int
        srand(static_cast<unsigned int>(time(0)));

        // 隨機生成迷宮
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cells[i][j].isWall = (rand() % 4 == 0); // 25% 機率是牆
                cells[i][j].isVisited = false;         // 初始化為未訪問
            }
        }

        // 設定起點和終點
        // 起點
        begin_x = rand() % height;
        begin_y = rand() % width;
        cells[begin_x][begin_y].isWall = false;
        // 終點
        // 確保起點與終點不在同一個位置
        do {
            finish_x = rand() % height;
            finish_y = rand() % height;
        } while (begin_x == finish_x && begin_y == finish_y);
        cells[finish_x][finish_y].isWall = false;




    }
    int Maze::getBeginX() const { return begin_x; }
    int Maze::getBeginY() const { return begin_y; }
    int Maze::getFinishX() const { return finish_x; }
    int Maze::getFinishY() const { return finish_y; }


    // 顯示迷宮
    // sf::RenderWindow& window 是 SFML 的窗口對象的引用，用於進行所有的繪圖操作
    void Maze::display(sf::RenderWindow& window, int player_x, int player_y) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                //創建一個長方形，大小為 20x20 像素，即為每個迷宮單元格的大小
                sf::RectangleShape rect(sf::Vector2f(20, 20));
                //將長方形放置在窗口中的正確位置
                rect.setPosition(j * 20, i * 20);
                // 這個判斷式是用來將牆壁畫成黑色的
                rect.setFillColor(cells[i][j].isWall ? sf::Color::Black : sf::Color::White);
                window.draw(rect);
            }
        }
        //繪製終點位置
        sf::RectangleShape finish(sf::Vector2f(15, 15));
        finish.setFillColor(sf::Color::Green);
        finish.setPosition(finish_y * 20 + 5, finish_x * 20 + 5);
        window.draw(finish);

        // 繪製玩家位置
        sf::CircleShape player(5); // 半徑為 10 的圓形，表示玩家
        player.setFillColor(sf::Color::Red); // 玩家顏色
        player.setPosition(player_y * 20 + 5, player_x * 20 + 5); // 計算玩家位置，顯示在格子中央
        window.draw(player); // 繪製玩家

    }

    bool Maze::player_move(int& player_x, int& player_y, int new_player_x, int new_player_y) {
        // 檢查新位置是否有效
        if (new_player_x < 0 || new_player_x >= height || new_player_y < 0 || new_player_y >= width || cells[new_player_x][new_player_y].isWall) {
            cout << "無法移動，碰到牆壁！" << endl;
            return false;
        }

        // 更新玩家位置
        player_x = new_player_x;
        player_y = new_player_y;
        cells[player_x][player_y].isVisited = true; // 標記為已訪問

        // 檢查是否到達終點
        if (player_x == finish_x && player_y == finish_y) {
            cout << "恭喜你成功到達終點！" << endl;
            return true;
        }
        return false;
    }
