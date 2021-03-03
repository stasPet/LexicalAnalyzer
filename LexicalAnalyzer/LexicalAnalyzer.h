#ifndef DEFINE_LEX_LEXICAL_ANALYZER
#define DEFINE_LEX_LEXICAL_ANALYZER

#include "Buffer.h"
#include "Lexeme.h"

#include <forward_list>

namespace lex
{
    class LexicalAnalyzer
    {
    private:
        Lexeme RefineLexeme(Buffer::Lexeme &);
        Lexeme RefineName(Buffer::Lexeme &);
        Lexeme RefineOperation(Buffer::Lexeme &);

        Lexeme::Type pastLexeme_;
        bool IsUnary(Lexeme::Type);

        std::forward_list<std::wstring> functionNames_;

    public:
        LexicalAnalyzer(std::initializer_list<std::wstring> =
                {L"sin", L"cos", L"tan", L"sqrt"} );

        std::queue<Lexeme> Convert(Buffer);
    };

    inline LexicalAnalyzer::LexicalAnalyzer(
        std::initializer_list<std::wstring> l) :
            functionNames_{l}
    {
        // ...
    }
}

#endif // DEFINE_LEX_LEXICAL_ANALYZER