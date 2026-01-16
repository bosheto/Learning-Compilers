#include "inc/tokenization.hpp"

/*
    
*/
char Tokenizer::consume(){
    return m_src.at(m_index++);
}


std::optional<char> Tokenizer::peek(int offset)  {
    if (m_index + offset >= m_src.size()){
        return {};
    }
    else {
        return m_src.at(m_index + offset);
    }
}


std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens {};
    std::string buffer;
    
    while(peek().has_value()){
        
        // Keywords 
        if(std::isalpha(peek().value())){
            buffer.push_back(consume());
            
            while(peek().has_value() && std::isalnum(peek().value())){
                buffer.push_back(consume());
            }

            if(buffer == "exit"){
                tokens.push_back({.type=TokenType::_exit});
                buffer.clear();
                continue;
            }
            else{
                std::cerr << "Error in source code!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        
        // Integer literals 
        else if (std::isdigit(peek().value())){
            buffer.push_back(consume());

            while (peek().has_value() && std::isdigit(peek().value()))
            {
                buffer.push_back(consume());
            }

            tokens.push_back({.type=TokenType::int_lit, .value=buffer});
            buffer.clear();
            
        }
        // Open parenthesis
        else if (peek().value() == '(') {
            consume();
            tokens.push_back({.type=TokenType::open_parenthesis});            
        }
        // Close parenthesis
        else if (peek().value() == ')'){
            consume();
            tokens.push_back({.type=TokenType::close_parenthesis});
        }
        // Semicolon
        else if(peek().value() == ';') {
            consume();
            tokens.push_back({.type=TokenType::semicolon});
            continue;
        }

        //White space
        else if (std::isspace(peek().value())){
            consume();
            continue;
        } else {
                std::cerr << "Error in source code! end of token tree!" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    m_index = 0;
    return tokens;
}