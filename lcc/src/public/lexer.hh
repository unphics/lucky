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
    lparent,
    rparent,
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
    ::std::string src_code;
    char cur_char{' '};
    int cursor{0};
};

lexer::lexer(const char* code) {
    this->src_code = code;
}

void lexer::get_next_char() {
    if (this->cursor == this->src_code.size()) {
        // ::printf("error: end of code\n");
        // ::exit(0);
        this->cur_char = '\0';
        this->cursor++;
    } else {
        this->cur_char = this->src_code[this->cursor++];
    }
}

void lexer::get_next_token() {
    while(::isspace(this->cur_char)) {
        this->get_next_char();
    }    
    token_kind kind;
    int value = 0;
    int startpos = this->cursor - 1;
    if (this->cur_char == '\0') {
        kind = token_kind::eof;
        this->get_next_char();
    } else if (this->cur_char == '+') {
        kind = token_kind::add;
        this->get_next_char();
    } else if (this->cur_char == '-') {
        kind = token_kind::sub;
        this->get_next_char();
    } else if (this->cur_char == '*') {
        kind = token_kind::mul;
        this->get_next_char();
    } else if (this->cur_char == '/') {
        kind = token_kind::div;
        this->get_next_char();
    } else if (this->cur_char == '(') {
        kind = token_kind::lparent;
        this->get_next_char();
    } else if (this->cur_char == ')') {
        kind = token_kind::rparent;
        this->get_next_char();
    } else if (::isdigit(this->cur_char)) {
        value = 0;
        do {
            value = value * 10 + this->cur_char - '0'; // 当前字符的ascii码减去0的ascii码得到当前字符对应的数字
            this->get_next_char();
        } while(::isdigit(this->cur_char));
        kind = token_kind::num;
    } else {
        ::printf("not supprot %c \n", this->cur_char);
    }
    this->cur_token = ::std::make_shared<token>();
    this->cur_token->kind = kind;
    this->cur_token->value = value;
    this->cur_token->content = this->src_code.substr(startpos, this->cursor - 1 - startpos);
}

#endif