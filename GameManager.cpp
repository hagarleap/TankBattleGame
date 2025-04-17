#include "GameManager.h"
#include <iostream>
#include <bits/algorithmfwd.h>

GameManager::GameManager(Board board,
                         const std::vector<Position>& spawnP1,
                         const std::vector<Position>& spawnP2)
    : board(std::move(board))
{
    for (size_t i = 0; i < spawnP1.size(); ++i)
        player1Tanks.emplace_back(1, static_cast<int>(i), spawnP1[i], Direction::L);
    for (size_t i = 0; i < spawnP2.size(); ++i)
        player2Tanks.emplace_back(2, static_cast<int>(i), spawnP2[i], Direction::R);
}

void GameManager::run(int maxSteps) {
    while (!gameOver && stepCounter < maxSteps*2) {
        ++stepCounter;
        moveShells();
        checkCollisions();
        // Game moves by shell steps
        if (stepCounter%2 == 0){
            tick();
            checkCollisions();
        }
        updateBoard();
        // Check win/tie conditions 
        if (player1Tanks.empty() && player2Tanks.empty()) {
            gameOver = true;
            resultMessage = "Tie: Both tanks destroyed.";
        } 
        else if (player1Tanks.empty()) {
            gameOver = true;
            resultMessage = "Player 2 wins!";
        } 
        else if (player2Tanks.empty()) {
            gameOver = true;
            resultMessage = "Player 1 wins!";
        }
    }

    if (!gameOver)
        resultMessage = "Tie: Max steps reached.";
}

void GameManager::tick() {
    for (auto& tank : player1Tanks)
        handleTankAction(tank, tank.nextAction());

    for (auto& tank : player2Tanks)
        handleTankAction(tank, tank.nextAction());
}

void GameManager::handleTankAction(Tank& tank, TankAction action) {
    if (!tank.isAlive()) return;

    bool success = true;

    switch (action) {
        case TankAction::Shoot:
            if (tank.canShoot()) {
                tank.onShoot();
                shells.emplace_back(tank.getPosition(), tank.getDirection(), tank.getPlayerId());
            } else {
                success = false;
            }
            break;

        case TankAction::MoveForward: {
            Position newPos = tank.getPosition().move(tank.getDirection(), 1);
            Tile& targetTile = board.getTile(newPos);

            // Don't move if wall or tank ahead — mines/shells handled in checkCollisions
            if (targetTile.isWall() || targetTile.isOccupied()) {
                success = false;
            } else {
                tank.moveForward();  // saves previous position
            }
            break;
        }

        case TankAction::MoveBackward: {
            Position backPos = tank.getPosition().move(opposite(tank.getDirection()), 1);
            Tile& targetTile = board.getTile(backPos);

            if (targetTile.isWall() || targetTile.isOccupied()) {
                success = false;
            } else {
                tank.moveBackward();  // saves previous position
            }
            break;
        }

        case TankAction::RotateLeft8:
            tank.rotateLeft8();
            break;

        case TankAction::RotateRight8:
            tank.rotateRight8();
            break;

        case TankAction::RotateLeft4:
            tank.rotateLeft4();
            break;

        case TankAction::RotateRight4:
            tank.rotateRight4();
            break;

        case TankAction::None:
        default:
            success = false;
            break;
    }

    recordAction(tank.getPlayerId(), tank.getTankId(), action, success);
    tank.tickCooldown();
}


void GameManager::moveShells() {
    for (Shell& shell : shells) {
        
        shell.advance();
        
    }
}
// after a moveing part has moved (shell/tank) and no collisions - update the location on the borad
void GameManager::updateBoard() {
    // 1. Clear dynamic elements (TANK1, TANK2, SHELL) from the board
    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            Position pos(x, y);
            Tile& tile = board.getTile(pos);

            // Don't clear walls or mines
            if (tile.getType() == TileType::TANK1 ||
                tile.getType() == TileType::TANK2 ||
                tile.getType() == TileType::SHELL) {
                tile.setType(TileType::EMPTY);
            }
        }
    }

    // 2. Place alive tanks on the board
    for (const Tank& tank : player1Tanks) {
        if (tank.isAlive()) {
            board.getTile(tank.getPosition()).setType(TileType::TANK1);
        }
    }

    for (const Tank& tank : player2Tanks) {
        if (tank.isAlive()) {
            board.getTile(tank.getPosition()).setType(TileType::TANK2);
        }
    }

    // 3. Optional: mark shell positions (if you want them on the tile map)
    for (const Shell& shell : shells) {
        const Position& pos = shell.getPosition();
        Tile& tile = board.getTile(pos);

        // Don't overwrite tanks, just place shell marker on empty tiles
        if (tile.getType() == TileType::EMPTY) {
            tile.setType(TileType::SHELL);
        }
    }
}


