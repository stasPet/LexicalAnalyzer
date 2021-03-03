#include "LexicalAnalyzer.h"

std::queue<lex::Lexeme> lex::LexicalAnalyzer::Convert(Buffer b)
{
    std::queue<Lexeme> result;
    pastLexeme_ = Lexeme::Empty;

    for (std::size_t i{}; i < b.Size(); ++i)
        result.emplace(RefineLexeme(b[i] ) );

    return result;
}

lex::Lexeme lex::LexicalAnalyzer::RefineLexeme(Buffer::Lexeme & l)
{
    Lexeme rl;

    switch (l.type)
    {
    case Buffer::LexemeT::Operation:
        rl = RefineOperation(l);
        break;

    case Buffer::LexemeT::Name:
        rl = RefineName(l);
        break;

    case Buffer::LexemeT::Number:
        rl = Lexeme{Lexeme::Number, std::move(l.value) };
        break;

    case Buffer::LexemeT::Fail:
        rl = Lexeme{Lexeme::Bad, std::move(l.value) };
        break;
    }

    if (IsUnary(rl.type) )
        rl.type = Lexeme::Not;

    pastLexeme_ = rl.type;

    return rl;
}

lex::Lexeme lex::LexicalAnalyzer::RefineName(Buffer::Lexeme & l)
{
    Lexeme::Type type{Lexeme::Name};

    for (std::wstring const & r : functionNames_)
    {
        if (r == l.value)
            type = Lexeme::Call;
    }

    return Lexeme{type, std::move(l.value) };
}

lex::Lexeme lex::LexicalAnalyzer::RefineOperation(Buffer::Lexeme & l)
{
    Lexeme::Type type;

    switch (l.value[0] )
    {
    case L'*':
        type = Lexeme::Multiplication;
        break;

    case L'/':
        type = Lexeme::Division;
        break;

    case L'+':
        type = Lexeme::Addition;
        break;

    case L'-':
        type = Lexeme::Subtraction;
        break;

    case L'(':
        type = Lexeme::LeftParenthesis;
        break;

    case L')':
        type = Lexeme::RightParenthesis;
        break;

    case L';': case L'\n':
        type = Lexeme::End;
        break;
    }

    return Lexeme{type, std::move(l.value) };
}

bool lex::LexicalAnalyzer::IsUnary(Lexeme::Type t)
{
    return t == Lexeme::Subtraction &&
        (pastLexeme_ == Lexeme::LeftParenthesis ||
         pastLexeme_ == Lexeme::Multiplication ||
         pastLexeme_ == Lexeme::Division ||
         pastLexeme_ == Lexeme::Addition ||
         pastLexeme_ == Lexeme::Subtraction ||
         pastLexeme_ == Lexeme::Not ||
         pastLexeme_ == Lexeme::Empty);
}