#pragma once
#include <string>
#include <vector>

class FileAnalyzer {
public:
    FileAnalyzer(const std::string &filePath);
    bool loadFile();
    std::vector<unsigned char> getFileContent() const;
    bool isPDF() const;
    bool isJPEG() const;

private:
    std::string filePath;
    std::vector<unsigned char> fileContent;
    bool checkSignature(const std::vector<unsigned char>& signature, size_t offset = 0) const;
};