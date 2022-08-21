#ifndef ALISTADT
#define ALISTADT

#include <ListADT.hpp>

template<typename E>
class AListADT: public ListADT<E>{
	private:
		int maxSize;
		int listSize;
		int curr;
		E* listArray;
	public:
		AListADT(int size=10);
		~AListADT();
		void clear();
		void insert(const E&);
		void append(const E&);
		E remove();
		void moveToStart();
		void moveToEnd();
		void prev();
		void next();
		int length() const;
		int currPos() const;
		void moveToPos(int pos);
		const E& getValue() const;
};
#endif
