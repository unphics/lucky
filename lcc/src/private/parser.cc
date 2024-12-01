#include "parser.hh"

#include <cassert>

parser::parser(lexer& lex) : lex(lex) {}

::std::shared_ptr<prog_node> parser::parse() {
    auto node = ::std::make_shared<prog_node>();
    // node->lhs = this->parse_expr();
    this->local_vars = &node->local_vars;
    while(this->lex.cur_token->kind != token_kind::eof) {
        node->stmts.push_back(this->parse_stmt());
    }
    return node;
}

::std::shared_ptr<ast_node> parser::parse_stmt() {
    auto node = ::std::make_shared<expr_stmt_node>();
    node->lhs = this->parse_expr();
    assert(this->lex.cur_token->kind == token_kind::semic);
    this->lex.get_next_token();
    return node;
}

::std::shared_ptr<ast_node> parser::parse_expr() {
    return this->parse_assign_expr();
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
    if (this->lex.cur_token->kind == token_kind::lparen) {
        this->lex.get_next_token();
        auto node = this->parse_expr();
        this->lex.get_next_token();
        return node;
    } else if (this->lex.cur_token->kind == token_kind::num) {
        auto node = ::std::make_shared<const_node>();
        node->value = lex.cur_token->value;
        this->lex.get_next_token();
        return node;
    } else if (this->lex.cur_token->kind == token_kind::ident) {
        auto node = ::std::make_shared<var_expr_node>();
        auto var = this->find_local_var(this->lex.cur_token->content);
        if (!var) {
            var = this->make_local_var(this->lex.cur_token->content);
        }
        node->var_obj = var;
        this->lex.get_next_token();
        return node;
    } else {
        ::printf("not support !!!");
        assert(0);
    }
}

::std::shared_ptr<ast_node> parser::parse_assign_expr() {
    auto left = this->parse_add_expr();
    if (this->lex.cur_token->kind == token_kind::assign) {
        this->lex.get_next_token();
        auto node = ::std::make_shared<assign_expr_node>();
        node->lhs = left;
        node->rhs = this->parse_assign_expr();
        return node;
    }
    return left;
}

::std::shared_ptr<var> parser::find_local_var(::std::string name) {
    if (this->locals_map.find(name) != this->locals_map.end()) {
        return this->locals_map[name];
    }
    return nullptr;
}

::std::shared_ptr<var> parser::make_local_var(std::string name) {
    auto obj = ::std::make_shared<var>();
    obj->name = name;
    obj->offset = 0;
    this->local_vars->push_front(obj);
    this->locals_map[name] = obj;
    return obj;
}