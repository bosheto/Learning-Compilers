#pragma once
#include "utils.hpp"

enum class TokenType {
    _exit,
    int_lit,
    semicolon,
    open_bracket,
    close_bracket,
    identifier,
    open_parenthesis,
    close_parenthesis
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};


class Tokenizer {
    public:
        inline explicit Tokenizer(const std::string src) 
            : m_src(std::move(src))
        {}

        std::vector<Token> tokenize();

    private:
        const std::string m_src;
        int m_index = 0;

        // nodiscard tells the compiler that if we dont use the return we have made a mistake
        [[nodiscard]]std::optional<char> peek(int ahead = 0);

        char consume() ;
};