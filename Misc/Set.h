#ifndef SI_SET_H
#define SI_SET_H

#include "debug.h"

#include <deque>
#include <vector>
#include <functional>
#include <cmath>
#include <unordered_set>

using namespace std;

struct Set
{
    unordered_set<unsigned> contained;

    explicit Set (vector<unsigned> v = {})
        : contained(v.begin(), v.end())
    {}

    [[nodiscard]]
    auto begin () const
    { return contained.begin(); }

    [[nodiscard]]
    auto end () const
    { return contained.end(); }

    [[nodiscard]]
    int size () const
    { return contained.size(); }

    void insert (int element)
    { contained.emplace(element); }

    bool operator == (const Set& other) const
    {
        for (auto i : this->contained)
            if (!other.contains(i))
                return false;
        for (auto i : other.contained)
            if (!this->contains(i))
                return false;
        return true;
    }

    [[nodiscard]]
    bool contains (unsigned element) const
    { return contained.count(element); }
};

template<>
struct std::hash<Set>
{
    size_t operator () (const Set& cs) const
    {
        auto seed = 0x9e3779b9;
        auto h = hash<int>();
        for (const auto& i : cs)
            seed ^= h(i) ^ seed + (seed << 6) + (seed >> 2);
        return seed;
    }
};

#endif //SI_SET_H
