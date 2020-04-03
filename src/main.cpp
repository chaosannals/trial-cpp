#include <iostream>
#include <set>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include "timing.h"

std::set<int> rand_set(int length, int min, int max)
{
    std::set<int> result;
    int limit = max - min;
    std::srand(std::time(nullptr));
    while (true)
    {
        int v = std::rand() % limit + min;
        if (result.size() >= length)
        {
            break;
        }
        if (result.find(v) == result.end())
        {
            result.insert(v);
        }
    }
    return result;
}

std::set<int> intersect(const std::set<int> &a, const std::set<int> &b)
{
    std::set<int> result;
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        if (b.find(*i) != b.end())
        {
            result.insert(*i);
        }
    }
    return result;
}

std::unordered_set<int> rand_uset(int length, int min, int max)
{
    std::unordered_set<int> result;
    int limit = max - min;
    std::srand(std::time(nullptr));
    while (true)
    {
        int v = std::rand() % limit + min;
        if (result.size() >= length)
        {
            break;
        }
        if (result.find(v) == result.end())
        {
            result.insert(v);
        }
    }
    return result;
}

std::unordered_set<int> uintersect(const std::unordered_set<int> &a, const std::unordered_set<int> &b)
{
    std::unordered_set<int> result;
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        if (b.find(*i) != b.end())
        {
            result.insert(*i);
        }
    }
    return result;
}

int main()
{
    std::set<int> sa = rand_set(1000000, 1, 10000000);
    std::set<int> sb = rand_set(1000000, 1, 10000000);
    std::unordered_set<int> usa = rand_uset(1000000, 1, 10000000);
    std::unordered_set<int> usb = rand_uset(1000000, 1, 10000000);
    std::set<int> sab = timing<std::set<int>>([&sa, &sb]() {
        return intersect(sa, sb);
    });
    std::cout << sab.size() << std::endl;
    std::unordered_set<int> usab = timing<std::unordered_set<int>>([&usa, &usb] {
        return uintersect(usa, usb);
    });
    std::cout << usab.size() << std::endl;
    return 0;
}