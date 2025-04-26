#include "Board.h"
#include "Tank.h"
#include "GameManager.h"
#include "InputParser.h"
#include "StrategyManager.h"
#include "UserInputAlgorithm.h"
#include "ChasingAlgorithm.h"
#include "ShootingAlgorithm.h"
#include <iostream>
#include <memory>
#include <vector>

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
  
    auto sm1 = std::make_shared<StrategyManager>(true); /// passing true means using the common sense algorithm (one that voids mines, making steps in the path of shells, etc.) 
    auto sm2 = std::make_shared<StrategyManager>(true); // it is reccommended to use false if using the UserInputAlgorithm, otherwise it will interfere with the user input if it thinks it is a bad move.

    sm1->assignAlgorithm(0, std::make_shared<ChasingAlgorithm>());
    sm2->assignAlgorithm(0, std::make_shared<ShootingAlgorithm>());

    GameManager manager(board, sm1, sm2, player1Tanks, player2Tanks);
    manager.run(100); // maxSteps = 100
    manager.writeLog("output_" + inputFile);

    std::cout << "✅ GameManager finished running" << std::endl;
    std::cout << manager.getResultMessage() << std::endl;
    return 0;
}