#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <string>

class Tuple {
    public:
        Tuple(std::size_t size, std::size_t base);

        int getDigitAt(std::size_t index);

        void setDigitAt(std::size_t index, int value);

        void increment();

        ~Tuple();

        bool isFinal();

        int* getDataPtr(); 

        std::size_t getSize();

        void dump();
    private:
        std::size_t m_size;
        std::size_t m_base;

        int* m_data;
};

#endif