#include "file_utils.hpp"

std::string utils::loadFile(const std::string& relativeFilePath) {
    std::ifstream file(relativeFilePath);

    auto currentPath = std::filesystem::current_path().string();

    if (!file.is_open()) {
        std::cerr << "Error when opening file " << relativeFilePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}
