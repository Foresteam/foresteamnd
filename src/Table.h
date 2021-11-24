#include <cstdlib>

/// @brief Dynamic array [][]. Better create with 'new'/'malloc'
template <typename T>
class Table {
private:
	T* _self;
	T** self;
	/// @brief Size of low level
	size_t s1;
	/// @brief Size of high level
	size_t s2;
public:
    /// @param s1 Size of low level
    /// @param s2 Size of high level
	Table(size_t s1, size_t s2);
	Table(const Table& other);

	Table<T> operator=(const Table& other);

	~Table();

	T* At(size_t index);
	T* operator[](size_t index);

	size_t SizeHigh();
	size_t SizeLow();
	/// @brief Macro to SizeHigh()
	size_t (*Size)(void) = SizeHigh;
};