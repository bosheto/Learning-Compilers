#pragma once
#include <string>
#include <sstream>
#include <optional>
#include <vector>
#include <iostream>
#include "./tokenization.hpp"


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
        
        inline std::optional<NodeExpr> parse_expr() {
            if (peek().has_value() && peek().value().type == TokenType::int_lit) {
                return NodeExpr{.int_lit = consume()};
            }else{
                // this means return null. C++ is weird.
                return {};
            }
        }

        inline std::optional<NodeExit> parse(){
            std::optional<NodeExit> root;
            
            while (peek().has_value())
            {
                if(peek().value().type == TokenType::_exit){

                    consume();
                    /*  
                        Using auto is clever since the return of parse_expr is an optional 
                        If it dosent have a value it will evaluate to false and go to the else block
                        if it has a value it will evaluate to true and we keep the value. Quite cool.
                    */
                    if (auto node_expr = parse_expr()){
                        root = NodeExit { .expr = node_expr.value()}; 
                    }else {
                        std::cerr << "Invalid expression" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    if(peek().has_value() || peek().value().type == TokenType::semicolon){
                        consume();
                    }else{
                        std::cerr << "Invalid expression" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }

            m_index = 0;
            return root;
        };

    private:
        size_t m_index = 0;
        const std::vector<Token> m_tokens;

                // nodiscard tells the compiler that if we dont use the return we have made a mistake
        [[nodiscard]]inline std::optional<Token> peek(int ahead = 1) const {
            if (m_index + ahead > m_tokens.size()){
                return {};
            }
            else {
                return m_tokens.at(m_index);
            }
        }

        inline Token consume() {
            return m_tokens.at(m_index++);
        }
};