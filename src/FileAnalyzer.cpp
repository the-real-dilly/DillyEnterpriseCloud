#include "../include/FileAnalyzer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

FileAnalyzer::FileAnalyzer(const std::string &filePath) : filePath(filePath) {}

bool FileAnalyzer::loadFile() {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    fileContent.resize(size);
    if (file.read(reinterpret_cast<char*>(fileContent.data()), size)) {
        std::cout << "[DEBUG] File size: " << size << " bytes" << std::endl;
        return true;
    }
    return false;
}

std::vector<unsigned char> FileAnalyzer::getFileContent() const {
    return fileContent;
}

bool FileAnalyzer::checkSignature(const std::vector<unsigned char>& signature, size_t offset) const {
    if (fileContent.size() < offset + signature.size()) {
        std::cout << "[DEBUG] Signature check failed at offset: " << offset << " (file too short)" << std::endl;
        return false;
    }

    bool match = std::equal(signature.begin(), signature.end(), fileContent.begin() + offset);
    std::cout << "[DEBUG] Checking signature at offset: " << offset << std::endl;
    std::cout << "[DEBUG] Expected: ";
    for (auto byte : signature) std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    std::cout << std::endl;
    std::cout << "[DEBUG] Found:    ";
    for (size_t i = 0; i < signature.size(); ++i) std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(fileContent[offset + i]) << " ";
    std::cout << std::endl;

    if (match) {
        std::cout << "[DEBUG] Signature match at offset: " << offset << std::endl;
    } else {
        std::cout << "[DEBUG] Signature mismatch at offset: " << offset << std::endl;
    }
    return match;
}

bool FileAnalyzer::isPDF() const {
    std::vector<unsigned char> pdfStartSignature = {0x25, 0x50, 0x44, 0x46}; 
    std::vector<unsigned char> pdfEndSignature = {0x25, 0x45, 0x4F, 0x46};   

    bool start = false;
    bool end = false;
    for (size_t offset = 0; offset <= fileContent.size() - pdfStartSignature.size(); ++offset) {
        if (checkSignature(pdfStartSignature, offset)) {
            start = true;
            break;
        }
    }
    for (size_t offset = fileContent.size() - pdfEndSignature.size(); offset >= pdfEndSignature.size(); --offset) {
        if (checkSignature(pdfEndSignature, offset)) {
            end = true;
            break;
        }
    }
    std::cout << "[DEBUG] PDF Start Check: " << start << ", PDF End Check: " << end << std::endl;
    return start && end;
}

bool FileAnalyzer::isJPEG() const {
    std::vector<unsigned char> jpegStartSignature = {0xFF, 0xD8, 0xFF}; 
    std::vector<unsigned char> jpegEndSignature = {0xFF, 0xD9};         

    bool start = false;
    bool end = false;
    for (size_t offset = 0; offset <= fileContent.size() - jpegStartSignature.size(); ++offset) {
        if (checkSignature(jpegStartSignature, offset)) {
            start = true;
            break;
        }
    }
    for (size_t offset = fileContent.size() - jpegEndSignature.size(); offset >= jpegEndSignature.size(); --offset) {
        if (checkSignature(jpegEndSignature, offset)) {
            end = true;
            break;
        }
    }
    std::cout << "[DEBUG] JPEG Start Check: " << start << ", JPEG End Check: " << end << std::endl;
    return start && end;
}
