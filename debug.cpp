#include <iostream>
#include <memory>
#include<vector>
#include "vector.hpp"

#include "ft_containers-unit-test/sources/system/lib.hpp"


template <typename T>
std::vector<int> erase_test_1(std::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    v.push_back(*(vector.begin() + 82 * _ratio));
	std::cout << v[1] << std::endl;
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> erase_test_1(_vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    v.push_back(*(vector.begin() + 82 * _ratio));
	std::cout << v[1] << std::endl;
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

int main(void)
{
	std::cout << (erase_test_1(ft::vector<int>()) == erase_test_1(std::vector<int>()));
}