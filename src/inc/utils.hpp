#pragma once
#include <string>
#include <sstream>
#include <optional>
#include <vector>
#include <iostream>
#include <variant>

inline void compiler_error_message(const char* msg) {
    std::cout << "      " << msg << " <------------" << std::endl;
};