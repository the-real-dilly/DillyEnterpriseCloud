// In your main.cpp or equivalent
#include "../include/Logger.h"
#include "../include/FileAnalyzer.h"
#include "../include/SignatureDetector.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Logger::getInstance().log(LogLevel::ERROR, "Usage: ./polyglot-detector <file_path>");
        return 1;
    }

    std::string filePath = argv[1];
    FileAnalyzer analyzer(filePath);

    if (!analyzer.loadFile()) {
        Logger::getInstance().log(LogLevel::ERROR, "Failed to load file: " + filePath);
        return 1;
    }

    SignatureDetector detector(analyzer);

    if (detector.detectPolyglot()) {
        Logger::getInstance().log(LogLevel::INFO, "Potential polyglot file detected!");
    } else {
        Logger::getInstance().log(LogLevel::INFO, "No polyglot file detected.");
    }

    return 0;
}
