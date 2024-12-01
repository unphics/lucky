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

struct src_loc {
    int line;
    int col;
};

class token {
public:
    token_kind kind;
    int value;
    ::std::string content;
    src_loc loc;
};

class lexer {
public:
    lexer(const char* code);
    void get_next_token();
    void get_next_char();
    void expect_token(token_kind kind);
    ::std::shared_ptr<token> cur_token;
    ::std::string src_code;
private:
    bool is_letter();
    bool is_digit();
    bool is_letter_or_digit();
    const char* get_token_simple_spelling(token_kind kind);
    char cur_char{' '};
    int cursor{0};
    int line{0};
    int line_head{0};
};

#endif