#include "FiniteAutomata/include.h"
#include <ctime>
#include <chrono>

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration{};

    Timer ()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer ()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        double ms = duration.count() * 1000.0f;
        std::cout << "Timer took: " << ms << "ms\n\n";
    }
};


int main ()
{
    srand(time(nullptr));
    typedef unsigned State;

    for (int trial = 0; trial < 5; ++trial, std::cout << "\n---------------\n")
        for (size_t n = 250; n <= 1250; n += 250)
        {
            std::cout << "Size: " << n << '\n';

            Set s;
            s.reserve(n);
            size_t temp1, temp2, temp3;

            unsigned f_size = rand() % (n) + 1;
            vector<unsigned> f_states(f_size);

            auto qfs = f_size;
            while (qfs--)
            {
                temp1 = rand() % (n);
                if (!s.contains(temp1))
                {
                    s.insert(temp1);
                    f_states.push_back(temp1);
                }
                else
                { qfs++; }
            }

            vector<vector<unsigned>> transitions(
                2 * n, vector<unsigned>(3, 0));
            for (unsigned i = 0; i < n; ++i)
            {
                temp2 = rand() % n;
                temp3 = rand() % n;
                transitions.push_back(vector<unsigned>{ i, 0, temp2 });
                transitions.push_back(vector<unsigned>{ i, 1, temp3 });
            }

            DFA dfa(n, (rand() % n), f_states, move(transitions));

            {
                Timer timer;
                auto table = dfa.hopcroft_reduce();
            }
//
//        auto table = dfa.optimized_equivalence_table();
//        for (int i = 0; i < table.size(); ++i, endl(std::cout))
//            for (int j : table[i])
//                std::cout << j << ' ';
//        endl(std::cout);
//
//        auto simp = dfa.huffman_moore_reduce();
//        simp.print();
//        endl(std::cout);
//
//        auto simp2 = dfa.hopcroft_reduce();
//        simp2.print();
        }
    return 0;

//    unsigned n, init, f_size;
//    cin >> n >> init >> f_size;
//
//    vector<unsigned> f_states(f_size);
//    for (auto& state : f_states)
//        cin >> state;
//
//    vector<vector<unsigned>> transitions(2 * n, vector<unsigned>(3, 0));
//    for (auto& transition : transitions)
//        cin >> transition[0] >> transition[1] >> transition[2];


}
