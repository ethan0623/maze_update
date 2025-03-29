#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "maze.h"

using namespace std;





int main() {
    //sf::VideoMode videoMode(width, height); ���ӳ]�w windows �����e
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maze Visualization");
    Maze maze(40, 30); // 40x30 ���g�c
    int player_x = maze.getBeginX(), player_y = maze.getBeginY(); // ���a��l��m
    bool canMove = true; // �аO�O�_�i�H����
    const float moveDelay = 0.15f; // ���ʩ���ɶ��]��^
    sf::Clock moveClock; // �Ω�p��

    while (window.isOpen()) {
        //�Ω��ܦU�بƥ�]�p��L�B�ƹ��B���f���A���^
        sf::Event event;
        // �B�z�ƥ�
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
        // moveClock.getElapsedTime() �|�۰ʪ�^�Ҹg���ɶ�
        //.asSeconds() �N�g�L���ɶ��ഫ���H����쪺�B�I��
        if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
            canMove = true; // ���s���\����
        }

        window.clear();
        maze.display(window, player_x, player_y); // ø�s�g�c����ܪ��a��m
        window.display(); // ��ܤ��e
    }

    return 0;
}