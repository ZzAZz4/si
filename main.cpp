#include "FiniteAutomata/include.h"

int main ()
{
    typedef unsigned State;

    size_t n, init, f_size;
    cin >> n >> init >> f_size;

    vector<size_t> f_states(f_size);
    for (auto& state : f_states)
        cin >> state;

    vector<vector<unsigned>> transitions(2 * n, vector<unsigned>(3, 0));
    for (auto& transition : transitions)
        cin >> transition[0] >> transition[1] >> transition[2];

    DFA dfa(n, init, f_states, move(transitions));

    auto simp_dfa = dfa.brzozowski_reduce();
    simp_dfa.print();
    endl(cout);

    auto table = dfa.equivalence_table();
    for (const auto& row : table)
    {
        for (const auto& elem : row)
            cout << elem << ' ';
        endl(cout);
    }
    return 0;
}
