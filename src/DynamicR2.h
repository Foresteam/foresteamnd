#include <cstdlib>

/// @brief Dynamic array [][]. Better create with 'new'/'malloc'
template <typename T>
class DynamicR2 {
private:
	T* _self;
	T** self;
	size_t s1, s2;
public:
    /// @param s1 Size of low level
    /// @param s2 Size of high level
	DynamicR2(size_t s1, size_t s2);
	DynamicR2(const DynamicR2& other);

	DynamicR2<T> operator=(const DynamicR2& other);

	~DynamicR2();

	T* At(size_t index);
	T* operator[](size_t index);
};