#ifndef ast_h
#define ast_h

#include <memory>
#include <list>

class ast_visitor;

class ast_node{
public:
    virtual ~ast_node() {};
    virtual void accept(ast_visitor* visit) = 0;
};

enum class bin_op {
    add, sub, mul, div
};

class var {
public:
    std::string name;
    int offset;
};

class prog_node: public ast_node {
public:
    ::std::list<::std::shared_ptr<ast_node>> stmts;
    ::std::list<::std::shared_ptr<var>> local_vars;
    virtual void accept(ast_visitor* visit) override;
};

class expr_stmt_node: public ast_node {
public:
    ::std::shared_ptr<ast_node> lhs;
    virtual void accept(ast_visitor* visit) override;
};

class assign_expr_node: public ast_node {
public:
    ::std::shared_ptr<ast_node> lhs;
    ::std::shared_ptr<ast_node> rhs;
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

class var_expr_node: public ast_node {
public:
    ::std::shared_ptr<var> var_obj;
    virtual void accept(ast_visitor* visit) override;
};

class ast_visitor {
public:
    ::std::string content;
    virtual void visit_prog(prog_node* node) = 0;
    virtual void visit_expr_stmt(expr_stmt_node* node) = 0;
    virtual void visit_bin(bin_node* node) = 0;
    virtual void visit_const(const_node* node) = 0;
    virtual void visit_var_expr(var_expr_node* node) = 0;
    virtual void visit_assign_expr(assign_expr_node* node) = 0;
};

#endif