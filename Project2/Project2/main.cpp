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

    // �ѼƤƺc�y��ơA�i�i���l��
    Maze(int w, int h) : width(w), height(h) {
        //height �����O�g�c���C�ơAvector<Cell>(width) �����O�C�@�C���� width �� Cell
        cells.resize(height, vector<Cell>(width));
        srand(static_cast<unsigned int>(time(0)));

        // �H���ͦ��g�c
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cells[i][j].isWall = (rand() % 4 == 0); // 25% ���v�O��
                cells[i][j].isVisited = false;         // ��l�Ƭ����X��
            }
        }

        // �]�w�_�I�M���I
        cells[0][0].isWall = false;                // �_�I
        cells[height - 1][width - 1].isWall = false; // ���I
    }

    // ��ܰg�c
    void display(sf::RenderWindow& window, int player_x, int player_y) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                sf::RectangleShape rect(sf::Vector2f(20, 20));
                rect.setPosition(j * 20, i * 20);
                rect.setFillColor(cells[i][j].isWall ? sf::Color::Black : sf::Color::White);
                window.draw(rect);
            }
        }

        // ø�s���a��m
        sf::CircleShape player(5); // �b�|�� 10 ����ΡA��ܪ��a
        player.setFillColor(sf::Color::Red); // ���a�C��
        player.setPosition(player_y * 20 + 5, player_x * 20 + 5); // �p�⪱�a��m�A��ܦb��l����
        window.draw(player); // ø�s���a
    }

    bool player_move(int& player_x, int& player_y, int new_player_x, int new_player_y) {
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
        if (player_x == height - 1 && player_y == width - 1) {
            cout << "���ߧA���\��F���I�I" << endl;
            return true;
        }
        return false;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze Visualization");
    Maze maze(40, 30); // 40x30 ���g�c

    int player_x = 0, player_y = 0; // ���a��l��m
    bool canMove = true; // �аO�O�_�i�H����
    const float moveDelay = 0.2f; // ���ʩ���ɶ��]��^
    sf::Clock moveClock; // �Ω�p��

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // ���T�B�z���f�����ƥ�
            }
        }

        if (canMove) { // �Ȧb�i�H���ʮ��ˬd����
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                maze.player_move(player_x, player_y, player_x - 1, player_y); // �W
                canMove = false;
                moveClock.restart(); // ���m�p�ɾ�
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                maze.player_move(player_x, player_y, player_x + 1, player_y); // �U
                canMove = false;
                moveClock.restart(); // ���m�p�ɾ�
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                maze.player_move(player_x, player_y, player_x, player_y - 1); // ��
                canMove = false;
                moveClock.restart(); // ���m�p�ɾ�
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                maze.player_move(player_x, player_y, player_x, player_y + 1); // �k
                canMove = false;
                moveClock.restart(); // ���m�p�ɾ�
            }
        }

        // �ˬd�O�_�W�L���ʩ���
        if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
            canMove = true; // ���s���\����
        }

        window.clear();
        maze.display(window, player_x, player_y); // ø�s�g�c����ܪ��a��m
        window.display(); // ��ܤ��e
    }

    return 0;
}