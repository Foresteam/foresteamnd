#pragma once
#include <exception>

template <typename Item>
struct STACK {
	Item data;
	STACK<Item>* next;
	STACK(Item data, STACK<Item>* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};

template <typename Item>
class Stack {
private:
	STACK<Item>* self;
	size_t size;
public:
	static void Swap(STACK<Item>* a, STACK<Item>* b) {
		STACK<Item>* t;
		t = b->next;
		b->next = a;
		a->next = t;
	}

	Stack() {
		size = 0;
		self = nullptr;
	}

	void Push(Item item) {
		self = new STACK<Item>(item, self);
		size += 1;
	}
	/// @throws StackUnderflow
	void Drop() {
		STACK<Item>* pt = self;
		self = self->next;
		delete pt;
		this->size -= 1;
	}
	/// @throws StackUnderflow
	Item Pop() {
		Item r = self->data;
		Drop();

		return r;
	}
	Item* Peek() {
		return &self->data;
	}
	void Dup() {
		Push(*Peek());
	}
	void Swap() {
		STACK<Item>* a = self, * b = self->next;
		Stack::Swap(a, b);
		self = b;
	}
	void Rot() {
		STACK<Item> *a = self, *b = a->next, *c = b->next;
		Stack::Swap(a, c);
		Stack::Swap(b, a);
		self = c;
	}
	void Flip() {
		Stack<Item> n;
		while (!IsEmpty())
			n.Push(Pop());
		*this = n;
	}
	bool IsEmpty() {
		return self == nullptr;
	}

	size_t GetSize() {
		return this->size;
	}
};