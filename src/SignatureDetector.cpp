#include "../include/SignatureDetector.h"
#include <iostream>

SignatureDetector::SignatureDetector(const FileAnalyzer &analyzer) : analyzer(analyzer) {}

bool SignatureDetector::detectPolyglot() {
    bool isPDF = analyzer.isPDF();
    bool isJPEG = analyzer.isJPEG();

    if (isPDF && isJPEG) {
        std::cout << "Polyglot detected: PDF and JPEG" << std::endl;
        return true;
    }
    return false;
}