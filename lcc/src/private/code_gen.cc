#include "code_gen.hh"

#include "stdio.h"

void code_gen::visit_prog(prog_node* node) {

#ifdef __linux__
    ::printf("\t.text\n");
    ::printf("\t.globl  prog\n");
    ::printf("prog:\n");
#else
    // ::printf("\t.globl  _prog\n");
    // ::printf("_prog:\n");
    ::printf("\t.code\n");
    ::printf("\tPUBLIC  prog\n");
    ::printf("prog PROC\n");
#endif

    int stack_size = 0;
    for (auto& v : node->local_vars) {
        stack_size += 8;
        v->offset = stack_size * -1;
    }

    ::printf("\tpush %%rbp\n");
    ::printf("\tmov %%rsp, %%rbp\n");
    ::printf("\tsub $%d, %%rsp\n", stack_size); // 开32字节栈空间

    for (auto& s : node->stmts) {
        s->accept(this);
        assert(this->stack_level == 0);
    }

    ::printf("\tmov %%rbp, %%rsp\n");
    ::printf("\tpop %%rbp\n");
    ::printf("\tret\n");
#ifndef __linux__
    ::printf("\tprog END\n");
    ::printf("\tEND\n");
#endif
}

void code_gen::visit_bin(bin_node* node) {
    node->rhs->accept(this);
    this->push();
    node->lhs->accept(this);
    this->pop("%rdi");
    switch (node->bin_op) {
    case bin_op::add : ::printf("\tadd %%rdi, %%rax\n"); break;
    case bin_op::sub : ::printf("\tsub %%rdi, %%rax\n"); break;
    case bin_op::mul : ::printf("\timul %%rdi, %%rax\n"); break;
    case bin_op::div :
        ::printf("\tcqo\n");
        ::printf("\tidiv %%rdi\n");
        break;
    default: assert(0); break;
    }
}

void code_gen::visit_const(const_node* node) {
    ::printf("\tmov $%d, %%rax\n", node->value);
}

void code_gen::push() {
    ::printf("\tpush %%rax\n");
    this->stack_level++;
}

void code_gen::pop(const char* reg) {
    ::printf("\tpop %s\n", reg);
    this->stack_level--;
}

void code_gen::visit_expr_stmt(expr_stmt_node* node) {
    node->lhs->accept(this);
}

void code_gen::visit_var_expr(var_expr_node* node) {
    ::printf("\tlea %d(%%rbp), %%rax\n", node->var_obj->offset);
    ::printf("\tmov (%%rax), %%rax\n");
}

void code_gen::visit_assign_expr(assign_expr_node* node) {
    auto var_node = std::dynamic_pointer_cast<var_expr_node>(node->lhs);
    assert(var_node != nullptr);
    ::printf("\tlea %d(%%rbp), %%rax\n", var_node->var_obj->offset);
    this->push();
    node->rhs->accept(this);
    this->pop("%rdi");
    ::printf("\tmov %%rax, (%%rdi)\n");
}

