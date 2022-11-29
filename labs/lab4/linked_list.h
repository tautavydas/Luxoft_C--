#include <iostream>

class LinkedList {
private:
	struct Node {
		int value;
		Node *next;
	};
	Node* _first{nullptr};

public:
	LinkedList();
	LinkedList(std::initializer_list<int> list);
	LinkedList(LinkedList const& copy);

	virtual ~LinkedList();
	void insertAt(size_t index, int value);
	void removeAt(size_t index);
	size_t getLength() const;
	friend bool operator==(LinkedList const& op1, LinkedList const& op2);
	friend std::ostream& operator<<(std::ostream& os, LinkedList const& list);
};

std::ostream& operator<<(std::ostream& os, LinkedList const& list);
