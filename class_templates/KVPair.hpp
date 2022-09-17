#ifndef KVPAIR
#define KVPAIR


template <typename Key, typename E>
class KVPair{
	private:
	       	Key k;
		E e;
	public:
		KVPair() { }
		KVPair(Key kval, E val){
			k = kval;
			e = val;
		}
		KVPair(const KVPair& o){
			k = o.k;
			e = o.e;
		}
		
		void operator =(const KVPair &o){
			k = o.k;
			e = o.e;
		}

		Key key(){
			return k;
		}
		void setKey(Key ink){
			k = ink;
		}

		E value(){
			return e;
		}
};

#endif
	
