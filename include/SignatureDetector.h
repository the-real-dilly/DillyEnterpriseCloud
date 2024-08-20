#pragma once
#include "FileAnalyzer.h"

class SignatureDetector {
public:
    SignatureDetector(const FileAnalyzer &analyzer);
    bool detectPolyglot();

private:
    const FileAnalyzer &analyzer;
};