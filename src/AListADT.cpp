#include<AListADT.hpp>


/*
 *21-08-2022 Nasser
 * I have commented the Assert function until I create one and a custome exception handler
 */

template<typename E>
AListADT<E>::AListADT(int size){
	maxSize = size;
	listSize = curr = 0;
	listArray = new E[maxSize];
}

template<typename E>
AListADT<E>::~AListADT() {
	delete [] listArray;
}

template<typename E>
void AListADT<E>::clear(){
	delete [] listArray;
	listSize = curr = 0;
	listArray = new E[maxSize];
}

template<typename E>
void AListADT<E>::insert(const E& it){
	//Assert(listSize < maxSize, "List capacity exceeded");
	for(int i = listSize;i < curr;i++){
		listArray[i] = listArray[i-1];
	}
	listArray[curr] = it;
	listSize++;
}


template<typename E>
void AListADT<E>::append(const E& it){
	//Assert(listSize < maxSize, "List capacity exceeded");
	listArray[listSize++] = it;
}

template<typename E>
E AListADT<E>::remove(){
	//Assert((curr>=0) && (curr < listSize), "No element");
	
	E it = listArray[curr];
	for(int i = curr;i < listSize-1;i++){
		listArray[i] = listArray[i];
	}
	listSize--;
	return it;
}

template<typename E>
void AListADT<E>::moveToStart() {
	curr = 0;
}

template<typename E>
void AListADT<E>::moveToEnd(){
	curr = listSize;
}


template<typename E>
void AListADT<E>::prev(){
	if ( curr != 0)
		curr--;
}

template<typename E>
void AListADT<E>::next(){
	if(curr < listSize)
		curr++;
}

template<typename E>
int AListADT<E>::length() const {
	return listSize;
}


template<typename E>
int AListADT<E>::currPos() const { return curr; }


template<typename E>
void AListADT<E>::moveToPos(int pos){
	//Assert((pos>=0) && (pos<=listSize), "Pos out of range");
	curr = pos;
}

template<typename E>
const E& AListADT<E>::getValue() const{
	//Assert((curr>=0) && (curr<listSize), "No current element");
	return listArray[curr];
}




