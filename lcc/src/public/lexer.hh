#ifndef lexer_h
#define lexer_h

#include <string>
#include <memory>

enum class token_kind {
    add,
    sub,
    mul,
    div,
    num,
    lparen,
    rparen,
    ident, // identifier 标识符
    semic, // semicolon 分号
    assign,
    eof,
};

class token {
public:
    token_kind kind;
    int value;
    ::std::string content;
};

class lexer {
public:
    lexer(const char* code);
    void get_next_token();
    void get_next_char();
    ::std::shared_ptr<token> cur_token;
private:
    bool is_letter();
    bool is_digit();
    bool is_letter_or_digit();
    ::std::string src_code;
    char cur_char{' '};
    int cursor{0};
};

#endif