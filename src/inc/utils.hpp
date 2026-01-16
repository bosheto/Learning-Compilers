#pragma once
#include <string>
#include <sstream>
#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include <fstream>

enum class CompilerStage {
    Tokenize,
    Parse,
    Generate,
    Generic
};

inline void compiler_error_and_exit(const char* msg, CompilerStage stage = CompilerStage::Generic){
    
    switch (stage)
    {
    case CompilerStage::Tokenize:
        std::cout << "Stage: TOKENIZE" << std::endl;
        break;
    case CompilerStage::Parse:
        std::cout << "Stage: PARSE" << std::endl;
        break;
    case CompilerStage::Generate:
        std::cout << "Stage: GENERATE" << std::endl;
        break;
    default:
        std::cout << "Generic error" << std::endl;
        break;
    }

    std::cerr << "      " << msg << " <------------" << std::endl;
    exit(EXIT_FAILURE);
};