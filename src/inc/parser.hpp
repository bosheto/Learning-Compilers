#pragma once
#include <string>
#include <sstream>
#include <optional>
#include <vector>
#include <iostream>
#include "tokenization.hpp"


    struct NodeExpr {
        Token int_lit;
    };

    struct NodeExit {
        NodeExpr expr;
    };

    
class Parser{
    public:
        inline explicit Parser(std::vector<Token> tokens)
            : m_tokens(std::move(tokens))
            {}
        
        // public Methods
        std::optional<NodeExit> parse();
 
    private:
        size_t m_index = 0;
        const std::vector<Token> m_tokens;

        // nodiscard tells the compiler that if we dont use the return we have made a mistake
        
        [[nodiscard]]std::optional<Token> peek(int offset = 0);

        Token consume();

        std::optional<NodeExpr> parse_expr();

};