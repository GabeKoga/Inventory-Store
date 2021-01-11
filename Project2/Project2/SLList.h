#pragma once

// forward declaration
template<typename Type> class SLLIter;

// class SLList
template<typename Type> class SLList
{
	// the iterator is the list’s friend
	friend class SLLIter<Type>;

	// add members/methods here…
	struct Node
	{
		Type data;
		Node *next;
	};
	Node *head;
	unsigned int Size;

public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty list
	/////////////////////////////////////////////////////////////////////////////
	SLList() {
		head = nullptr;
		Size = 0;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : Destroys the list
	/////////////////////////////////////////////////////////////////////////////
	~SLList() {
		while (head != nullptr) {
			Node *temp = head;
			head = head->next;
			delete temp;
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear() {
		while (head != nullptr) {
			Node *temp = head;
			head = head->next;
			delete temp;
		}
		Size = 0;
	}

	void recurse(Node *that) {
		if (that != nullptr) {
			recurse(that->next);
			addHead(that->data);
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that) {
		if (this->head != that.head)
		{
			clear();
			recurse(that.head);
			this->Size = that.Size;
		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that) {
		recurse(that.head);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : addHead
	// Parameters :	v - the item to add to the list
	/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v) {
		Node *temp = new Node;
		temp->data = v;
		temp->next = head;
		head = temp;
		Size++;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :	index - an iterator to the location to insert at
	//				v - the item to insert
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v) {
		Node *temp = new Node;
		temp->data = v;
		if (index.cur != nullptr) {

			if (index.prev == nullptr) {
				temp->next = index.cur;
				index.cur = temp;
				index.list->head = index.cur;
			}
			else {
				temp->next = index.cur;
				index.prev->next = temp;
			}
			index.cur = temp;
			Size++;
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : remove
	// Parameters :	index - an iterator to the location to remove from
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index) {
		if (index.cur != nullptr) {
			if (index.prev == nullptr) {
				Node *temp = index.cur;
				index.cur = index.cur->next;
				index.list->head = index.cur;
				delete temp;
			}
			else {
				index.prev->next = index.cur->next;
				delete index.cur;
				index.cur = index.prev->next;
			}
			Size--;
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : size
	// Return : the number of items stored in the linked list.
	/////////////////////////////////////////////////////////////////////////////
	inline unsigned int size() const {
		return Size;
	}

};

// class SLLIter
template<typename Type> class SLLIter
{
	// the list is the iterator’s friend
	friend class SLList<Type>;

	// add members/methods here…
	typename SLList<Type>::Node *prev, *cur;
	SLList<Type> *list;
public:

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	/////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate) {
		list = &listToIterate;
		cur = list->head;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list
	/////////////////////////////////////////////////////////////////////////////
	void begin() {
		cur = list->head;
		prev = nullptr;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of the list, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool end() const {
		if (cur == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++() {
		if (cur != nullptr) {
			prev = cur;
			cur = cur->next;
		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location
	/////////////////////////////////////////////////////////////////////////////
	Type& current() const {
		return cur->data;
	}

};


