#pragma once

#include <functional> // std::less
#include <iterator>

// This is C++ magic which will allows our function
// to default to using a < b if the comparator arg
// is unspecified. It uses defines std::less<T>
// for the iterator's value_type.
//
// For example: if you have a vector<float>, the 
// iterator's value type will be float. std::less 
// will select the < for sorting floats as the 
// default comparator.

namespace sort {
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;
	// template<typename RandomIter>
	// using greater_for_iter = std::greater<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept { 
		T hold_a = std::move(a);
		a = std::move(b);
		b = std::move(hold_a);
	 }

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// You may delete the types you don't use to remove the compiler warnings
		using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
		using value_type      = typename _it::value_type;
		using reference       = typename _it::reference;
		using pointer         = typename _it::pointer;

		// COMPLETE
		if (end == begin) {
			return;
		}
		for (RandomIter k = end - 1; k != begin; k--) {
			// std::cout << "k: " << *k << std::endl;
			bool go_on = false;
			for (RandomIter n = begin; n != k; n++) {
				if (comp(*(n+1),*n)) {
					swap(*(n+1),*n);
					// std::cout << "swapped " << *n << " with " << *(n+1) << std::endl;
					go_on = true;
				}
			}
			if (!go_on) {
				break;
			}
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) { 
		for (RandomIter i = begin; i != end; i++) {
			// std::cout << "i: " << *i << std::endl;
			// RandomIter temp = i;
			for (RandomIter j = i; j != begin && comp(*(j),*(j-1)); j--) {
				// std::cout << "switching " << *(j-1) << " and " << *j << std::endl;
				swap(*(j),*(j-1));
			}
		}
	}



	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// ptrdiff_t _size = (end - begin) - 1;
		for (RandomIter i = begin; i != end ; i++) {
			RandomIter index = i;
			for (RandomIter j = i + 1; j < end; j++) {
				if (comp(*j,*index)) {
					index = j;
				}
			}
			swap(*index,*i);
		}
	}
}
