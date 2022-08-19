template<typename Key, typename E>
class DictionaryADT{
	private:
		void operator =(const DictionaryADT&);
		DictionaryADT(const DictionaryADT&);
	public:
		DictionaryADT();
		virtual ~Dictionary() {}
		virtual void clear() = 0;
		virtual void insert(const Key& k, const E& e) = 0;
		virtual E remove(const Key& k) = 0;
		virtual E removeAny() = 0;
		virtual E find(const Key& k) const = 0;
		virtual int size() = 0;
};

