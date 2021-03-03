#ifndef DEFINE_LEX_LEXEME
#define DEFINE_LEX_LEXEME

#include <string>

namespace lex
{
    struct Lexeme
    {
    public:
        enum Type
        {
            Name,
            Number,
            Operation,
            Variable,
            Call,
            Multiplication,
            Division,
            Addition,
            Subtraction,
            Not,
            LeftParenthesis,
            RightParenthesis,  
            End,
            Bad,
            Empty
        };

        Type type;
        std::wstring stringValue;

        explicit Lexeme(Type t = Type::Empty, std::wstring = std::wstring{} );
    };

    inline Lexeme::Lexeme(Type t, std::wstring s) :
        type{t}, stringValue{std::move(s) } {}
}

#endif // LEX_DEFINE_LEXEME