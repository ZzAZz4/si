#include "DFA.h"
#include "NFA.h"

vector<vector<int>> DFA::equivalence_table () const
{
    enum EQ_CLASS
    {
        DIST = 0,
        EQ = 1,
        UNDEF = -1
    };
    vector<vector<int>> table(
        size_, vector<int>(size_, UNDEF));

    function<int (State, State)> fill_table = [&] (State i, State j)
    {
        if (table[i][j] != UNDEF)
            return table[i][j];
        table[i][j] = table[j][i] = EQ;
        for (const auto& a : { 0u, 1u })
        {
            auto n_i = compute(i, a), n_j = compute(j, a);
            if (fill_table(n_i, n_j) == DIST)
                return table[i][j] = table[j][i] = DIST;
        }
        return table[i][j] = table[j][i] = EQ;
    };

    for (int i = 0; i < size_; ++i)
    {
        table[i][i] = EQ;
        for (int j = 0; j < i; ++j)
            if (f_states.contains(i) ^ f_states.contains(j))
                table[i][j] = table[j][i] = DIST;
    }
    for (int i = 0; i < size_; ++i)
        for (int j = 0; j < i; ++j)
            fill_table(i, j);

    return table;
}
NFA DFA::make_reverse () const
{
    vector<vector<State>> rev_function;
    for (State p = 0; p < function_.size(); ++p)
        for (const Chr& a : { 0u, 1u })
            rev_function.emplace_back(vector{ function_[p][a], a, p });

    return NFA (
        size_, f_states.elements, vector{ b_state }, rev_function);
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

bool DFA::accepts (int state) const
{ return f_states.contains(state); }

DFA::DFA (
    size_t n, DFA::State begin, vector<State> f_states,
    const DFA::Function& fun)
    : size_(n),
      b_state(begin),
      f_states(move(f_states))
{
    function_.resize(size_, vector<State>(2, 0));
    for (const auto& trans : fun)
        function_[trans[0]][trans[1]] = trans[2];
}
