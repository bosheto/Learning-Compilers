#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include "./inc/tokenization.hpp"
#include "./inc/parser.hpp"
#include "./inc/generator.hpp"

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

    Tokenizer tokenizer(std::move(file_content));
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeExit> root = parser.parse();
    
    if(!root.has_value()){
        std::cerr << "No Nodes generated" << std::endl;
        return EXIT_FAILURE;
    }
    Generator generator(root.value());

    {
        std::fstream file("../out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 ../out.asm -o ../test.o");
    system("ld ../test.o -o ../test");

    return EXIT_SUCCESS;
}