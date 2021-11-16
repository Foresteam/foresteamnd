#pragma once
#include <exception>

#define TSTACKITEM template<typename Item>
#define TSTACKNODEITEM template<typename ITEM>

TSTACKITEM class Stack {
private:
	TSTACKNODEITEM struct Node {
		ITEM data;
		Node<ITEM>* next;
		Node(ITEM data, Node<ITEM>* next = nullptr);
	};

	Node<Item>* self;
	size_t size;
public:
	static void Swap(Node<Item>* a, Node<Item>* b);

	Stack();

	void Push(Item item);
	/// @throws StackUnderflow
	void Drop();
	/// @throws StackUnderflow
	Item Pop();
	Item* Peek();
	void Dup();
	void Swap();
	void Rot();
	void Flip();
	bool IsEmpty();

	size_t GetSize();
};