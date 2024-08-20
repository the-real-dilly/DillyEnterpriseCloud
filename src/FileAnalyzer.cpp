#include "../include/FileAnalyzer.h"
#include <fstream>
#include <iostream>

FileAnalyzer::FileAnalyzer(const std::string &filePath) : filePath(filePath) {}

bool FileAnalyzer::loadFile() {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return false;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    fileContent.resize(size);
    if (file.read(reinterpret_cast<char*>(fileContent.data()), size)) {
        return true;
    }
    return false;
}

std::vector<unsigned char> FileAnalyzer::getFileContent() const {
    return fileContent;
}

bool FileAnalyzer::checkSignature(const std::vector<unsigned char>& signature, size_t offset) const {
    if (fileContent.size() < offset + signature.size()) return false;
    return std::equal(signature.begin(), signature.end(), fileContent.begin() + offset);
}

bool FileAnalyzer::isPDF() const {
    std::vector<unsigned char> pdfSignature = {0x25, 0x50, 0x44, 0x46}; 
    return checkSignature(pdfSignature);
}

bool FileAnalyzer::isJPEG() const {
    std::vector<unsigned char> jpegSignature = {0xFF, 0xD8, 0xFF}; 
    return checkSignature(jpegSignature);
}