#include "inc/parser.hpp"


/*  16/01/26 
    Get a token from the list, return it and move the index +1
    Usually we are getting the token from the peek function so most of 
    the time we dont't consume the value and only use this to move the 
    index.
    author: Boris Gezkovski
*/
Token Parser::consume(){
    return m_tokens.at(m_index++);
}

/*
    16/01/26
    This does a similar thing to consume but its also checks if they are more tokens
    to consume. If we have a token we usaly get it from here and then call consume to move
    the index +1
    author: Boris Gezkovski
*/
std::optional<Token> Parser::peek(int offset){
    if (m_index + offset >= m_tokens.size()){
        return {};
    }
    else {
        return m_tokens.at(m_index + offset);
    }
}

/*
    16/01/26
    Parses a NodeExpr from a token, we check if the TokenType is int literal 
    if true we return a new NodeExpr node with .int_lit value = token, also moves 
    index +1 through consume.
    If false it returns null.
    author: Boris Gezkovski
*/
std::optional<NodeExpr> Parser::parse_expr() {
    if (peek().has_value() && peek().value().type == TokenType::int_lit) {
        return NodeExpr{.int_lit = consume()};
    }else{
        // this means return null. C++ is weird.
        return {};
    }
}

/*
    16/01/26
    ----- WILL BE REFACTORED ----
    Parses the tokens and returns a NodeExit

*/
std::optional<NodeExit> Parser::parse() {
    std::optional<NodeExit> root;
    
    while (peek().has_value())
    {
        if( peek().value().type == TokenType::_exit && peek(1).has_value() 
            && peek(1).value().type == TokenType::open_parenthesis){

            consume(); // consume exit keyword
            consume(); // consume ( 
            /*  
                Using auto is clever since the return of parse_expr is an optional 
                If it doesn't have a value it will evaluate to false and go to the else block
                if it has a value it will evaluate to true and we keep the value. Quite cool.
            */
            if (auto node_expr = parse_expr()){
                root = NodeExit { .expr = node_expr.value()}; // consume expresion 
            }else {
                std::cerr << "Invalid expression" << std::endl;
                exit(EXIT_FAILURE);
            }
            
            if(peek().has_value() && peek().value().type == TokenType::close_parenthesis){
                consume(); // Consume ')' 
            }else{
                std::cerr << "Missing )!" << std::endl;
                exit(EXIT_FAILURE);
            }

            // Semicolon
            if(peek().has_value() && peek().value().type == TokenType::semicolon){
                consume();
            }else{
                std::cerr << "Missing ;" << std::endl;
                exit(EXIT_FAILURE);
            }
        }else{
            std::cerr << "      Error in syntax no opening ( <-------------" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    m_index = 0;
    return root;
}

