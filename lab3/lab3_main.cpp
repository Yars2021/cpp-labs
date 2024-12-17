#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#include "superstring.hpp"

using namespace std;

SuperString avg_list1;

bool comp_6(SuperString &a, SuperString &b) {
    return (a > avg_list1) && (b < avg_list1);
}

vector<SuperString> intersection(vector<SuperString> v1, std::vector<SuperString> v2) {
    vector<SuperString> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(),v1.end(), v2.begin(),v2.end(), back_inserter(v3));

    return v3;
}

int main() {
    srand(time(nullptr));

    // 1. Create v1
    vector<SuperString> v1;
    for (int i = 0; i < rand() % 500 + 500; i++, v1.push_back(SuperString(5, 10)));

    // 2. Create v2 as a part of v1 (last 200)
    vector<SuperString> v2(v1.end() - 200, v1.end());

    // 3. Create list1 as a 20-50 sorted slice of v1
    sort(v1.begin() + 20, v1.begin() + 50 + 1);
    list<SuperString> list1(v1.begin() + 20, v1.begin() + 50 + 1);

    // 4. Create list2 as a rand(20, 50) slice of smallest items of v2
    sort(v2.begin(), v2.end());
    list<SuperString> list2(v2.begin(), v2.begin() + rand() % 30 + 20);

    // 5. Remove list1 from v1 and list2 from v2
    v1.erase(v1.end() - 200, v1.end());
    v2.erase(v2.begin(), v2.begin() + list2.size() + 1);

    // 6. Find avg and sort list1
    unsigned int avg_len = 0;
    for (auto it = list1.begin(); it != list1.end(); it++) avg_len += it->length();
    avg_len /= list1.size();

    for (auto it = list1.begin(); it != list1.end(); it++) {
        if (it->length() == avg_len) {
            avg_list1 = *it;
            break;
        }
    }

    list1.sort(comp_6);

    // 7. Remove all length % 2 == 1 from list2
    list1.remove_if([](auto val) {
        return ((val.length() % 2) == 1);
    });

    // 8. v3 = v1 intersect v2
    vector<SuperString> v3 = intersection(v1, v2);

    // 9. Make list1 and list2 sizes equal. Form list3 from pairs of list1 and list2 items
    if (list1.size() > list2.size()) {
        list<SuperString>::iterator range_end = list1.begin();
        advance(range_end, list1.size() - list2.size());
        list1.erase(list1.begin(), range_end);
    } else {
        list<SuperString>::iterator range_end = list2.begin();
        advance(range_end, list2.size() - list1.size());
        list2.erase(list2.begin(), range_end);
    }

    list<pair<SuperString, SuperString>> list3;

    for (auto l1 = list1.begin(), l2 = list2.begin(); l1 != list1.end() && l2 != list2.end(); advance(l1, 1), advance(l2, 1)) {
        list3.push_back({*l1, *l2});
    }

    // 10. Task 9 but for vectors v1 and v2 and without cutting v1 and v2
    vector<pair<SuperString, SuperString>> v4;

    for (int i = 0; i < min(v1.size(), v2.size()); i++) v4.push_back({v1[i], v2[i]});

    return 0;
}