template <typename T>
class scoped_ptr {
	T * ptr_;
	scoped_ptr(scoped_ptr<T> const & other) = delete;             // Запрет конструктора копирования
	scoped_ptr & operator=(scoped_ptr<T> const & other) = delete; // Запрет копирующего присваивания 
public:
	scoped_ptr(T * ptr): ptr_(ptr){ }
	
	~scoped_ptr() {
		if (ptr_) {
			delete ptr_;
		}
	}

	T * operator->() { 
	//	if (ptr_) {
			return ptr_;
	//	}
	}

	T & operator* () { 
	//	if (ptr_) {
			return *ptr_;
	//	}
	}

	T * get() const {
	//	if (ptr_) {
			return ptr_;
	//	}
	}

	void reset(T * ptr = nullptr);

	bool isEmpty();

	void swap(scoped_ptr & other);
};

template <typename T>
void scoped_ptr<T>::swap(scoped_ptr & other) {
	if (ptr_ || other.ptr_) {
		T * buff = ptr_;
		ptr_ = other.ptr_;
		other.ptr_ = buff;
	}
}

template <typename T>
bool scoped_ptr<T>::isEmpty() {
	if (ptr_) {
		return false;
	}
	return true;
}

template <typename T>
void scoped_ptr<T>::reset(T * ptr) {
	if (ptr_) {
		delete ptr_;
		ptr_ = ptr;
	}
}
