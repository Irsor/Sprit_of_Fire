#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

namespace utils {
    std::string loadFile(const std::string& relativeFilePath);
}