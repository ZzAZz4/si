#include "DFA.h"
#include "../NFA/NFA.h"
#include <unordered_map>
#include <queue>

NFA DFA::revert_as_nfa () const
{
    vector<vector<State>> rev_function;
    for (State input = 0; input < function_.size(); ++input)
        for (const Chr& chr : { 0u, 1u })
            rev_function.emplace_back(
                vector{ function_[input][chr], chr, input });

    auto nfa = NFA(size_, f_states.elements, vector{ b_state }, rev_function);
    return nfa;
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
}

template<class T>
struct std::hash<pair<T, T>>
{
    size_t operator () (const pair<T, T>& p) const
    {
        std::hash<T> hasher = std::hash<T>();
        return hasher(p.first) ^ hasher(p.second);
    }
};

DFA::Table DFA::optimized_equivalence_table () const
{
    typedef pair<State, State> SPair;

    unordered_map<SPair, vector<SPair>> dependencies;
    vector<vector<int>> table(size_, vector<int>(size_, 0));
    queue<SPair> remaining;

    for (State p = 0; p < size_; ++p)
        for (State q = 0; q < size_; ++q)
            for (Chr c : { 0u, 1u })
            {
                SPair dependency = { function_[p][c], function_[q][c] };
                dependencies[dependency].emplace_back(make_pair(p, q));
            }

    for (State i = 0; i < size_; i++)
        for (State j = 0; j < i; j++)
            if (accepts(i) ^ accepts(j))
            {
                table[i][j] = table[j][i] = 1;
                remaining.emplace(i, j);
                remaining.emplace(j, i);
            }

    while (!remaining.empty())
    {
        SPair entry = remaining.front();
        for (auto[p, q] : dependencies[entry])
        {
            if (!table[p][q])
                remaining.emplace(p, q);
            table[p][q] = 1;
        }
        remaining.pop();
    }
    return table;

}

DFA DFA::huffman_moore_reduce () const
{
    DFA filtered = remove_unreachable();
    Table table = filtered.optimized_equivalence_table();

    vector<vector<State>> blocks;
    unordered_map<State, State> block_index;

    for (State i = 0; i < filtered.size_; ++i)
        for (State j = 0; j < i; ++j)
            if (!table[i][j])
            {
                auto i_block = block_index.find(i),
                    j_block = block_index.find(j);
                if (i_block == block_index.end() &&
                    j_block == block_index.end())
                {
                    block_index[i] = block_index[j] = blocks.size();
                    blocks.push_back(vector<State>{ i, j });
                }
                else if (i_block != block_index.end())
                {
                    block_index[j] = i_block->second;
                    blocks[i_block->second].push_back(j);
                }
                else if (j_block != block_index.end())
                {
                    block_index[i] = j_block->second;
                    blocks[j_block->second].push_back(i);
                }
            }
    for (State i = 0; i < filtered.size_; ++i)
        if (block_index.emplace(i, blocks.size()).second)
            blocks.emplace_back(vector<State>{ i });
    // Blocks are built, lets define the stuff
    size_t new_size = blocks.size();
    State init = block_index[filtered.b_state];
    vector<State> new_accept_states;
    Function new_transitions;

    for (auto block : blocks)
    {
        auto repr = block.front();
        State index = block_index[repr];
        if (filtered.accepts(repr))
            new_accept_states.emplace_back(index);
        for (Chr c : { 0u, 1u })
        {
            State dest = block_index[filtered.function_[repr][c]];
            new_transitions.push_back(vector<State>{ index, c, dest });
        }
    }
    return DFA(new_size, init, new_accept_states, new_transitions);
}

DFA DFA::remove_unreachable () const
{
    unordered_map<State, State> renamed_states;
    vector<State> f_reachable;
    vector<vector<State>> func_reachable;

    size_t i = 0;
    std::function<void (State)> fill = [&] (State cur)
    {
        if (renamed_states.emplace(cur, i).second)
        {
            State c_index = i++;
            renamed_states[cur] = c_index;
            if (accepts(cur))
                f_reachable.emplace_back(c_index);

            for (Chr c : { 0u, 1u })
            {
                auto reached = function_[cur][c];
                fill(reached);
                auto res = renamed_states[reached];
                func_reachable.emplace_back(vector{ c_index, c, res });
            }
        }
    };
    fill(b_state);
    DFA n_dfa(i, (State) 0, f_reachable, func_reachable);
    return n_dfa;
}


