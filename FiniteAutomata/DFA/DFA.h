//
// Created by esteb on 07-Nov-20.
//

#ifndef SI_DFA_H
#define SI_DFA_H

#include <utility>
#include <iostream>
#include "../../Misc/Set.h"

struct NFA;

struct DFA
{
    typedef unsigned State;
    typedef unsigned Chr;
    typedef vector<vector<State>> Function;
    typedef vector<vector<int>> Table;

    size_t size_{};
    State b_state{};
    Set f_states{};
    Function function_{};

    DFA (size_t n, State begin, vector<State> f_states, Function fun);

    [[nodiscard]]
    State compute (State state, Chr input) const
    { return function_[state][input]; }

    [[nodiscard]]
    bool accepts (State state) const;

    [[nodiscard]]
    NFA reverse_nfa () const;

    [[nodiscard]]
    Table equivalence_table () const;

    DFA brzozowski_reduce () const;

    void print ();
};

#endif //SI_DFA_H
