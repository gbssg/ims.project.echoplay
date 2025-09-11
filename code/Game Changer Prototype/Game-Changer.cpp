
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

class iGame
{
public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void end() = 0;
    virtual ~iGame() {}
};

class Snake : public iGame
{
public:
    void start() override
    {
        cout << "Snake Started" << endl;
    }
    void update() override
    {
        cout << "Snake Updating..." << endl;
    }
    void end() override
    {
        cout << "Snake Ended" << endl;
    }
};

class Tetris : public iGame
{
public:
    void start() override
    {
        cout << "Tetris Started" << endl;
    }
    void update() override
    {
        cout << "Tetris Updating..." << endl;
    }
    void end() override
    {
        cout << "Tetris Ended" << endl;
    }
};

class Connect4 : public iGame
{
public:
    void start() override
    {
        cout << "Connect4 Started" << endl;
    }
    void update() override
    {
        cout << "Connect4 Updating..." << endl;
    }
    void end() override
    {
        cout << "Connect4 Ended" << endl;
    }
};

class Pong : public iGame
{
public:
    void start() override
    {
        cout << "Pong Started" << endl;
    }
    void update() override
    {
        cout << "Pong Updating..." << endl;
    }
    void end() override
    {
        cout << "Pong Ended" << endl;
    }
};

Snake snake;
Tetris tetris;
Connect4 connect4;
Pong pong;

using GameFunc = void (iGame::*)();

iGame *games[] = {&snake, &tetris, &connect4, &pong};
const int numGames = sizeof(games) / sizeof(games[0]);

int main()
{
    int currentGame = 0;
    GameFunc startFunc = &iGame::start;
    GameFunc updateFunc = &iGame::update;
    GameFunc endFunc = &iGame::end;

    while (true)
    {
        iGame *game = games[currentGame];
        (game->*startFunc)();
        cout << "Press any key to end this game..." << endl;
        while (!_kbhit())
        {
            (game->*updateFunc)();
            Sleep(500);
        }
        _getch();
        (game->*endFunc)();
        currentGame = (currentGame + 1) % numGames;
        system("cls");
    }
    return 0;
}