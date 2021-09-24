#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <string>

class Tuple {
    public:
        Tuple(std::size_t size, std::size_t base);

        int getDigitAt(std::size_t index);

        void increment();

        ~Tuple();

        bool isFinal();

        void dump();
    private:
        std::size_t m_size;
        std::size_t m_base;

        int* m_data;
};

#endif