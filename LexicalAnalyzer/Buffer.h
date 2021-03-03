#ifndef DEFINE_LEX_EXPRESSION
#define DEFINE_LEX_EXPRESSION

#include <vector>
#include <queue>
#include <memory>
#include <string>

#include "StateMachine.h"

namespace lex
{
    class Buffer
    {
    public:
        using LexemeT = StateMachine::State;

        struct Lexeme
        {
            LexemeT type;
            std::wstring value;

            Lexeme(LexemeT, std::wstring);
        };

    private:
        using StorageT = std::vector<Lexeme>;

        StorageT storege_;
        StateMachine stateMachine_;

    public:
        Buffer() = default;
        Buffer(std::queue<wchar_t> );

        void Initialize(std::queue<wchar_t> );
        StorageT::size_type Size();

        Lexeme & operator[](std::size_t);
        Lexeme const & operator[](std::size_t) const;
    };

    inline Buffer::Buffer(std::queue<wchar_t> b)
    {
        Initialize(std::move(b) );
    }

    inline Buffer::Lexeme & Buffer::operator[](std::size_t i)
    {
        return storege_[i];
    }
    inline  Buffer::Lexeme const & Buffer::operator[](std::size_t i) const
    {
        return storege_[i];
    }

    inline Buffer::Lexeme::Lexeme(LexemeT t, std::wstring s) :
        type{t}, value{std::move(s) }
    {
        // ...
    }

    inline Buffer::StorageT::size_type Buffer::Size()
    {
        return storege_.size();
    }
}

#endif // DEFINE_LEX_EXPRESSION
