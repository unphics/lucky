#ifndef parser_h
#define parser_h

#include "lexer.hh"
#include "ast.hh"
#include <memory>
#include <list>
#include <unordered_map>

class parser {
public:
    parser(lexer& lex);
    ::std::shared_ptr<prog_node> parse();
private:
    ::std::shared_ptr<ast_node> parse_stmt();
    ::std::shared_ptr<ast_node> parse_expr();
    ::std::shared_ptr<ast_node> parse_add_expr();
    ::std::shared_ptr<ast_node> parse_mul_expr();
    ::std::shared_ptr<ast_node> parse_prim_expr(); // primary
    ::std::shared_ptr<ast_node> parse_assign_expr();
    ::std::shared_ptr<var> find_local_var(::std::string name);
    ::std::shared_ptr<var> make_local_var(::std::string name);
    lexer& lex;
    ::std::list<::std::shared_ptr<var>>* local_vars{nullptr};
    ::std::unordered_map<::std::string, ::std::shared_ptr<var>> locals_map;
};

#endif