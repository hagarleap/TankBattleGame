#include "ChasingAlgorithm.h"
#include "Board.h"
#include "Tile.h"
#include "Direction.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <climits>
// This implementation uses 2-step BFS to chase the opponent while treating walls and mines as obstacles.

TankAction ChasingAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    Position start = tank.getPosition();
    Direction dir = tank.getDirection();
    int width = board.getWidth();
    int height = board.getHeight();

    // Find enemy tank position
    Position target{-1, -1};
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile t = board.getTile(x, y);
            if ((tank.getPlayerId() == 1 && t.isTank2()) || (tank.getPlayerId() == 2 && t.isTank1())) {
                target = {x, y};
                break;
            }
        }
    }
    if (target.x == -1) return TankAction::None;

    // 2-step BFS (lookahead)
    struct Node { Position pos; Direction firstStep; int depth; };
    std::queue<Node> q;
    std::unordered_map<int, bool> visited;
    auto hash = [&](Position p) { return p.y * width + p.x; };

    const std::vector<Direction> directions = {Direction::U, Direction::UR, Direction::R, Direction::DR,
                                               Direction::D, Direction::DL, Direction::L, Direction::UL};

    for (Direction d : directions) {
        Position next = start.move(d);
        if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height) continue;
        const Tile& t = board.getTile(next);
        if (t.isWall() || t.isMine() || t.isOccupied()) continue;
        q.push({next, d, 1});
        visited[hash(next)] = true;
    }

    Direction bestDir = dir;
    int bestDist = INT_MAX;

    while (!q.empty()) {
        Node current = q.front(); q.pop();
        int dist = std::abs(target.x - current.pos.x) + std::abs(target.y - current.pos.y);
        if (dist < bestDist) {
            bestDist = dist;
            bestDir = current.firstStep;
        }
        if (current.depth >= 2) continue;

        for (Direction d : directions) {
            Position next = current.pos.move(d);
            if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height) continue;
            if (visited[hash(next)]) continue;
            const Tile& t = board.getTile(next);
            if (t.isWall() || t.isMine() || t.isOccupied()) continue;
            visited[hash(next)] = true;
            q.push({next, current.firstStep, current.depth + 1});
        }
    }

    return (bestDir == dir) ? TankAction::MoveForward : rotateToward(dir, bestDir);
}