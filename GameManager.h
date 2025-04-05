#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Board.h"
#include "Tank.h"
#include "Shell.h"
#include "Action.h"
#include <vector>
#include <string>
#include <fstream>

class GameManager {
public:
    GameManager(Board board,
                const std::vector<Position>& spawnP1,
                const std::vector<Position>& spawnP2);

    void run(int maxSteps = 1000);
    void writeLog(const std::string& outputFile) const;

private:
    Board board;

    std::vector<Tank> player1Tanks;
    std::vector<Tank> player2Tanks;
    std::vector<Shell> shells;

    int stepCounter = 0;
    std::vector<std::string> log;

    bool gameOver = false;
    std::string resultMessage;

    void tick();
    void handleTankAction(Tank& tank, Action action);
    void updateShells();
    void checkCollisions();
    void recordAction(int playerId, int tankId, Action action, bool success);
};

#endif // GAMEMANAGER_H
