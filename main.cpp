#include "DFA.h"
#include "NFA.h"

auto brzozowski_reduce(const DFA& dfa)
{
    return dfa.make_reverse().make_dfa().make_reverse().make_dfa();
}

int main ()
{
    DFA dfa(
        3, 0,
        { 0, 1 },
        {{ 0, 0, 1 },
         { 0, 1, 2 },
         { 1, 0, 1 },
         { 1, 1, 2 },
         { 2, 0, 0 },
         { 2, 1, 2 }}
    );
    dfa.print();
    endl(cout);

    auto simp = brzozowski_reduce(dfa);
    simp.print();
    endl(cout);

    auto table = dfa.equivalence_table();
    for (const auto& row : table)
    {
        for (const auto& elem : row)
            std::cout << elem << ' ';
        endl(std::cout);
    }
    return 0;
}
