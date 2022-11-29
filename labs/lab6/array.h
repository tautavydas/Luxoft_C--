#include <stddef.h> 
#include <initializer_list>
#include <map>

class Array {
public:
    Array();
    Array(int size);
    Array(std::initializer_list<double> list);
    Array(const Array& other);
    Array(Array&& other);

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);

    ~Array();
    double& operator[](std::size_t index);
    
    std::size_t size() const;

    static size_t& allocated_memory();

private:
    std::size_t size_;
    double* array_;
};