#include "ChasingAlgorithm.h"
#include <queue>
#include <unordered_map>

TankAction ChasingAlgorithm::decideAction(const Tank& tank, const Board& board, const std::vector<Shell>& shells) {
    Position start = tank.getPosition();
    Direction dir = tank.getDirection();
    int width = board.getWidth();
    int height = board.getHeight();

    // Find opponent tank
    Position target = {-1, -1};
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile tile = board.getTile(x, y);
            if ((tank.getPlayerId() == 1 && tile.isTank2()) || (tank.getPlayerId() == 2 && tile.isTank1())) {
                target = {x, y};
                break;
            }
        }
    }
    if (target.x == -1) return TankAction::None;

    // BFS for shortest direction
    std::queue<Position> q;
    std::unordered_map<int, Position> parent;
    std::unordered_map<int, bool> visited;
    auto hash = [&](Position p) { return p.y * width + p.x; };

    q.push(start);
    visited[hash(start)] = true;

    const std::vector<Direction> directions = {Direction::U, Direction::UR, Direction::R, Direction::DR, Direction::D, Direction::DL, Direction::L, Direction::UL};

    while (!q.empty()) {
        Position current = q.front(); q.pop();
        if (current == target) break;

        for (Direction d : directions) {
            Position next = current.move(d);
            if (next.x < 0 || next.y < 0 || next.x >= width || next.y >= height) continue;
            Tile t = board.getTile(next);
            if (t.isWall() || t.isOccupied()) continue;
            int h = hash(next);
            if (visited[h]) continue;
            visited[h] = true;
            parent[h] = current;
            q.push(next);
        }
    }

    if (!visited[hash(target)]) return TankAction::None;

    // Trace one step toward target
    Position p = target;
    while (parent[hash(p)] != start) {
        p = parent[hash(p)];
    }

    // Decide how to move toward p
    int dx = p.x - start.x;
    int dy = p.y - start.y;

    for (Direction d : directions) {
        if (::dx(d) == dx && ::dy(d) == dy) {
            if (d == dir) return TankAction::MoveForward;
            // Rotation logic (simplified)
            return TankAction::RotateRight8;
        }
    }
    return TankAction::None;
}