#pragma once
template <class Type>
class DynArray
{
private:
	Type * array;
	unsigned int Size, Capacity;

public:

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Constructor
	// Notes : Constructs an empty array (Size 0 Capacity 0)
	/////////////////////////////////////////////////////////////////////////////
	DynArray() { Size = 0; Capacity = 0; array = nullptr; }

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Destructor
	// Notes : cleans up any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	~DynArray() { Size = 0; Capacity = 0; delete[] array; array = nullptr;}

		/////////////////////////////////////////////////////////////////////////////
		// Function :	Copy Constructor
		/////////////////////////////////////////////////////////////////////////////
		DynArray(const DynArray<Type>& that) 
		{
			this->Size = that.Size;
			this->Capacity = that.Capacity;
			this->array = new Type[this->Capacity];
			for (unsigned int i = 0; i < Size; ++i)
			{
				this->array[i] = that.array[i];
			}
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function :	Assignment Operator
		/////////////////////////////////////////////////////////////////////////////
		DynArray<Type>& operator=(const DynArray<Type>& that)
		{
			if (this == &that)
			{
				return *this;
			}
			else {

				this->clear();
				this->Size = that.Size;
				this->Capacity = that.Capacity;
				this->array = new Type[this->Capacity];
				for (int i = 0; i < this->Size; ++i)
				{
					this->array[i] = that.array[i];
				}
				return *this;
			}
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : operator[]
		// Parameters : index - the index to access
		// Return : Type & - returns the array element at [index]
		// Notes : performs no error checking. user should ensure index is 
		//		valid with the size() method
		/////////////////////////////////////////////////////////////////////////////
		Type& operator[](const unsigned int index)
		{
			return this->array[index];
		}


		/////////////////////////////////////////////////////////////////////////////
		// Function : operator[]
		// Parameters : index - the index to access
		// Return : const Type & - returns the array element at [index]
		// Notes : performs no error checking. user should ensure index is 
		//		valid with the size() method
		/////////////////////////////////////////////////////////////////////////////
		const Type& operator[](const unsigned int index) const
		{
			return this->array[index];
		}
		
		/////////////////////////////////////////////////////////////////////////////
		// Function :	size
		// Returns : int - returns the number of items being stored
		// Notes : this function returns the number of items being stored, 
		/////////////////////////////////////////////////////////////////////////////
		unsigned int size() const { return Size; }
		/////////////////////////////////////////////////////////////////////////////
		// Function : capacity
		// Returns : int - returns the number of items the array can store before 
		//		the next resize
		// Notes : this function returns the number of items the array can store, 
		//		not the number of bytes
		/////////////////////////////////////////////////////////////////////////////
		unsigned int capacity() const { return Capacity; }

		/////////////////////////////////////////////////////////////////////////////
		// Function :	clear
		// Notes : cleans up any dynamic memory and resets size and capacity to 0
		/////////////////////////////////////////////////////////////////////////////
		void clear() { Size = 0; Capacity = 0; delete[] array; array = nullptr; }

		/////////////////////////////////////////////////////////////////////////////
		// Function : append
		// Parameters : item - the item to be appended to the next open spot
		// Notes : this function will append the item to the next open spot. if 
		//		no room exists, the array's capacity will be doubled and then 
		//		the item will be added
		/////////////////////////////////////////////////////////////////////////////
		void append(const Type& item)
		{
			if (Size == Capacity)
			{
				reserve();
			}
			this->array[Size] = item;
			
			++Size;
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : reserve
		// Parameters : newCap - the new capacity
		// Notes : 	- default parameter - reserve more space in the array, based on
		//		the expansion rate (100%, 1 minimum).
		//		- non-default parameter, expand to the specified capacity
		//		- if newCap is LESS than the current capacity, do nothing. 
		//		This function should NOT make the array smaller.
		/////////////////////////////////////////////////////////////////////////////
		void reserve(const unsigned int & newCap = 0)
		{
			Type *tempArray;
			if (newCap == 0)
			{
				if (Capacity != 0) {

					Capacity *= 2;
				}
				else {
					Capacity = 1;
				}
			}
			else if(newCap > Capacity)
			{
				Capacity = newCap;
			}
			else
			{
				return;
			}
			tempArray = new Type[Capacity];
			for (unsigned int i = 0; i < Size; ++i)
			{
				tempArray[i] = this->array[i];
			}
			delete[] array;
			this->array = tempArray;
			//tempArray = nullptr;
		}

};

