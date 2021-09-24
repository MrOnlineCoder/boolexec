#include <Runtime.hpp>

#include <iostream>
#include <algorithm>

RuntimeContext::RuntimeContext() {
    K = 2;
}

void RuntimeContext::registerVariable(std::string name) {
    m_variables[name] = 0;
}

value_t RuntimeContext::resolve(const std::string& name) {
    return m_variables[name];
}

void RuntimeContext::updateVariable(const std::string name, value_t val) {
    m_variables[name] = val;
}

std::vector<std::string> RuntimeContext::getVariablesNames() {
    std::vector<std::string> names;
    for (auto const& key : m_variables)
        names.push_back(key.first);

    std::sort(names.begin(), names.end());
    
    return names;
}   

unsigned int RuntimeContext::getK() {
    return K;
}

void RuntimeContext::setK(int newK) {
    K = newK;
}

void RuntimeContext::clear() {
    m_variables.clear();
}