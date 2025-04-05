#include "GameManager.h"
#include <iostream>

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
    while (!gameOver && stepCounter < maxSteps) {
        ++stepCounter;
        tick();
        updateShells();
        checkCollisions();

        // Check win/tie conditions (simplified for now)
        if (player1Tanks.empty() && player2Tanks.empty()) {
            gameOver = true;
            resultMessage = "Tie: Both tanks destroyed.";
        } else if (player1Tanks.empty()) {
            gameOver = true;
            resultMessage = "Player 2 wins!";
        } else if (player2Tanks.empty()) {
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

void GameManager::handleTankAction(Tank& tank, Action action) {
    bool success = true;

    // Example logic — real movement handling comes later
    if (action == Action::Shoot && tank.canShoot()) {
        tank.onShoot();
        shells.emplace_back(tank.getPosition(), tank.getDirection());
    } else if (action == Action::Shoot && !tank.canShoot()) {
        success = false;
    }

    recordAction(tank.getPlayerId(), tank.getTankId(), action, success);
    tank.tickCooldown();
}

void GameManager::updateShells() {
    for (Shell& shell : shells) {
        shell.advance();
        // TODO: tunnel logic, shell removal, etc.
    }
}

void GameManager::checkCollisions() {
    // TODO: collisions between tanks, shells, walls, mines
}

void GameManager::recordAction(int playerId, int tankId, Action action, bool success) {
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
