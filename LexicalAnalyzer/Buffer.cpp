#include "Buffer.h"

void lex::Buffer::Initialize(std::queue<wchar_t> b)
{
    stateMachine_.Reset();

    std::wstring wStringBuffer;
    std::wstring::value_type wCharBuffer;
    LexemeT ls;

    while (!b.empty() )
    {
        wCharBuffer = b.front();
        ls = stateMachine_.PostSymbol(wCharBuffer);

        switch (ls)
        {
            case StateMachine::Number:
            {
                storege_.emplace_back(ls,
                    std::move(wStringBuffer) );
                break;
            }
            case StateMachine::Name:
            {
                storege_.emplace_back(ls,
                    std::move(wStringBuffer) );
                break;
            }
            case StateMachine::Fail:
            {
                storege_.emplace_back(ls,
                    std::move(wStringBuffer) );
                break;
            }
            case StateMachine::Operation:
            {
                std::wstring temp{wCharBuffer};
                storege_.emplace_back(ls, temp);
                b.pop();
                break;
            }
            default:
                wStringBuffer += wCharBuffer;
                b.pop();
                break;
        }
    }
}