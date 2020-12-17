#include "FiniteAutomata/include.h"


int main ()
{
    typedef unsigned State;

    unsigned n, init, f_size;
    cin >> n >> init >> f_size;

    vector<unsigned> f_states(f_size);
    for (auto& state : f_states)
        cin >> state;

    vector<vector<unsigned>> transitions(2 * n, vector<unsigned>(3, 0));
    for (auto& transition : transitions)
        cin >> transition[0] >> transition[1] >> transition[2];

    DFA dfa(n, init, f_states, move(transitions));

//    // Pregunta 1
//
//    auto simp_dfa = dfa.brzozowski_reduce();
//    simp_dfa.print();
//    endl(cout);
//
//    // Pregunta 2
//    auto table = dfa.equivalence_table();
//    auto table2 = dfa.optimized_equivalence_table();
//    EXPECTSVAL(table.size(), table2.size());
//
//    for (int i = 0; i < table.size(); ++i)
//    {
//        EXPECTSVAL(table[i].size(), table2[i].size());
//        for (int j = 0; j < table[i].size(); ++j)
//        {
//            cout << table[i][j] << ' ';
//            EXPECTSVAL(table[i][j], table2[i][j]);
//        }
//        endl(cout);
//    }
    auto table = dfa.optimized_equivalence_table();
    for (int i = 0; i < table.size(); ++i, endl(std::cout))
        for (int j : table[i])
            std::cout << j << ' ';
    endl(std::cout);

    auto simp = dfa.huffman_moore_reduce();
    simp.print();
    endl(std::cout);

    auto simp2 = dfa.hopcroft_reduce();
    simp2.print();

    return 0;
}
