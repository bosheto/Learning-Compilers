#pragma once
#include <string>
#include <sstream>
#include <optional>
#include <vector>

enum class TokenType {
    _exit,
    int_lit,
    semicolon
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

        inline std::vector<Token> tokenize(){
      
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

                // Semicollon
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



    private:
        const std::string m_src;
        int m_index = 0;

        // nodiscard tells the compiler that if we dont use the return we have made a mistake
        [[nodiscard]]inline std::optional<char> peek(int ahead = 1) const {
            if (m_index + ahead > m_src.length()){
                return {};
            }
            else {
                return m_src.at(m_index);
            }
        }

        inline char consume() {
            return m_src.at(m_index++);
        }
};