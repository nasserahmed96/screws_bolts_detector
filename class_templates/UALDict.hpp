#ifndef UALDICT
#define UALDICT

#include "DictionaryADT.hpp"
#include "AListADT.hpp"
#include "KVPair.hpp"


template <typename Key, typename E>
class UALDict : public DictionaryADT<Key, E>{
	private:
		AListADT<KVPair<Key, E>> *list;
	public:
		UALDict(int size = 5){
			list = new AListADT<KVPair<Key, E>>(size);
		}
		~UALDict() {
			delete list;
		}
		void clear() {
			list->clear();
		}
		void insert(const Key& k, const E& e){
			KVPair<Key, E> temp(k, e);
			list->append(temp);
		}

		E remove(const Key& k){
			E temp = find(k);
			if (temp != NULL) list->remove();
			return temp;
		}

		//Remove the last element from the dictionary
		E removeAny(){
			list->moveToEnd();
			list->prev();
			KVPair<Key, E> e = list->remove();
			return e.value();
		}

		E find(const Key& k) const {
			for(list->moveToStart(); list->currPos() < list->length(); list->next()){
				KVPair<Key, E> temp = list->getValue();
				if (k == temp.key())
					return temp.value();
		}
			return NULL;
		}

		int size() {
			return list->length();
		}


};

#endif
