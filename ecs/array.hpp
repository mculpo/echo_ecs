#include <iostream>
template <class T>
class Array {
public:
	Array(uint32_t pCapacity) : mCapacity(pCapacity), mSize(0) {
		mData = new T[mCapacity];
	}

	~Array() {
		delete[] mData;
	}

	void push(const T& element) {
		if (mSize < mCapacity) {
			mData[mSize] = element;
			mSize++;
		}
		else {
			reserve(mCapacity * 2);
		}
	}

	uint32_t size() { return size; }
	uint32_t capacity() { return capacity; }
	void reserve(uint32_t pCapacity) {
		if (pCapacity > mCapacity) {
			T* new_data = new T[pCapacity];
			for (int i = 0; i < mSize; i++) {
				new_data[i] = mData[i];
			}
			delete[] mData;
			mData = new_data;
			mCapacity = pCapacity;
		}
	}
	void showAll() {
		for (int i = 0; i < mSize; i++) {
			std::cout << mData[i] << std::endl;
		}
	}
	void showAllMemorySize() {
		for (int i = 0; i < mSize; i++) {
			std::cout << &mData[i] << std::endl;
		}
	}
	void showAllMemoryCapacity() {
		for (int i = 0; i < mCapacity; i++) {
			std::cout << "index " << i << " / value array: " << mData[i] << ", access memory:" << &mData[i] << std::endl;
		}
	}
	T& operator[](int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range.");
		}
		return mData[index];
	}

private:
	T* mData;
	uint32_t mCapacity;
	uint32_t mSize;
};
