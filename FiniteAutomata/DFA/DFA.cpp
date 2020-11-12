#include "DFA.h"
#include "../NFA/NFA.h"

NFA DFA::revert_as_nfa () const
{
    vector<vector<State>> rev_function;
    for (State input = 0; input < function_.size(); ++input)
        for (const Chr& chr : { 0u, 1u })
            rev_function.emplace_back(vector{ function_[input][chr], chr, input });

    return NFA(size_, f_states.elements, vector{ b_state }, rev_function);
}

void DFA::print ()
{
    cout << size_ << ' ' << b_state << ' ' << f_states.size();
    for (const auto& i : f_states)
        cout << ' ' << i;
    endl(cout);

    for (size_t i = 0; i < function_.size(); ++i)
        for (int a : { 0, 1 })
            cout << i << ' ' << a << ' ' << function_[i][a] << '\n';
}

bool DFA::accepts (State state) const
{ return f_states.contains(state); }

DFA::DFA (
    size_t n, DFA::State begin, vector<State> f_states,
    Function fun)
    : size_(n),
      b_state(begin),
      f_states(move(f_states))
{
    function_.resize(size_, vector<State>(2, 0));
    for (const auto& trans : fun)
        function_[trans[0]][trans[1]] = trans[2];
}

DFA DFA::brzozowski_reduce () const
{
    return this->revert_as_nfa().to_dfa().revert_as_nfa().to_dfa();
}

vector<vector<int>> DFA::equivalence_table () const
{
    Table table(size_, vector<int>(size_, 0));

    for (State i = 0; i < size_; ++i)
        for (State j = 0; j < i; ++j)
            if (accepts(i) ^ accepts(j))
                table[i][j] = table[j][i] = 1;

    while (true)
    {
        bool modified = false;
        for (State i = 0; i < size_; ++i)
            for (State j = 0; j < i; ++j)
                if (!table[i][j])
                    for (const Chr& a : { 0u, 1u })
                        if (table[compute(i, a)][compute(j, a)])
                        {
                            table[i][j] = table[j][i] = 1;
                            modified = true;
                        }

        if (!modified)
            break;
    }
    return table;
//    typedef function<int (State, State)> DFS_Function;
//
//    Table table(size_, vector<int>(size_, -1));
//    DFS_Function areEquivalent = [&] (State i, State j)
//    {
//        auto& curr = table[i][j];
//        if (curr != -1)
//            return curr;
//        curr = 1;
//        for (const Chr& a : { 0u, 1u })
//        {
//            State n_i = compute(i, a);
//            State n_j = compute(j, a);
//            if (!areEquivalent(n_i, n_j))
//                return curr = 0;
//        }
//        return curr;
//    };
//
//    for (State i = 0; i < size_; ++i)
//    {
//        table[i][i] = 1;
//        for (size_t j = 0; j < i; ++j)
//            if ((accepts(i) && !accepts(j)) || (!accepts(i) && accepts(j)))
//                table[i][j] = 0;
//    }
//
//    for (State i = 0; i < size_; ++i)
//        for (State j = 0; j < i; ++j)
//            table[j][i] = areEquivalent(i, j);
//
//    return table;
}
