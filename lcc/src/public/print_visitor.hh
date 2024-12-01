#ifndef print_visitor_h
#define print_visitor_h

#include "ast.hh"
#include <cassert>

class print_visitor: public ast_visitor {
public:
    virtual void visit_prog(prog_node* node) override;
    virtual void visit_bin(bin_node* node) override;
    virtual void visit_const(const_node* node) override;
};

void print_visitor::visit_prog(prog_node* node) {
    node->lhs->accept(this);
    ::printf(" \n");
}
void print_visitor::visit_bin(bin_node* node) {
    node->rhs->accept(this);
    node->lhs->accept(this);
    switch (node->bin_op) {
        case bin_op::add: ::printf("+ "); break;
        case bin_op::sub: ::printf("- "); break;
        case bin_op::mul: ::printf("* "); break;
        case bin_op::div: ::printf("/ "); break;
        default: assert(0); break;
    }
}
void print_visitor::visit_const(const_node* node) {
    ::printf("%d ", node->value);
}
#endif