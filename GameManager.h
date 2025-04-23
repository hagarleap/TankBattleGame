#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Board.h"
#include "Tank.h"
#include "Shell.h"
#include "TankAction.h"
#include <vector>
#include <string>
#include <fstream>

class GameManager {
public:
    GameManager(Board& board,
                 std::vector<Tank>& player1Tanks,
                 std::vector<Tank>& player2Tanks);

    void run(int maxSteps = 1000);
    void writeLog(const std::string& outputFile) const;
    std::string getResultMessage() const;


private:
    Board& board;

    std::vector<Tank>& player1Tanks;
    std::vector<Tank>& player2Tanks;
    std::vector<Shell> shells;

    int stepCounter = 0;
    std::vector<std::string> log;

    bool gameOver = false;
    std::string resultMessage;

    void tick();
    void handleTankAction(Tank& tank, TankAction& action);
    void moveShells();
    void checkCollisions();
    void updateBoard();
    void recordAction(int playerId, int tankId, TankAction action, bool success);

};

#endif // GAMEMANAGER_H
