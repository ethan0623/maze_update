#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "maze.h"

using namespace std;





int main() {
    //sf::VideoMode videoMode(width, height); 拿來設定 windows 的長寬
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze Visualization");
    Maze maze(40, 30); // 40x30 的迷宮
    int player_x = maze.getBeginX(), player_y = maze.getBeginY(); // 玩家初始位置
    bool canMove = true; // 標記是否可以移動
    const float moveDelay = 0.15f; // 移動延遲時間（秒）
    sf::Clock moveClock; // 用於計時

    while (window.isOpen()) {
        //用於表示各種事件（如鍵盤、滑鼠、窗口狀態等）
        sf::Event event;
        // 處理事件
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
        // moveClock.getElapsedTime() 會自動返回所經的時間
        //.asSeconds() 將經過的時間轉換為以秒為單位的浮點數
        if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
            canMove = true; // 重新允許移動
        }

        window.clear();
        maze.display(window, player_x, player_y); // 繪製迷宮並顯示玩家位置
        window.display(); // 顯示內容
    }

    return 0;
}