// #include <vector>
// #include <tuple>
#include <algorithm>

#include "PartitionMatroid.hpp"


PartitionPair::PartitionPair() {}
PartitionPair::PartitionPair(int element, int partition) : pair(std::make_tuple(element, partition)) {}
std::tuple<int, int> pair;
bool PartitionPair::operator<(PartitionPair& pair_2) { return (get_element() < pair_2.get_element()); }
bool PartitionPair::operator>(PartitionPair& pair_2) { return (get_element() > pair_2.get_element()); }
bool PartitionPair::operator==(PartitionPair& pair_2) { return (get_element() == pair_2.get_element()); }
int PartitionPair::get_element() { return std::get<0>(pair); }
int PartitionPair::get_partition() { return std::get<1>(pair); }




PartitionMatroid::PartitionMatroid() {}
PartitionMatroid::PartitionMatroid(std::vector<PartitionPair>& input) : set(input) {}

// Matroid functions begin --------------------------------------------------------------------------------------------------
void PartitionMatroid::min_sort() {
    std::sort(set.begin(), set.end(), MinCompare<PartitionPair>{});
}

void PartitionMatroid::max_sort() {
    std::sort(set.begin(), set.end(), MaxCompare<PartitionPair>{});
}

bool PartitionMatroid::not_empty() {
    return (!set.empty());
}

PartitionPair PartitionMatroid::top() {
    if (set.empty()) { throw std::runtime_error("Cannot get first element of an empty graph"); }
    else {
        return set[set.size()-1];
    }
}

// If element e does not share the same partition with another element already in the set then it will return true
bool PartitionMatroid::is_independent(PartitionPair& e) {
    for (int i = 0; i < set.size(); i++) {
        if (e.get_partition() == set[i].get_partition()) { // if we are about to add an element with the same partition as a previous element
            return false;
        }
    }
    return true;

}   

void PartitionMatroid::add_element(PartitionPair e) {
    set.push_back(e);
}

void PartitionMatroid::pop() {
    set.pop_back();
}
// Matroid functions end ---------------------------------------------------------------------------------------------------------


std::string PartitionMatroid::get_string() {
    std::string str = "{";
    for (int i = 0; i < set.size(); i++) {
        str += std::to_string(set[i].get_element());
        if (i == set.size()-1) {
            continue;
        }
        str += ", ";
    }
    str += "}";
    return str;
}

std::vector<PartitionPair> PartitionMatroid::get_data() {
    return set;
}



std::ostream& operator<<(std::ostream& os, PartitionMatroid& p) {
    os << p.get_string();
    return os;
}

// Utility to create a PartitionPair
PartitionPair make_pair(int elem, int part) {
    return PartitionPair(elem, part);
}