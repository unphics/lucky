#ifndef ast_h
#define ast_h

#include <memory>

class ast_visitor;

class ast_node{
public:
    virtual ~ast_node() {};
    virtual void accept(ast_visitor* visit) = 0;
};

enum class bin_op {
    add, sub, mul, div
};

class prog_node: public ast_node {
public:
    ::std::shared_ptr<ast_node> lhs;
    virtual void accept(ast_visitor* visit) override;
};

class bin_node: public ast_node {
public:
    virtual void accept(ast_visitor* visit) override;
    ::std::shared_ptr<ast_node> lhs;
    ::std::shared_ptr<ast_node> rhs;
    typename ::bin_op bin_op;
};

class const_node: public ast_node {
public:
    virtual void accept(ast_visitor* visit) override;
    int value;
};

class ast_visitor {
public:
    virtual void visit_prog(prog_node* node) = 0;
    virtual void visit_bin(bin_node* node) = 0;
    virtual void visit_const(const_node* node) = 0;
};

void prog_node::accept(ast_visitor* visit) {
    visit->visit_prog(this);
}

void bin_node::accept(ast_visitor* visit) {
    visit->visit_bin(this);
}

void const_node::accept(ast_visitor* visit) {
    visit->visit_const(this);
}

#endif