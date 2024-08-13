#pragma once
#include <cstdint>
#include <cstring>

namespace Mou
{

template<class T>
class SmartArr
{
public:
    SmartArr() = default;
    SmartArr(int32_t length)
        : length(length)
    {
        array = new T[length];
    }
    ~SmartArr() { delete[] array; }
    void Reserve(int32_t length)
    {
        if (array == nullptr) {
            array = new T[length];
        }
        else {
            delete[] array;
            array = new T[length];
        }
        this->length = length;
        nextPos = 0;
    }
    T& operator[](int32_t index)
    {
        return array[index];
    }
    void PushBack(T element)
    {
        if (nextPos < length)
        {
            array[nextPos] = element;
            nextPos++;
        }
        else
        {
            // realloc
            assert(nextPos < length);
        }
    }
    void PopBack()
    {
        nextPos--;
        std::memset(&array[nextPos], 0, sizeof(T));
    }
    void SwapBackAndPop(int32_t index)
    {
        nextPos--;
        array[index] = array[nextPos];
        std::memset(&array[nextPos], 0, sizeof(T));
    }
    const int32_t Length()
    {
        return nextPos;
    }
private:
    int32_t length;
    int32_t nextPos = 0;
    T* array = nullptr;
};

}