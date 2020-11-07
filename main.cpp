#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>

#ifndef NDEBUG
#define EXPECTS(condition, msg) \
if (!(condition)) \
{ \
    fprintf(stderr, "At line %d of %s\n", __LINE__, __FILE__);\
    fprintf(stderr, "On call to %s\n", __PRETTY_FUNCTION__);\
    throw std::logic_error(msg " (failed " #condition ")");\
}
#else
#define EXPECTS(...)
#endif
using namespace std;

template<class T>
using Set = unordered_set<T>;

template<class T, class U>
using Map = unordered_map<T, U>;

struct Input
{
    int p{};
    int a{};

    bool operator == (const Input& other) const
    { return p == other.p && a == other.a; }
};

template<class T>
struct std::hash<Set<T>>
{
    std::size_t operator () (std::unordered_set<T> const& set) const
    {
        std::size_t seed = set.size();
        for (auto& i : set)
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

template<>
struct std::hash<Input>
{
    size_t operator () (const Input& x) const
    {
        return hash<int>()(x.a) ^ hash<int>()(x.p);
    }
};

struct DFA;
struct NFA;

struct NFA
{
    typedef int State;
    typedef int Token;

    size_t num_states{};
    Set<State> initial_states{};
    Set<State> accept_states{};
    Map<Input, Set<State>> transitions{};
    Set<Token> alphabet = { 0, 1 };

    auto compute_step (const Set<State>& states, Token input) const
    {
        EXPECTS(alphabet.count(input), "input is not present in alphabet");
        unordered_set<int> computation;
        for (const auto& state : states)
        {
            EXPECTS(state < num_states, "state doesn't exist in NFA");
            auto iter = transitions.find({ state, input });
            if (iter != transitions.end())
                for (const auto& i : iter->second)
                    computation.emplace(i);
        }
        return computation;
    };

    bool is_accept_state (const Set<State>& states) const
    {
        for (const auto& accept_state : accept_states)
            if (states.count(accept_state))
                return true;
        return false;
    };

    DFA make_dfa () const;
};

struct DFA
{
    typedef int State;
    typedef int Token;

    size_t num_states{};
    State initial_state{};
    Set<State> accept_states{};
    Map<Input, State> transitions{};
    Set<Token> alphabet = { 0, 1 };

    State compute_step (State state, Token input) const
    {
        auto i = alphabet.find(input);
        EXPECTS (alphabet.find(input) != alphabet.end(),
                 "input is not present in alphabet");
        EXPECTS (state < num_states, "state doesn't exist in DFA");
        return transitions.at(Input{ state, input });
    }

    bool is_accept_state (State state) const
    {
        return accept_states.find(state) == accept_states.end();
    }

    NFA make_reverse () const;

    vector<vector<int>> equivalence_table () const
    {
        enum EQ_CLASS
        {
            DIST = 0,
            EQ = 1,
            UNDEF = -1
        };
        vector<vector<int>> table(
            num_states, vector<int>(num_states, UNDEF));

        function<int (State, State)> fill_table = [&] (State i, State j)
        {
            if (table[i][j] != UNDEF)
                return table[i][j];
            table[i][j] = table[j][i] = EQ;
            for (const auto& a : alphabet)
            {
                auto n_i = compute_step(i, a), n_j = compute_step(j, a);
                if (fill_table(n_i, n_j) == DIST)
                    return table[i][j] = table[j][i] = DIST;
            }
            return table[i][j] = table[j][i] = EQ;
        };

        for (int i = 0; i < num_states; ++i)
        {
            table[i][i] = EQ;
            for (int j = 0; j < i; ++j)
                if (accept_states.count(i) ^ accept_states.count(j))
                    table[i][j] = table[j][i] = DIST;
        }
        for (int i = 0; i < num_states; ++i)
            for (int j = 0; j < i; ++j)
                fill_table(i, j);

        return table;
    }
};

DFA NFA::make_dfa () const
{
    unordered_map<unordered_set<int>, int> state_num;
    queue<unordered_set<int>> wait_queue;

    int i = 0;
    state_num.emplace(initial_states, i);
    wait_queue.emplace(initial_states);

    DFA dfa{
        0,
        0,
        {},
        {},
        alphabet };

    while (!wait_queue.empty())
    {
        auto current = wait_queue.front();
        wait_queue.pop();
        if (is_accept_state(current))
            dfa.accept_states.emplace(state_num[current]);

        for (const auto& a : alphabet)
        {
            auto comp = compute_step(current, a);
            if (state_num.find(comp) == end(state_num))
            {
                state_num[comp] = ++i;
                wait_queue.emplace(comp);
            }
            auto input = Input{ state_num[current], a };
            dfa.transitions.emplace(input, state_num[comp]);
        }
    }
    dfa.num_states = ++i;
    return dfa;
}

NFA DFA::make_reverse () const
{
    NFA nfa{
        num_states,
        { accept_states },
        { initial_state },
        {},
        alphabet };

    nfa.transitions.reserve(transitions.size());
    for (auto&[domain, out_state] : transitions)
        nfa.transitions[Input{ out_state, domain.a }].emplace(domain.p);

    return nfa;
}

DFA brzozowski_reduce (const DFA& dfa)
{
    auto reverse_dfa = dfa.make_reverse().make_dfa();
    return reverse_dfa.make_reverse().make_dfa();
}

int main ()
{
    DFA dfa;
    int nf;
    cin >> dfa.num_states >> dfa.initial_state >> nf;

    dfa.accept_states.reserve(nf);
    for (int i = 0, state; i < nf; ++i)
    {
        cin >> state;
        dfa.accept_states.emplace(state);
    }

    dfa.transitions.reserve(2 * dfa.num_states);

    for (unsigned i = 0; i < 2 * dfa.num_states; ++i)
    {
        Input in{};
        int out;
        cin >> in.p >> in.a >> out;
        dfa.transitions.emplace(in, out);
    }

    auto reduced = brzozowski_reduce(dfa);
    std::cout << reduced.num_states << ' ' << reduced.initial_state << ' '
              << reduced.accept_states.size();
    for (auto i : reduced.accept_states)
        std::cout << ' ' << i;
    endl(std::cout);

    for (const auto&[input, output] : reduced.transitions)
        std::cout << input.p << ' ' << input.a << ' ' << output << '\n';

    endl(std::cout);
    auto table = dfa.equivalence_table();
    for (const auto& i : table)
    {
        for (auto j : i)
            std::cout << j << ' ';
        std::cout << std::endl;
    }
    return 0;
}
