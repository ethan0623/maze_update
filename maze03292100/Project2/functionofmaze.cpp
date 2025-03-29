#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "maze.h"
using namespace std;


vector<vector<Cell>> cells;
    // �ѼƤƺc�y��ơA�i�i���l��
Maze::Maze(int w, int h) : width(w), height(h) {
        //height �����O�g�c���C�ơAvector<Cell>(width) �����O�C�@�C���� width �� Cell
        cells.resize(height, vector<Cell>(width));
        //srand �� source code => void srand(unsigned int seed);
        //time(0) �������� time_t�A�ҥH�n���z�L static_cast<unsigned int>(time(0)) �ন unsigned int
        srand(static_cast<unsigned int>(time(0)));

        // �H���ͦ��g�c
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cells[i][j].isWall = (rand() % 4 == 0); // 25% ���v�O��
                cells[i][j].isVisited = false;         // ��l�Ƭ����X��
            }
        }

        // �]�w�_�I�M���I
        // �_�I
        begin_x = rand() % height;
        begin_y = rand() % width;
        cells[begin_x][begin_y].isWall = false;
        // ���I
        // �T�O�_�I�P���I���b�P�@�Ӧ�m
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


    // ��ܰg�c
    // sf::RenderWindow& window �O SFML �����f��H���ޥΡA�Ω�i��Ҧ���ø�Ͼާ@
    void Maze::display(sf::RenderWindow& window, int player_x, int player_y) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                //�Ыؤ@�Ӫ���ΡA�j�p�� 20x20 �����A�Y���C�Ӱg�c�椸�檺�j�p
                sf::RectangleShape rect(sf::Vector2f(20, 20));
                //�N����Ω�m�b���f�������T��m
                rect.setPosition(j * 20, i * 20);
                // �o�ӧP�_���O�ΨӱN����e���¦⪺
                rect.setFillColor(cells[i][j].isWall ? sf::Color::Black : sf::Color::White);
                window.draw(rect);
            }
        }
        //ø�s���I��m
        sf::RectangleShape finish(sf::Vector2f(15, 15));
        finish.setFillColor(sf::Color::Green);
        finish.setPosition(finish_y * 20 + 5, finish_x * 20 + 5);
        window.draw(finish);

        // ø�s���a��m
        sf::CircleShape player(5); // �b�|�� 10 ����ΡA��ܪ��a
        player.setFillColor(sf::Color::Red); // ���a�C��
        player.setPosition(player_y * 20 + 5, player_x * 20 + 5); // �p�⪱�a��m�A��ܦb��l����
        window.draw(player); // ø�s���a

    }

    bool Maze::player_move(int& player_x, int& player_y, int new_player_x, int new_player_y) {
        // �ˬd�s��m�O�_����
        if (new_player_x < 0 || new_player_x >= height || new_player_y < 0 || new_player_y >= width || cells[new_player_x][new_player_y].isWall) {
            cout << "�L�k���ʡA�I������I" << endl;
            return false;
        }

        // ��s���a��m
        player_x = new_player_x;
        player_y = new_player_y;
        cells[player_x][player_y].isVisited = true; // �аO���w�X��

        // �ˬd�O�_��F���I
        if (player_x == finish_x && player_y == finish_y) {
            cout << "���ߧA���\��F���I�I" << endl;
            return true;
        }
        return false;
    }
