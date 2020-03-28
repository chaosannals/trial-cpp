#include <iostream>
#include <set>
#include <ctime>
#include <cstdlib>

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

int main()
{
    std::set<int> sa = rand_set(1000000, 1, 10000000);
    std::set<int> sb = rand_set(1000000, 1, 10000000);
    std::set<int> sab = intersect(sa, sb);
    std::cout << sab.size() << std::endl;
    std::cout << RAND_MAX << std::endl;
    return 0;
}