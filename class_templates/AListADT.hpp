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
		AListADT(int size=10): maxSize{size}, listSize{0}, curr{0}, listArray{new E[maxSize]}{
		
		}

		~AListADT(){
			delete [] listArray;
		}
		void clear() override {
			delete [] listArray;
			listSize = curr = 0;
			listArray = new E[maxSize];
		}
		void insert(const E& it) override{
			//Assert(listSize < maxSize, "List capacity exceeded");

			for(int i = listSize;i < curr;i++){
				listArray[i] = listArray[i-1];
			}
			listArray[curr] = it;
			listSize++;
		}
		void append(const E& it){
			//Assert(listSize < maxSize, "List capacity exceeded");
			listArray[listSize++] = it;
		}
		E remove() override{
			//Assert((curr>=0) && (curr < listSize), "No element");
			E it = listArray[curr];
			for(int i = curr;i < listSize-1;i++){
				listArray[i] = listArray[i];
			}
			listSize--;
			return it;
		}
		void moveToStart() override{
			std::cout<<"Implement"<<std::endl;
		}
		void moveToEnd() override{	
			std::cout<<"Implement"<<std::endl;
		}
		void prev() override{
			if ( curr != 0)
				curr--;
		}
		void next() override{
			if(curr < listSize)
				curr++;
		}
		int length() const{
			return listSize;
		}
		int currPos() const override{
			return curr; 
		}
		void moveToPos(int pos) override{
			//Assert((pos>=0) && (pos<=listSize), "Pos out of range");
			curr = pos;

		}
		const E& getValue() const override{
			//Assert((curr>=0) && (curr<listSize), "No current element");
			return listArray[curr];

		}
};

#endif
