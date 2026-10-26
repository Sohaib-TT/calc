#pragma once

#include "exprtk.hpp"
#include "nodes.hpp"
#include "displaybuilder.hpp"

#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>



inline std::string replace_all_tokens(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

inline std::string evaluate_expression(std::string expr_str) {
    // 1. Translate 'ln' to ExprTk's native 'log' function
    expr_str = replace_all_tokens(expr_str, "log", "log10");
    expr_str = replace_all_tokens(expr_str, "ln", "log");

    using T = double;
    exprtk::expression<T> expression;
    exprtk::parser<T> parser;
    
    exprtk::symbol_table<T> symbol_table;
    symbol_table.add_constants();

    T i_val = 0.0; 
    symbol_table.add_variable("I", i_val);

    expression.register_symbol_table(symbol_table);

    if (!parser.compile(expr_str, expression)) {
        return "Syntax Error";
    }

    T result = expression.value();

    if (std::isnan(result)) {
        return "Not a Real Number";
    }
    if (std::isinf(result)) {
        return "Division by Zero";
    }

    std::ostringstream stream;
    stream << result;
    return stream.str();
}


inline std::string calculate(Node* head,Node** cursor){
    std::string equation = "";
    Node* node = head;
    
    if(node->next == NULL){return "";}
    while(node->next!=NULL){node = node->next;equation+= node->value;}
    std::string result = evaluate_expression(equation);
    switch (result[0])
    {
    case 'S':case 'N':case 'D':
        return result;
        break;
    
    default:
        
        ac(head,cursor);
        for ( int i = 0; i < result.length(); i++){
            add(cursor,std::string(1,result[i]));
        }
        return "2";
        break;
    }
}