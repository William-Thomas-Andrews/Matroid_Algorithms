// #include <iostream>
#include <algorithm>
// #include "UnionFind.hpp"
#include "Graph.hpp"
#include "Compare.hpp"


// Corresponds to the Edge type for Graphic Matroids

Edge::Edge() {}
Edge::Edge(Vertex v1, Vertex v2, Weight w) : v(v1 > v2 ? v1 : v2), u(v1 > v2 ? v2 : v1), weight(w) {}

std::string Edge::get_string() {
    std::string str = "(" + std::to_string(v) + " - " + std::to_string(u) + ")" + "(" + std::to_string(weight) + ")";
    return str;
}

const std::string Edge::get_string() const {
    std::string str = "(" + std::to_string(v) + " - " + std::to_string(u) + ")" + "(" + std::to_string(weight) + ")";
    return str;
}

Vertex Edge::get_left() { return v; }
Vertex Edge::get_right() { return u; }
Weight Edge::get_weight() { return weight; }

void Edge::set_weight(Weight w) { weight = w; }

// Comparison operator <
bool Edge::operator<(Edge& e2) {
    return (weight < e2.get_weight());
}

// Comparison operator >
bool Edge::operator>(Edge& e2) {
    return (weight > e2.get_weight());
}

// Comparison operator ==
bool Edge::operator==(Edge& e2) {
    if (v == e2.get_left() and u == e2.get_right() and weight == e2.get_weight()) return true;
    return false;
}

// Comparison operator !=
bool Edge::operator!=(Edge& e2) {
    return (weight != e2.get_weight());
}


std::ostream& operator<<(std::ostream& os, Edge& e) {
    os << e.get_string();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    os << e.get_string();
    return os;
}

// The input set for a Graphic Matroid
Graph::Graph() {}
Graph::Graph(int size) : union_set(UnionFind(size)) {}
Graph::Graph(std::vector<std::tuple<Vertex, Vertex, Weight>> input_data) : union_set(UnionFind(input_data.size())) {
    for (auto x : input_data) {
        Edge e = Edge(std::get<0>(x), std::get<1>(x), std::get<2>(x));
        this->add_element(e);
        union_set.union_operation(e.get_left(), e.get_right());
    }
}
Graph::Graph(std::vector<Edge> input_data) : union_set(UnionFind(input_data.size())) {
    for (Edge e : input_data) {
        this->add_element(e);
        union_set.union_operation(e.get_left(), e.get_right());
    }
}

// Matroid functions begin --------------------------------------------------------------------------------------------------
void Graph::min_sort() {
    std::sort(edges.begin(), edges.end(), MinCompare<Edge>{});
}

void Graph::max_sort() {
    std::sort(edges.begin(), edges.end(), MaxCompare<Edge>{});
}

bool Graph::not_empty() {
    return (!edges.empty());
}

Edge Graph::top() {
    if (edges.empty()) { throw std::runtime_error("Cannot get first element of an empty graph"); }
    else {
        return edges[edges.size()-1];
    }
}

// If adding Edge e does not create a cycle then it will return true
bool Graph::is_independent(Edge& e) {
    // If both sides of the edge are in the same partition, 
    // then it creates a cycle and we return false because adding 'e' is not valid if we want to keep the graph acyclic.
    // Otherwise return true because both parititions are disjoint
    return (!(union_set.find_operation(e.get_left()) == union_set.find_operation(e.get_right())));
}   

void Graph::add_element(Edge e) {
    edges.push_back(e);
    union_set.union_operation(e.get_left(), e.get_right());
}

void Graph::pop() {
    edges.pop_back();
}
// Matroid functions end ---------------------------------------------------------------------------------------------------------


std::vector<Edge>& Graph::get_data() {
    return edges;
}

std::string Graph::get_string() {
    std::string str = "";
    for (auto edge : edges) {
        str += edge.get_string() + " ";
    }
    str += "\n";
    return str;
}


std::ostream& operator<<(std::ostream& os, Graph& G) {
    os << G.get_string();
    return os;
}