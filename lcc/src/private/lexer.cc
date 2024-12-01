#include "lexer.hh"

#include <cassert>

lexer::lexer(const char* code) {
    this->src_code = code;
}

void lexer::get_next_char() {
    if (this->cursor == this->src_code.size()) {
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
        kind = token_kind::lparen;
        this->get_next_char();
    } else if (this->cur_char == ')') {
        kind = token_kind::rparen;
        this->get_next_char();
    } else if (this->cur_char == ';') {
        kind = token_kind::semic;
        this->get_next_char();
    } else if (this->cur_char == '=') {
        kind = token_kind::assign;
        this->get_next_char();
    } else if (::isdigit(this->cur_char)) {
        value = 0;
        do {
            value = value * 10 + this->cur_char - '0'; // 当前字符的ascii码减去0的ascii码得到当前字符对应的数字
            this->get_next_char();
        } while(::isdigit(this->cur_char));
        kind = token_kind::num;
    } else {
        if (this->is_letter()) {
            while(this->is_letter_or_digit()) {
                this->get_next_char();
            }
            kind = token_kind::ident;
        } else {
            ::printf("not supprot %c \n", this->cur_char);
            assert(0);
        }
    }
    this->cur_token = ::std::make_shared<token>();
    this->cur_token->kind = kind;
    this->cur_token->value = value;
    this->cur_token->content = this->src_code.substr(startpos, this->cursor - 1 - startpos);
}

bool lexer::is_letter() {
    return (this->cur_char >= 'a' && this->cur_char <= 'z') 
        || (this->cur_char >= 'A' && this->cur_char <= 'Z');
}

bool lexer::is_digit() {
    return this->cur_char >= '0' && this->cur_char <= '9';
}
bool lexer::is_letter_or_digit() {
    return this->is_letter() || this->is_digit();
}