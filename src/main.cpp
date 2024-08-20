#include "../include/FileAnalyzer.h"
#include "../include/SignatureDetector.h"
#include "../include/Logger.h"

int main(int argc, char *argv[]) {
    Logger& logger = Logger::getInstance(); 

    if (argc < 2) {
        logger.log(LogLevel::ERROR, "Usage: ./DILLYPOLYSCAN <file_path>");
        return 1;
    }

    std::string filePath = argv[1];
    FileAnalyzer analyzer(filePath);

    if (!analyzer.loadFile()) {
        logger.log(LogLevel::ERROR, "Failed to load file: " + filePath);
        return 1;
    }

    SignatureDetector detector(analyzer);

    if (detector.detectPolyglot()) {
        logger.log(LogLevel::INFO, "Potential polyglot file detected!");
    } else {
        logger.log(LogLevel::INFO, "No polyglot file detected.");
    }

    return 0;
}
