#include <queue>
#include "DFA.h"
#include "NFA.h"


DFA NFA::make_dfa () const
{
    unordered_map<Set, State> state;
    queue<Set> wait_queue;

    State i = 0;
    state.emplace(b_states, i);
    wait_queue.emplace(b_states);

    vector<State> dfa_f_states{};
    vector<vector<State>> function;
    while (!wait_queue.empty())
    {
        const auto current = wait_queue.front();
        const auto& cur_state = state[current];
        wait_queue.pop();
        if (accepts(current))
            dfa_f_states.emplace_back(cur_state);

        for (const Chr a : { 0u, 1u })
        {
            const auto comp = compute(current, a);
            const auto [it, inserted] = state.emplace(comp, i + 1);
            if (inserted)
            {
                wait_queue.emplace(comp);
                ++i;
            }
            const auto& [_, dest_state] = *it;
            function.emplace_back(vector{ cur_state, a, dest_state });
        }
    }
    return DFA(i + 1, 0, dfa_f_states, function);
}

Set NFA::compute (const Set& states, NFA::Chr a) const
{
    if (states.elements.empty())
        return states;

    unordered_set<State> res;
    for (const auto& p : states)
        for (const auto& i : function_[p][a])
            res.emplace(i);

    return Set(vector<State>{ res.begin(), res.end()});
}

bool NFA::accepts (const Set& states) const
{
    for (auto state : states)
        if (f_states.contains(state))
            return true;
    return false;
}

void NFA::print ()
{
    std::cout << size_ << " { ";
    for (auto s : b_states)
        std::cout << s << ' ';
    cout << "} " << f_states.size();
    for (auto i : f_states)
        cout << ' ' << i;
    endl(cout);

    for (unsigned p = 0; p < size_; ++p)
    {
        for (auto a : { 0, 1 })
        {
            cout << p << ' ' << a << " { ";
            for (auto i : function_[p][a])
                cout << i << ' ';
            cout << "}\n";
        }
    }
}

NFA::NFA (
    size_t n, vector<State> init, vector<State> f_st, vector<vector<State>> fun)
    : size_(n), b_states(move(init)), f_states(move(f_st))
{
    sort(
        fun.begin(), fun.end(), [] (const auto& a, const auto& b)
        { return a[2] < b[2]; });
    function_.resize(size_, vector<Set>(2));
    for (const auto& trans : fun)
        function_[trans[0]][trans[1]].insert(trans[2]);
}

