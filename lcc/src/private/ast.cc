#include "ast.hh"


void prog_node::accept(ast_visitor* visit) {
    visit->visit_prog(this);
}

void expr_stmt_node::accept(ast_visitor* visit) {
    visit->visit_expr_stmt(this);
}

void bin_node::accept(ast_visitor* visit) {
    visit->visit_bin(this);
}

void const_node::accept(ast_visitor* visit) {
    visit->visit_const(this);
}

void var_expr_node::accept(ast_visitor* visit) {
    visit->visit_var_expr(this);
}

void assign_expr_node::accept(ast_visitor* visit) {
    visit->visit_assign_expr(this);
}