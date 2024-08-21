#include "../include/SignatureDetector.h"
#include <iostream>

SignatureDetector::SignatureDetector(const FileAnalyzer &analyzer) : analyzer(analyzer) {}

bool SignatureDetector::detectPolyglot() {
    std::cout << "[DEBUG] SignatureDetector initialized" << std::endl;
    bool isPDF = analyzer.isPDF();
    bool isJPEG = analyzer.isJPEG();

    std::cout << "[DEBUG] PDF signature detected: " << isPDF << std::endl;
    std::cout << "[DEBUG] JPEG signature detected: " << isJPEG << std::endl;

    if (isPDF && isJPEG) {
        std::cout << "[INFO] Polyglot detected: PDF and JPEG" << std::endl;
        return true;
    }
    std::cout << "[INFO] No polyglot file detected." << std::endl;
    return false;
}
