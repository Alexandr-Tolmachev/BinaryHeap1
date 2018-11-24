#include<iostream>
#include<algorithm>
#include "Array.h"
using std::min;
using std::max;
using std::cerr;

template <typename Key>
class BinaryHeap {
public:
	class Pointer {
	public:
		Pointer() : index(0) {}
		//~Pointer();
		Key index;
	private:
		friend class BinaryHeap;
	};

	BinaryHeap() { }

	template <class Iterator>
	BinaryHeap(Iterator begin, Iterator end) {
		for (Iterator it = begin; it != end; ++it) {
			Pointer* pointer = new Pointer();
			pointer->index = heap_array.size();
			back_ptr.add(pointer);
			heap_array.add(*it);
		}
		for (int i = heap_array.size() - 1; i >= 0; --i)
			sift_down(i);
	}

	
	void optimize(int insertCount, int extractCount) {
		try {
			if (insertCount <= 0 || extractCount <= 0) {
				throw out_of_range("Value exceeds range");
			}
		}
		catch (out_of_range& err) {
			cerr << err.what() << "\n";
			exit(1);
		}
		count_child = max(2, insertCount / extractCount);
	}

	bool is_empty() {
		return (heap_array.size() == 0);
	}

	Key extract_min() {
		try {
			if (is_empty()) {
				throw logic_error("Can't get minimum from empty structures");
			}
		}
		catch (logic_error& err) {
			cerr << err.what() << "\n";
			exit(1);
		}
		Key min = heap_array[0];
		swap(0, heap_array.size() - 1);
		back_ptr.pop_back();
		heap_array.pop_back();
		sift_down(0);
		return min;
	}

	Key get_min() {
		try {
			if (is_empty()) {
				throw logic_error("Can't get minimum from empty structures");
			}
		}
		catch (logic_error& err) {
			cerr << err.what() << "\n";
			exit(0);
		}
		return heap_array[0];
	}

	void Delete(Pointer* ptr) {
		try {
			if (ptr == nullptr) {
				throw out_of_range("Pointer exceeds range");
			}
		}
		catch (out_of_range& err) {
			cerr << err.what() << "\n";
			exit(1);
		}
		change(ptr, get_min());
		extract_min();
	}
	
	Pointer* insert(Key element) {
		Pointer* pointer = new Pointer;
		pointer->index = heap_array.size();
		back_ptr.add(pointer);
		heap_array.add(element);
		sift_up(heap_array.size() - 1);
		return pointer;
	}
	
	void change(Pointer* ptr, Key key) {
		try {
			if (ptr == nullptr || !heap_array.is_correct(ptr->index)) {
				throw out_of_range("Pointer exceeds range");
			}
		}
		catch (out_of_range& err) {
			cerr << err.what() << "\n";
			exit(1);
		}
		heap_array[ptr->index] = key;
		if (key < heap_array[(ptr->index - 1) / count_child])
			sift_up(ptr->index);
		else 
			sift_down(ptr->index);
	}
	
private:
	Array<Key> heap_array;
	Array<Pointer* > back_ptr;
	int count_child = 2;

	void swap(Key ind1, Key ind2) {
		if (heap_array.is_correct(ind1) && heap_array.is_correct(ind2)) {
			heap_array.swap(ind1, ind2);

			Pointer* ptr = back_ptr[ind1];
			back_ptr[ind1] = back_ptr[ind2];
			back_ptr[ind2] = ptr;

			back_ptr[ind1]->index = ind1;
			back_ptr[ind2]->index = ind2;

		}
		else {
			try {
				throw out_of_range("Index exceeds range");
			}
			catch (out_of_range& err) {
				cerr << err.what() << "\n";
				exit(1);
			}
		}
	}

	void sift_down(int index) {
		int heap_size = heap_array.size();
		if (count_child * index + 1 < heap_size) {
			int left = count_child * index + 1;
			int right = count_child * index + count_child;
			int curr = left;

			for (int i = left; i <= min(right, heap_size - 1); ++i) {
				if (heap_array[curr] > heap_array[i])
					curr = i;
			}

			if (heap_array[curr] < heap_array[index]) {
				swap(curr, index);
				sift_down(curr);
			}
		}
	}

	void sift_up(int index) {
		while (index > 0) {
			int parent = (index - 1) / count_child;
			if (heap_array[parent] <= heap_array[index])
				return;
			swap(parent, index);
			index = parent;
		}
	}
};


