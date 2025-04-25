#include "ChasingAlgorithm.h"
#include "Board.h"
#include "Tile.h"
#include "Direction.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <climits>

// Full BFS to chase the opponent, treating walls and mines as impassable
TankAction ChasingAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    (void)shells;
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

    struct Node {
        Position pos;
        Direction from;
    };

    std::queue<Node> q;
    std::unordered_map<int, Position> parent;
    std::unordered_map<int, bool> visited;
    auto hash = [&](Position p) { return p.y * width + p.x; };

    q.push({start, dir});
    visited[hash(start)] = true;

    const std::vector<Direction> directions = {
        Direction::U, Direction::UR, Direction::R, Direction::DR,
        Direction::D, Direction::DL, Direction::L, Direction::UL
    };

    while (!q.empty()) {
        Node current = q.front(); q.pop();
        if (current.pos == target) break;

        for (Direction d : directions) {
            Position next = board.wrapPosition(current.pos.move(d));
            int h = hash(next);
            if (visited[h]) continue;
            const Tile& t = board.getTile(next);
            bool isTarget = (next == target);
            if ((t.isWall() || t.isMine() || t.isOccupied()) && !isTarget) continue;
            visited[h] = true;
            parent[h] = current.pos;
            q.push({next, d});
        }
    }

    // Reconstruct path
    int h = hash(target);
    if (!visited[h]) {
        std::cout << "Target not reachable from start" << std::endl;
        return TankAction::None;
    } 

    // Trace path from target back to start
    std::vector<Position> path;
    for (Position at = target; at != start && parent.count(hash(at)); at = parent[hash(at)]) {
        path.push_back(at);
    }

    std::cout << "[Chasing] Path from target to start:\n";
    for (const Position& p : path) {
        std::cout << "(" << p.x << "," << p.y << ") ";
    }
    std::cout << std::endl;

    if (path.empty()) {
    // Path not reachable in 1 move — rotate toward target as fallback
    Direction toTarget = directionTo(start, target, board.getWidth(), board.getHeight());
    if (toTarget != dir) return rotateToward(dir, toTarget);
    return TankAction::None;
}
    Position step = path.back();

    for (Direction d : directions) {
        Position moved = board.wrapPosition(start.move(d));
        if (moved == step) {
            return (d == dir) ? TankAction::MoveForward : rotateToward(dir, d);
        }
    }

    return TankAction::None;
}