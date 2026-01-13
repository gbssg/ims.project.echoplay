#pragma once

#include <stdint.h>
#include <SparkFun_Qwiic_Button.h>
#include <Screen.h>
#include <SimpleSoftTimer.h>
#include <vector>
#include <Cloud/Cloud.h>
#include <JumpMan/JumpMan.h>
#include <Obstacle/Obstacle.h>
#include <IGame.h>

using namespace HolisticSolutions;

class CarJump : public IGame
{
private:
    std::vector<uint8_t> smallCloudSprite =
        {0, 1, 1, 0, 0,
         1, 1, 1, 1, 1,
         1, 1, 1, 1, 1};

    std::vector<uint8_t> longCloudSprite =
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
         0, 0, 1, 1, 1, 1, 0, 1, 1, 0,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::vector<uint8_t> bigCloudSprite =
        {0, 0, 1, 1, 1, 1, 0, 0,
         0, 1, 1, 1, 1, 1, 1, 0,
         1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1,
         0, 0, 1, 1, 1, 1, 1, 0};

    std::vector<uint8_t> carSprite =
        {0, 1, 1, 0,
         1, 1, 1, 1};

    std::vector<uint8_t> planeSprite =
        {0, 0, 0, 0, 0, 0, 0, 0, 1,
         0, 1, 1, 0, 0, 0, 0, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::vector<uint8_t> stoneSprite =
        {1, 1,
         1, 1,
         1, 1};

    Cloud smallCloud1{5, 5, smallCloudSprite};

    Cloud smallCloud2{5, 5, smallCloudSprite};

    Cloud longCloud{10, 4, longCloudSprite};

    Cloud bigCloud{8, 3, bigCloudSprite};

    std::vector<Cloud *> clouds = {
        &smallCloud1,
        &smallCloud2,
        &longCloud,
        &bigCloud};

    JumpMan Player{1, 13, 1, {1, 1}};

    Obstacle Car{4, 13, carSprite};

    Obstacle Plane{9, 11, planeSprite};

    Obstacle Stone{2, 12, stoneSprite};

    std::vector<Obstacle *> Obstacles = {
        &Car,
        &Plane,
        &Stone};

    int selectedObstacle;
    SimpleSoftTimer ObstacleSpawnTimer{5000};
    bool ObstacleSpawnWaiting = false;

    enum state
    {
        GAME_START,
        PLAYING
    };
    state gameState;

    int difficulty;
    SimpleSoftTimer DifficultyIncreaseTimer{10000};

public:
    void setup(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void start(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void update(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);

    void end(Screen &screen, QwiicButton &leftButton, QwiicButton &rightButton);
};