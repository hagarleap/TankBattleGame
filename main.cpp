#include <iostream>
#include <vector>
#include "Board.h"
#include "Tank.h"
#include "InputParser.h"
#include "GameManager.h"

int main(int argc, char* argv[]) {
    std::cout << "🛠️ Program started..." << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: ./TankGame <input_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::vector<Tank> player1Tanks;
    std::vector<Tank> player2Tanks;
    std::vector<std::string> inputErrors;

    int width = 0, height = 0;
    if (!InputParser::getBoardDimensions(inputFile, width, height, inputErrors)) {
        std::cerr << "Failed to read board dimensions." << std::endl;
        return 1;
    }
    
    Board board(width, height); 
    
    if (!InputParser::parseFile(inputFile, board, player1Tanks, player2Tanks, inputErrors)) {
        std::cerr << "Failed to parse input file." << std::endl;
        return 1;
    }
    std::cout << "✅ Parsed input file" << std::endl;


    if (!inputErrors.empty()) {
        std::ofstream errFile("input_errors.txt");
        for (const std::string& err : inputErrors) {
            errFile << err << std::endl;
        }
    }
    std::cout << "✅ Starting game loop" << std::endl;
    GameManager manager(board, player1Tanks, player2Tanks);
    manager.run(5); // maxSteps = 100
    std::cout << "✅ GameManager finished running" << std::endl;
    std::cout << manager.getResultMessage() << std::endl;
    return 0;
}
