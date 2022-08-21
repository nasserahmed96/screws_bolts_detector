#ifndef KVPAIR
#define KVPAIR


template <typename Key, typename E>
class KVPair{
	private:
	       	Key k;
		E e;
	public:
		KVPair();
		KVPair(Key kval, E val);
		KVPair(const KVPair& o);
		void operator =(const KVPair &o);
		Key key();
		void setKey(Key ink);
		E value();
}


	
