#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_lit,
    semicolon
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenize(const std::string input) {
    
    std::vector<Token> tokens;
    std::string buffer;
    for(int i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if (std::isalpha(c)){

            buffer.push_back(c);
            i++;
            while(std::isalnum(input.at(i))){
                buffer.push_back(input.at(i));
                i++;
            }
            i--;
            if(buffer == "return"){
                tokens.push_back({.type=TokenType::_return});
                buffer.clear();
                continue;
            }else{
                std::cerr << "Error in code" << std::endl;
                exit(EXIT_FAILURE);
            }
        }else if(std::isdigit(c)){
            buffer.push_back(c);
            i++;
            while (std::isdigit(input.at(i))){
                buffer.push_back(input.at(i));
                i++;
            }   
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value=buffer});
            buffer.clear();
        }else if(c == ';'){
            tokens.push_back({.type = TokenType::semicolon});
        }else if (std::isspace(c)) {
            continue;
        }else {
            std::cerr << "Error in code" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return tokens; 
}

std::string tokens_to_asm(const std::vector<Token> tokens){
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (int i = 0 ; i < tokens.size(); i++){
        const Token token = tokens.at(i);
        if (token.type == TokenType::_return){
            if (i+1 < tokens.size() && tokens.at(i+1).type == TokenType::int_lit){
                if(i + 2 < tokens.size() && tokens.at(i+2).type == TokenType::semicolon){
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i + 1).value.value() << "\n";
                    output << "    syscall\n";
                }
            }
        }
    }
    return output.str();
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "No input file specified" << std::endl;
        return EXIT_FAILURE;
    }


    std::string file_content;
    // Load file into memory
    std::fstream input(argv[1], std::ios::in);

    // Create buffer and read file into it.
    std::stringstream content_stream;
    content_stream << input.rdbuf(); 
    file_content = content_stream.str();
    // Close file 
    input.close();

    std::vector<Token> tokens = tokenize(file_content);
    // std::cout << tokens_to_asm(tokens) << std::endl;


    {
        std::fstream file("../out.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }

    system("nasm -felf64 ../out.asm -o ../test.o");
    system("ld ../test.o -o ../test");

    return EXIT_SUCCESS;
}