#include <iostream>

#include "lexer.hh";
#include "parser.hh"
#include "print_visitor.hh"
#include "code_gen.hh"

const char* code = " a= 3; a; 5 + a + (1 -3)* 4  /2 ; ";

void test_lex();
void test_parser();
void test_code_gen();

int main(int argc, char** argv) {
    std::cout << "hello world!" << std::endl;

    // test_lex();
    // test_parser();
    test_code_gen();

    return 0;
}

void test_lex() {
    lexer lex(code);
    do {
        lex.get_next_token();
        ::printf("token : %s\n", lex.cur_token->content.c_str());
    } while (lex.cur_token->kind != token_kind::eof);
}

void test_parser() { 
    lexer lex(code);
    lex.get_next_token();
    parser parser(lex);
    print_visitor visitor;
    auto root = parser.parse();
    root->accept(&visitor);
    ::std::cout << visitor.content << ::std::endl;
}

void test_code_gen() {
    lexer lex(code);
    lex.get_next_token();
    parser parser(lex);
    code_gen gen;
    auto root = parser.parse();
    freopen("../../../../../out/asm.s", "w", stdout);
    root->accept(&gen);
    freopen("/dev/tty", "w", stdout);

    // int result = prog();
}