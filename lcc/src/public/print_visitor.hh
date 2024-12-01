#ifndef print_visitor_h
#define print_visitor_h

#include "ast.hh"
#include <cassert>

class print_visitor: public ast_visitor {
public:
    virtual void visit_prog(prog_node* node) override;
private:
    virtual void visit_expr_stmt(expr_stmt_node* node) override;
    virtual void visit_bin(bin_node* node) override;
    virtual void visit_const(const_node* node) override;
    virtual void visit_var_expr(var_expr_node* node) override;
    virtual void visit_assign_expr(assign_expr_node* node) override;
};

#endif