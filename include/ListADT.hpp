#ifndef LISTADT
#define LISTADT

template <typename E>
class ListADT{
	private:
		void operator = (const ListADT&);
		ListADT (const ListADT&);
	public:
		ListADT();
		virtual ~ListADT();
		virtual void clear() = 0;
		virtual void insert(const E& item) = 0;
		virtual E remove() = 0;
		virtual void moveToStart() = 0;
		virtual void moveToEnd() = 0;
		virtual void prev() = 0;
		virtual void next() = 0;
		virtual int currPos() const = 0;
		virtual void moveToPos(int pos) const = 0;
		virtual const E& getValue() const = 0;
};
#endif
