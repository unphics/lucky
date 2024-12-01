#ifndef code_gen_h
#define code_gen_h

#include "ast.hh"
#include <cassert>

class code_gen: public ast_visitor {
public:
    code_gen() {}
    virtual void visit_prog(prog_node* node) override;
private:
    virtual void visit_bin(bin_node* node) override;
    virtual void visit_const(const_node* node) override;
    void push();
    void pop(const char* reg);
    int stack_level{0};
};

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
    ::printf("\tpush %%rbp\n");
    ::printf("\tmov %%rsp, %%rbp\n");
    ::printf("\tsub $32, %%rsp\n"); // 开32字节栈空间

    node->lhs->accept(this);
    assert(this->stack_level == 0);

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

#endif