void GameManager::checkCollisions() {
    std::vector<size_t> shellsToRemove;

    // === 1. Shell collisions ===
    for (size_t i = 0; i < shells.size(); ++i) {
        Shell& shell1 = shells[i];
        Position pos1 = shell1.getPosition();
        Tile& currTile = board.getTile(pos1);

        // 1.1 Shell–shell
        for (size_t j = i + 1; j < shells.size(); ++j) {
            if (shells[j].getPosition() == pos1) {
                shellsToRemove.push_back(i);
                shellsToRemove.push_back(j);
                goto next_shell;
            }
        }

        // 1.2 Shell–wall
        if (currTile.isWall()) {
            currTile.hitWall();
            shellsToRemove.push_back(i);
            continue;
        }

        // 1.3 Shell–tank1
        if (currTile.isTank1()) {
            for (Tank& tank : player1Tanks) {
                if (tank.isAlive() && tank.getPosition() == pos1) {
                    tank.destroy();
                    currTile.setType(TileType::EMPTY);
                    shellsToRemove.push_back(i);
                    goto next_shell;
                }
            }
        }

        // 1.4 Shell–tank2
        if (currTile.isTank2()) {
            for (Tank& tank : player2Tanks) {
                if (tank.isAlive() && tank.getPosition() == pos1) {
                    tank.destroy();
                    currTile.setType(TileType::EMPTY);
                    shellsToRemove.push_back(i);
                    goto next_shell;
                }
            }
        }

    next_shell:
        continue;
    }

    // === 2. Tank–object collisions ===
    auto checkTankCollision = [&](Tank& tank, std::vector<Tank>& enemyTanks) {
        if (!tank.isAlive()) return;

        Position pos = tank.getPosition();
        Tile& tile = board.getTile(pos);

        // Tank on a wall – cancel move
        if (tile.isWall()) {
            tank.cancelMove(); // custom method: restore previous position
            return;
        }

        // Tank on a mine – destroy
        if (tile.isMine()) {
            tank.destroy();
            tile.setType(TileType::EMPTY);
            return;
        }

        // Tank on a shell – destroy
        for (Shell& shell : shells) {
            if (shell.getPosition() == pos) {
                tank.destroy();
                tile.setType(TileType::EMPTY);
                break;
            }
        }

        // Tank collided with another tank – destroy both
        for (Tank& enemy : enemyTanks) {
            if (enemy.isAlive() && enemy.getPosition() == pos) {
                tank.destroy();
                enemy.destroy();
                tile.setType(TileType::EMPTY);
                break;
            }
        }
    };

    for (Tank& t1 : player1Tanks) checkTankCollision(t1, player2Tanks);
    for (Tank& t2 : player2Tanks) checkTankCollision(t2, player1Tanks);

    // === 3. Remove dead shells ===
    std::sort(shellsToRemove.begin(), shellsToRemove.end());
    shellsToRemove.erase(std::unique(shellsToRemove.begin(), shellsToRemove.end()), shellsToRemove.end());

    for (auto it = shellsToRemove.rbegin(); it != shellsToRemove.rend(); ++it) {
        shells.erase(shells.begin() + *it);
    }
}


void GameManager::recordAction(int playerId, int tankId, TankAction action, bool success) {
    std::string logEntry = "P" + std::to_string(playerId) + "-T" + std::to_string(tankId) +
                           ": " + std::string(to_string(action)) +
                           (success ? "" : " (BAD STEP)");
    log.push_back(logEntry);
}

void GameManager::writeLog(const std::string& outputFile) const {
    std::ofstream out(outputFile);
    for (const auto& entry : log)
        out << entry << "\n";
    out << "Result: " << resultMessage << "\n";
}
