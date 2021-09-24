#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <string>
#include <unordered_map>
#include <vector>

typedef int value_t;


class RuntimeContext {
    public:
        RuntimeContext();

        void registerVariable(std::string name);

        value_t resolve(const std::string& name);

        void updateVariable(const std::string name, value_t val);

        std::vector<std::string> getVariablesNames(); 

        unsigned int getK();

        void clear();

        void setK(int newK);
    private:
        std::unordered_map<std::string, value_t> m_variables;

        int K;
};

#endif // RUNTIME_HPP
