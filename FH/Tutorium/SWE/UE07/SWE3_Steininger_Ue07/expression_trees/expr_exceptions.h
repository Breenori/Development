#ifndef EXPRESSION_TREE_EXPR_EXCEPTIONS_H
#define EXPRESSION_TREE_EXPR_EXCEPTIONS_H

#include <exception>

namespace xpr{
    class EvaluationException : public std::exception{
    public:
        virtual const char* what() const noexcept{
            return "Evaluation Exception: Unable to evaluate expression tree!\n";
        }

    };


}



#endif //EXPRESSION_TREE_EXPR_EXCEPTIONS_H
