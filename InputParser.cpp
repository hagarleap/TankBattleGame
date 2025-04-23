#include "InputParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

bool InputParser::getBoardDimensions(const std::string& filename, int& width, int& height, std::vector<std::string>& inputErrors) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        inputErrors.push_back("Cannot open file: " + filename);
        return false;
    }

    std::string line;
    if (std::getline(inFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> width >> height)) {
            inputErrors.push_back("Invalid board dimensions line.");
            return false;
        }
        return true;
    }

    inputErrors.push_back("File is empty or missing dimensions.");
    return false;
}


bool InputParser::parseFile(const std::string& filename,
    Board& board,
    std::vector<Tank>& player1Tanks,
    std::vector<Tank>& player2Tanks,
    std::vector<std::string>& inputErrors
) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    int width = 0, height = 0;
    std::string line;

    // First line: dimensions
    if (std::getline(inFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> width >> height)) {
            inputErrors.push_back("Invalid board dimensions.");
            return false;
        }
    } else {
        inputErrors.push_back("File is empty.");
        return false;
    }

    int currentRow = 0;
    int tank1Count = 0;
    int tank2Count = 0;

    while (std::getline(inFile, line) && currentRow < height) {
        for (int col = 0; col < width; ++col) {
            char ch = (col < int(line.size())) ? line[col] : ' ';

            Position pos(col, currentRow);

            switch (ch) {
                case '#':
                    board.placeWall(pos);
                    break;
                case '@':
                    board.placeMine(pos);
                    break;
                case '1':
                    if (tank1Count == 0) {
                        player1Tanks.emplace_back(1, tank1Count, pos, Direction::L); // cannon left
                        board.placeTank(pos, 1);
                        tank1Count++;
                    } else {
                        inputErrors.push_back("Multiple tanks found for Player 1; only the first one is used.");
                    }
                    break;
                case '2':
                    if (tank2Count == 0) {
                        player2Tanks.emplace_back(2, tank2Count, pos, Direction::R); // cannon right
                        board.placeTank(pos, 2);
                        tank2Count++;
                    } else {
                        inputErrors.push_back("Multiple tanks found for Player 2; only the first one is used.");
                    }
                    break;
                case ' ':
                    break; // Empty space
                default:
                    inputErrors.push_back("Unknown character '" + std::string(1, ch) +
                                          "' at row " + std::to_string(currentRow) +
                                          ", col " + std::to_string(col));
                    break;
            }
        }
        currentRow++;
    }
    std::cout << "✅ Parsing Done!" << std::endl;

    // Handle too few or too many rows
    if (currentRow < height) {
        inputErrors.push_back("Too few rows in the input file; expected " + std::to_string(height));
    }

    if (std::getline(inFile, line)) {
        inputErrors.push_back("Too many rows in the input file; expected " + std::to_string(height));
    }

    return true;
}
