#include <cwctype>
#include "StateMachine.h"

lex::StateMachine::StateMachine() :
    currentState_{Start},
    transitionTable
    {
        // Transition{StateFrom, Event::Type, StateTo, Action},

        /*Start*/
        Transition{Start, Event::Digit,     DigitDotExponent},
        Transition{Start, Event::Dot,       Skip},
        Transition{Start, Event::Exponent,  DigitAlpha},
        Transition{Start, Event::PlusMinus, Operation},
        Transition{Start, Event::Separator, Operation},
        Transition{Start, Event::Alpha,     DigitAlpha},
        Transition{Start, Event::NoMatch,   Skip},

        /*DigitDotExponent*/
        Transition{DigitDotExponent, Event::Dot,       DigitExponent},
        Transition{DigitDotExponent, Event::Exponent,  DigitOperation},
        Transition{DigitDotExponent, Event::PlusMinus, Number},
        Transition{DigitDotExponent, Event::Separator, Number},
        Transition{DigitDotExponent, Event::Alpha,     Skip},
        Transition{DigitDotExponent, Event::NoMatch,   Skip},

        /*DigitExponent*/
        Transition{DigitExponent, Event::Dot,       Number},
        Transition{DigitExponent, Event::Exponent,  DigitOperation},
        Transition{DigitExponent, Event::PlusMinus, Number},
        Transition{DigitExponent, Event::Separator, Number},
        Transition{DigitExponent, Event::Alpha,     Number},
        Transition{DigitExponent, Event::NoMatch,   Skip},

        /*DigitOperation*/
        Transition{DigitOperation, Event::Digit,     DigitB},
        Transition{DigitOperation, Event::Dot,       Fail},
        Transition{DigitOperation, Event::Exponent,  Fail},
        Transition{DigitOperation, Event::Separator, Fail},
        Transition{DigitOperation, Event::Alpha,     Fail},
        Transition{DigitOperation, Event::NoMatch,   Fail},
        
        /*DigitA*/
        Transition{DigitA, Event::Digit,     DigitB},
        Transition{DigitA, Event::Dot,       Fail},
        Transition{DigitA, Event::Exponent,  Fail},
        Transition{DigitA, Event::PlusMinus, Fail},
        Transition{DigitA, Event::Separator, Fail},
        Transition{DigitA, Event::Alpha,     Fail},
        Transition{DigitA, Event::NoMatch,   Fail},
        
        /*DigitB*/
        Transition{DigitB, Event::Dot,       Number},
        Transition{DigitB, Event::Exponent,  Number},
        Transition{DigitB, Event::PlusMinus, Number},
        Transition{DigitB, Event::Separator, Number},
        Transition{DigitB, Event::Alpha,     Number},
        Transition{DigitB, Event::NoMatch,   Number},
        
        /*DigitAlpha*/
        Transition{DigitAlpha, Event::Dot,       Skip},
        Transition{DigitAlpha, Event::PlusMinus, Name},
        Transition{DigitAlpha, Event::Separator, Name},
        Transition{DigitAlpha, Event::NoMatch,   Skip},
        
        /*Skip*/
        Transition{Skip, Event::PlusMinus, Fail},
        Transition{Skip, Event::Separator, Fail},
        
        /*Number*/
        Transition{Number, Event::Digit,     DigitDotExponent},
        Transition{Number, Event::Dot,       Skip},
        Transition{Number, Event::Exponent,  DigitAlpha},
        Transition{Number, Event::PlusMinus, Operation},
        Transition{Number, Event::Separator, Operation},
        Transition{Number, Event::Alpha,     DigitAlpha},
        Transition{Number, Event::NoMatch,   Skip},
        
        /*Name*/
        Transition{Name, Event::Digit,     DigitDotExponent},
        Transition{Name, Event::Dot,       Skip},
        Transition{Name, Event::Exponent,  DigitAlpha},
        Transition{Name, Event::PlusMinus, Operation},
        Transition{Name, Event::Separator, Operation},
        Transition{Name, Event::Alpha,     DigitAlpha},
        Transition{Name, Event::NoMatch,   Skip},
        
        /*Operation*/
        Transition{Operation, Event::Digit,     DigitDotExponent},
        Transition{Operation, Event::Dot,       Skip},
        Transition{Operation, Event::Exponent,  DigitAlpha},
        Transition{Operation, Event::PlusMinus, Operation},
        Transition{Operation, Event::Separator, Operation},
        Transition{Operation, Event::Alpha,     DigitAlpha},
        Transition{Operation, Event::NoMatch,   Skip},
        
        /*Fail*/
        Transition{Fail, Event::Digit,     DigitDotExponent},
        Transition{Fail, Event::Dot,       Skip},
        Transition{Fail, Event::Exponent,  DigitAlpha},
        Transition{Fail, Event::PlusMinus, Operation},
        Transition{Fail, Event::Separator, Operation},
        Transition{Fail, Event::Alpha,     DigitAlpha},
        Transition{Fail, Event::NoMatch,   Skip},
    } {}

lex::StateMachine::State lex::StateMachine::PostSymbol(wchar_t s)
{
    Transition * t{};
    Event e{s};

    for(std::size_t i = 0; i < transitionTable.size(); ++i)
    {
        t = &transitionTable[i];

        if(currentState_ == t->from_ && e == t->event_)
        {
            currentState_ = t->to_;
            break;
        }  
    }

    return currentState_;
}

lex::StateMachine::Event::Event(wchar_t s)
{
    type_ = Type::NoMatch;

    switch (s)
    {
        case L'.':
            type_ = Type::Dot;
            break;

        case L'E':
        case L'e':
            type_ = Type::Exponent;
            break;

        case L'+':
        case L'-':
            type_ = Type::PlusMinus;
            break;

        case L'*': case L'/':
        case L'(': case L')':
        case L';': case L'\n':
            type_ = Type::Separator;
            break;

        default:
            if (std::iswdigit(s) )
                type_ = Type::Digit;
            if (std::iswalpha(s) || s == L'_')
                type_ = Type::Alpha;
            if (std::iswspace(s) )
                type_ = Type::Separator;
    }
}