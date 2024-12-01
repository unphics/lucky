#include "print_visitor.hh"

#include <string>

void print_visitor::visit_prog(prog_node* node) {
    for (auto& s : node->stmts) {
        s->accept(this);
    }
}

void print_visitor::visit_expr_stmt(expr_stmt_node* node) {
    node->lhs->accept(this);
    this->content += ";";
}

void print_visitor::visit_bin(bin_node* node) {
    node->lhs->accept(this);
    switch (node->bin_op) {
        case bin_op::add: this->content += "+ "; break;
        case bin_op::sub: this->content += "- "; break;
        case bin_op::mul: this->content += "* "; break;
        case bin_op::div: this->content += "/ "; break;
        default: assert(0); break;
    }
    node->rhs->accept(this);
}

void print_visitor::visit_const(const_node* node) {
    this->content += ::std::to_string(node->value);
    this->content += " ";
}

void print_visitor::visit_var_expr(var_expr_node* node) {
    this->content += node->var_obj->name;
}

void print_visitor::visit_assign_expr(assign_expr_node* node) {
    node->lhs->accept(this);
    this->content += '=';
    node->rhs->accept(this);
}