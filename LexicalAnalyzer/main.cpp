#include "LexicalAnalyzer.h"

int main()
{
    std::queue<wchar_t> q;
    std::wstring s{L"(-1+a)*$4830/1.0e-1*sqrt;"};

    for (auto c : s) q.emplace(c);
    auto e{lex::LexicalAnalyzer{}.Convert(q) };

    return 0;
}