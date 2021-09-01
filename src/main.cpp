#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


using Ip = std::array<int, 4>;

using IpPool = std::vector<Ip>;
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template<class Compare, typename T>
bool pair_comparer(Compare comp, const T& a, const T& b) {
    return comp(a, b);
}

template<class Compare, typename T, typename... Args>
bool pair_comparer(Compare comp, const T& a, const T& b, const Args&... args) {
    return a == b ? pair_comparer(comp, args...) : comp(a, b);
}

bool IpCompare (const Ip& ip1, const Ip& ip2)
{
    return pair_comparer([](const auto& a, const auto& b) { return a > b; }, ip1.at(0), ip2.at(0), ip1.at(1), ip2.at(1), ip1.at(2), ip2.at(2), ip1.at(3), ip2.at(3));
}

template<typename Separator, typename T>
std::ostream& join_print(std::ostream& s, const Separator& separator, const T& t)
{
    s << t;
    return s;
}

template<typename Separator, typename T, typename... Args>
std::ostream& join_print(std::ostream& s, const Separator& separator, const T& t, const Args&... args)
{
    s << t << separator;
    join_print(s, separator, args...);
    return s;
}

void print_ip(const Ip& ip)
{
    join_print(std::cout, ".", ip.at(0), ip.at(1), ip.at(2), ip.at(3));
    std::cout << std::endl;
}

template<class T>
class filtered
{
    using Filter = std::function<bool(typename T::value_type)>;
public:
    filtered(const T& t, const Filter& f) :container(t), filter(f) {}

    class const_iterator : public T::const_iterator
    {
    public:
        const_iterator& operator++() noexcept {
            T::const_iterator::operator++();
            T::const_iterator::operator=(std::find_if(static_cast<typename T::const_iterator&>(*this), end, filter));

            return *this;
        }
    private:
        const_iterator(const typename T::const_iterator& it, const typename T::const_iterator& e, const Filter& f) :
            T::const_iterator(it), filter(f), end(e)
        {
            T::const_iterator::operator=(std::find_if(static_cast<typename T::const_iterator&>(*this), end, filter));
        }
        const Filter& filter;
        const typename T::const_iterator end;
    
    friend filtered;
    };

    const_iterator begin()
    {
        return const_iterator(container.cbegin(), container.cend(), filter);
    };
    const_iterator end()
    {
        return const_iterator(container.cend(), container.cend(), [](auto) {return true; });
    };

private:
    const T& container;
    const Filter filter;
};

int main(int argc, char const *argv[])
{
    try
    {
        IpPool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            auto ip = split(v.at(0), '.');
            ip_pool.push_back({ std::stoi(ip[0]), std::stoi(ip[1]), std::stoi(ip[2]), std::stoi(ip[3]) });
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), IpCompare);

        for (const auto& ip: ip_pool)
            print_ip(ip);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        for (const auto& ip : filtered<IpPool>(ip_pool, [](auto v) {return v.at(0) == 1; }))
            print_ip(ip);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        for (const auto& ip : filtered<IpPool>(ip_pool, [](auto v) {return v.at(0) == 46 && v.at(1) == 70; }))
            print_ip(ip);


        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        for (const auto& ip : filtered<IpPool> (ip_pool, [](auto v) {return std::find(v.begin(), v.end(), 46) != v.end(); }))
            print_ip(ip);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
