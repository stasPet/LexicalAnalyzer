#ifndef DEFINE_LEX_STATE_MACHINE
#define DEFINE_LEX_STATE_MACHINE

#include <array>

namespace lex
{
    class StateMachine
    {
    public:
        enum State
        {
            Start,  DigitDotExponent, DigitExponent, DigitOperation,
            DigitA, DigitB,           DigitAlpha,    Skip,
            Number, Name,             Operation,     Fail
        };

    private:
        class Event
        {
        public:
            enum Type
            {
                Digit,     Dot,   Exponent, PlusMinus,
                Separator, Alpha, NoMatch
            };

            Event(wchar_t); 
            bool operator==(Type) const;

            Type type_;
        };

        struct Transition
        {
            State from_;
            Event::Type event_;
            State to_;

            Transition(State, Event::Type, State);
        };

        std::array<Transition, 72> transitionTable;
        State currentState_;

    public:
        StateMachine();

        State PostSymbol(wchar_t);
        void Reset();
    };

    inline void StateMachine::Reset()
    {
        currentState_ = Start;
    }

    inline StateMachine::Transition::Transition(
        State f, Event::Type e, State t) : from_{f}, event_{e}, to_{t} {}

    inline bool StateMachine::Event::operator==(Type t) const
    {
        return type_ == t;
    }
}

#endif // DEFINE_LEX_STATE_MACHINE