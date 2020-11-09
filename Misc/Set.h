#ifndef SI_SET_H
#define SI_SET_H

#include "debug.h"

#include <deque>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

struct Set
{
    vector<bool> contained;
    vector<unsigned> elements;

    explicit Set (vector<unsigned> v = {})
    {
        if (!v.empty())
        {
            if (!is_sorted(std::begin(v), std::end(v)))
                sort(std::begin(v), std::end(v));
            elements = move(v);
            unsigned max = elements.back();
            unsigned size = 1;
            while (size < max + 1)
                size *= 2;
            contained.resize(size, false);
            for (const auto& elem : elements)
                contained[elem] = true;
        }
    }

    [[nodiscard]]
    auto begin () const
    { return elements.begin(); }

    [[nodiscard]]
    auto end () const
    { return elements.end(); }

    [[nodiscard]]
    int size () const
    { return elements.size(); }

    [[nodiscard]]
    int capacity () const
    { return contained.size(); }

    void reserve (int n)
    {
        contained.resize(n);
        elements.reserve(n);
    }

    void insert (int element)
    {
        if (element >= contained.size())
        {
            unsigned size = 1;
            while (size < element + 1)
                size *= 2;
            contained.resize(size, false);
        }
        if (!contained[element])
        {
            if (elements.empty() || elements.back() < element)
                elements.emplace_back(element);
            else
                elements.insert(
                    upper_bound(elements.begin(), elements.end(), element),
                    element);
            contained[element] = true;
        }
    }

    bool operator == (const Set& other) const
    {
        return this->elements == other.elements;
    }

    [[nodiscard]]
    bool contains (unsigned element) const
    {
        return element < contained.size() && contained[element];
    }

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
