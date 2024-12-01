#ifndef parser_h
#define parser_h

#include "lexer.hh"
#include "ast.hh"
#include <memory>

class parser {
public:
    parser(lexer& lex);
    ::std::shared_ptr<prog_node> parse();
private:
    lexer& lex;
    ::std::shared_ptr<ast_node> parse_expr();
    ::std::shared_ptr<ast_node> parse_add_expr();
    ::std::shared_ptr<ast_node> parse_mul_expr();
    ::std::shared_ptr<ast_node> parse_prim_expr(); // primary
};

parser::parser(lexer& lex) : lex(lex) {}

::std::shared_ptr<prog_node> parser::parse() {
    auto node = ::std::make_shared<prog_node>();
    node->lhs = this->parse_expr();
    return node;
}

::std::shared_ptr<ast_node> parser::parse_expr() {
    return this->parse_add_expr();
}

::std::shared_ptr<ast_node> parser::parse_add_expr() {
    auto left = this->parse_mul_expr();
    while(this->lex.cur_token->kind == token_kind::add || this->lex.cur_token->kind == token_kind::sub) {
        bin_op an_op = bin_op::add;
        if (this->lex.cur_token->kind == token_kind::sub) an_op = bin_op::sub;
        this->lex.get_next_token();
        auto node = ::std::make_shared<bin_node>();
        node->bin_op = an_op;
        node->lhs = left;
        node->rhs = this->parse_mul_expr();
        left = node;
    }
    return left;
}

::std::shared_ptr<ast_node> parser::parse_mul_expr() {
    auto left = this->parse_prim_expr();
    while(this->lex.cur_token->kind == token_kind::mul || this->lex.cur_token->kind == token_kind::div) {
        bin_op an_op = bin_op::mul;
        if (this->lex.cur_token->kind == token_kind::div) an_op = bin_op::div;
        this->lex.get_next_token();
        auto node = ::std::make_shared<bin_node>();
        node->bin_op = an_op;
        node->lhs = left;
        node->rhs = this->parse_prim_expr();
        left = node;
    }
    return left;
}

::std::shared_ptr<ast_node> parser::parse_prim_expr() {
    if (this->lex.cur_token->kind == token_kind::lparent) {
        this->lex.get_next_token();
        auto node = this->parse_expr();
        this->lex.get_next_token();
        return node;
    } else {
        auto node = ::std::make_shared<const_node>();
        node->value = lex.cur_token->value;
        this->lex.get_next_token();
        return node;
    }
}


#endif