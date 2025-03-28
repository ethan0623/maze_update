#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Cell {
    bool isWall;
    bool isVisited;
};

class Maze {
public:
    vector<vector<Cell>> cells;
    int width, height;

    // 參數化構造函數，可進行初始化
    Maze(int w, int h) : width(w), height(h) {
        //height 指的是迷宮的列數，vector<Cell>(width) 指的是每一列都有 width 個 Cell
        cells.resize(height, vector<Cell>(width));
        srand(static_cast<unsigned int>(time(0)));

        // 隨機生成迷宮
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cells[i][j].isWall = (rand() % 4 == 0); // 25% 機率是牆
                cells[i][j].isVisited = false;         // 初始化為未訪問
            }
        }

        // 設定起點和終點
        cells[0][0].isWall = false;                // 起點
        cells[height - 1][width - 1].isWall = false; // 終點
    }

    // 顯示迷宮
    void display(sf::RenderWindow& window, int player_x, int player_y) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                sf::RectangleShape rect(sf::Vector2f(20, 20));
                rect.setPosition(j * 20, i * 20);
                rect.setFillColor(cells[i][j].isWall ? sf::Color::Black : sf::Color::White);
                window.draw(rect);
            }
        }

        // 繪製玩家位置
        sf::CircleShape player(5); // 半徑為 10 的圓形，表示玩家
        player.setFillColor(sf::Color::Red); // 玩家顏色
        player.setPosition(player_y * 20 + 5, player_x * 20 + 5); // 計算玩家位置，顯示在格子中央
        window.draw(player); // 繪製玩家
    }

    bool player_move(int& player_x, int& player_y, int new_player_x, int new_player_y) {
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
        if (player_x == height - 1 && player_y == width - 1) {
            cout << "恭喜你成功到達終點！" << endl;
            return true;
        }
        return false;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze Visualization");
    Maze maze(40, 30); // 40x30 的迷宮

    int player_x = 0, player_y = 0; // 玩家初始位置
    bool canMove = true; // 標記是否可以移動
    const float moveDelay = 0.2f; // 移動延遲時間（秒）
    sf::Clock moveClock; // 用於計時

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // 正確處理窗口關閉事件
            }
        }

        if (canMove) { // 僅在可以移動時檢查按鍵
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                maze.player_move(player_x, player_y, player_x - 1, player_y); // 上
                canMove = false;
                moveClock.restart(); // 重置計時器
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                maze.player_move(player_x, player_y, player_x + 1, player_y); // 下
                canMove = false;
                moveClock.restart(); // 重置計時器
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                maze.player_move(player_x, player_y, player_x, player_y - 1); // 左
                canMove = false;
                moveClock.restart(); // 重置計時器
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                maze.player_move(player_x, player_y, player_x, player_y + 1); // 右
                canMove = false;
                moveClock.restart(); // 重置計時器
            }
        }

        // 檢查是否超過移動延遲
        if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
            canMove = true; // 重新允許移動
        }

        window.clear();
        maze.display(window, player_x, player_y); // 繪製迷宮並顯示玩家位置
        window.display(); // 顯示內容
    }

    return 0;
}