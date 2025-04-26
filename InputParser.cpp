#include "InputParser.h"
#include "Tile.h"
#include "Tank.h"
#include <fstream>
#include <iostream>

std::pair<int, int> InputParser::getBoardDimensions(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Cannot open input file: " << filename << std::endl;
        return {-1, -1};
    }

    int width, height;
    inputFile >> width >> height;
    if (inputFile.fail() || width <= 0 || height <= 0) {
        std::cerr << "Error: Invalid board dimensions." << std::endl;
        return {-1, -1};
    }
    return {width, height};
}

bool InputParser::parseFile(const std::string& filename,
    Board& board,
    std::vector<Tank>& player1Tanks,
    std::vector<Tank>& player2Tanks,
    std::vector<std::string>& inputErrors)
{
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Cannot open input file: " << filename << std::endl;
        return false;
    }

    int width, height;
    inputFile >> width >> height;
    if (inputFile.fail() || width <= 0 || height <= 0) {
        std::cerr << "Error: Invalid board dimensions." << std::endl;
        return false;
    }

    std::string line;
    std::getline(inputFile, line); // consume the rest of the first line

    int player1TanksCount = 0;
    int player2TanksCount = 0;
    int row = 0;

    while (std::getline(inputFile, line)) {
        if (row >= board.getHeight()) {
            inputErrors.push_back("Extra row detected beyond declared board height at row " + std::to_string(row));
            continue;
        }

        for (int col = 0; col < board.getWidth(); ++col) {
            char ch = (col < int(line.size())) ? line[col] : ' ';

            Tile& tile = board.getTile(col, row);

            switch (ch) {
                case '#':
                    board.placeWall(Position(col, row));
                    break;
                case 'M':
                    board.placeMine(Position(col, row));
                    break;
                case '1':
                    if (player1TanksCount >= 1) {
                        inputErrors.push_back("Multiple tanks for player 1 detected at (" + std::to_string(col) + "," + std::to_string(row) + ")");
                    } else {
                        player1Tanks.emplace_back(1, player1TanksCount, Position(col, row), Direction::U);
                        tile.setType(TileType::TANK1);
                        ++player1TanksCount;
                    }
                    break;
                case '2':
                    if (player2TanksCount >= 1) {
                        inputErrors.push_back("Multiple tanks for player 2 detected at (" + std::to_string(col) + "," + std::to_string(row) + ")");
                    } else {
                        player2Tanks.emplace_back(2, player2TanksCount, Position(col, row), Direction::U);
                        tile.setType(TileType::TANK2);
                        ++player2TanksCount;
                    }
                    break;
                case ' ':
                    // Empty space, nothing to do
                    break;
                default:
                    inputErrors.push_back("Unknown character '" + std::string(1, ch) + "' at (" + std::to_string(col) + "," + std::to_string(row) + ")");
                    // Treat as empty tile
                    break;
            }
        }
        ++row;
    }

    if (row < board.getHeight()) {
        inputErrors.push_back("Missing rows: Board height declared as " + std::to_string(board.getHeight()) +
                              " but only " + std::to_string(row) + " rows found");
    }

    // If there were errors, write them to input_errors.txt
    if (!inputErrors.empty()) {
        std::ofstream errFile("input_errors.txt");
        for (const auto& err : inputErrors) {
            errFile << err << "\n";
        }
        errFile.close();
        std::cout << "Parsing completed with " << inputErrors.size() << " recoverable errors.\n";
    } else {
        std::cout << "Parsing completed with no errors.\n";
    }

    return true;
}
