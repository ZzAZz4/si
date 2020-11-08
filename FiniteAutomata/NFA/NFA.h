//
// Created by esteb on 07-Nov-20.
//

#ifndef SI_NFA_H
#define SI_NFA_H

#include <utility>
#include <unordered_set>

#include "../../Misc/Set.h"

struct DFA;

struct NFA
{
    typedef unsigned State;
    typedef unsigned Chr;
    typedef vector<vector<Set>> Function;

    size_t size_{};
    Set b_states{};
    Set f_states{};
    Function function_{};

    NFA (size_t n, vector<State> init, vector<State> f_st, vector<vector<State>> fun);
    NFA (size_t n, Set init, vector<State> f_st, vector<vector<State>> fun);

    [[nodiscard]]
    Set compute (const Set& states, Chr a) const;

    [[nodiscard]]
    bool accepts (const Set& states) const;

    [[nodiscard]]
    DFA to_dfa () const;

    void print ();

};


#endif //SI_NFA_H
