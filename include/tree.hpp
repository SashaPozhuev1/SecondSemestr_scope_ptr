template <typename T>
class tree_t
{
private:
	struct node_t {
		node_t * left;
		node_t * right;
		T value;
	};
private:
	node_t * root_;
	void destroy(node_t * curr_);
	bool search(T value, const node_t * curr_, bool & success) const;
	void inorder(std::ostream & stream, const node_t * curr_, std::size_t count) const;
	bool compare(bool & success, node_t * left, node_t * right) const;
	node_t * remser(T value, node_t * curr_, node_t *& newcurr_) {
		if (curr_) {
			if (curr_->value != value) {
				remser(value, curr_->right, newcurr_);
				remser(value, curr_->left, newcurr_);
			}
			else if (curr_->value == value) {
				newcurr_ = curr_;
			}
		}
		return root_;
	}

	node_t * search(const node_t * curr_, node_t * newcurr_, node_t *& pred_) {
		if (newcurr_){
			if (curr_ == root_) {
				pred_ = root_;
				return root_;
			}
			if (newcurr_->right != curr_) {
				search(curr_, newcurr_->right, pred_);
			}
			if (newcurr_->left != curr_) {
				search(curr_, newcurr_->left, pred_);
			}
			if (newcurr_->right == curr_) {
				pred_ = newcurr_;
			}
			if (newcurr_->left == curr_) {
				pred_ = newcurr_;
			}
		}
		return root_;
	}
public:
	tree_t();
	tree_t(std::initializer_list<T> keys);
	~tree_t();
	bool isEmpty();
	void insert(T value);
	bool find(T value) const;
	void print(std::ostream & stream) const;
	auto operator==(tree_t const & other) const;
	bool remove(T value);
	bool read(std::istream & stream, std::ostream & ostream);
	node_t * root() {
		return root_;
	}
};

template <typename T>
tree_t<T>::tree_t() {
	root_ = nullptr;
}

template <typename T>
tree_t<T>::~tree_t() {
	destroy(root_);
}

template <typename T>
void tree_t<T>::destroy(node_t * curr_) {
	if (curr_) {
		destroy(curr_->right);
		destroy(curr_->left);
		delete curr_;
	}
}

template <typename T>
bool tree_t<T>::isEmpty() {
	if (root_) {
		return false;
	}
	return true;
}

template <typename T>
void tree_t<T>::insert(T value) {
	if (!root_) {
		root_ = new node_t;
		root_->value = value;
		root_->left = nullptr;
		root_->right = nullptr;
	}
	else {
		node_t * curr_ = root_;
		while (curr_) {
			if (value >= curr_->value) {
				if (curr_->right) {
					curr_ = curr_->right;
				}
				else {
					curr_->right = new node_t;
					curr_ = curr_->right;
					curr_->value = value;
					curr_->left = nullptr;
					curr_->right = nullptr;
					break;
				}
			}
			else if (value < curr_->value) {
				if (curr_->left) {
					curr_ = curr_->left;
				}
				else {
					curr_->left = new node_t;
					curr_ = curr_->left;
					curr_->value = value;
					curr_->left = nullptr;
					curr_->right = nullptr;
					break;
				}
			}
		}
	}
}

template <typename T>
bool tree_t<T>::find(T value) const {
	bool success = false;
	search(value, root_, success);

/*	if (success) {
		std::cout << "true\n";
	}
	else {
		std::cout << "false\n";
	}*/
	return success;
}

template <typename T>
bool tree_t<T>::search(T value, const node_t * curr_, bool & success) const {
	if (curr_) {
		if (curr_->value != value) {
			search(value, curr_->left, success);
			search(value, curr_->right, success);
		}
		else if (curr_->value == value) {
			success = true;
		}
	}
	return success;
}

template <typename T>
tree_t<T>::tree_t(std::initializer_list<T> keys) {
	root_ = nullptr;
	size_t size = keys.size();
	for (size_t i = 0; i < size; i++) {
		T value = *(keys.begin() + i);
		insert(value);
	}
}

template <typename T>
auto tree_t<T>::operator==(tree_t const & other) const {
	bool success = true;
	compare(success, root_, other.root_);
	return success;
}

template <typename T>
bool tree_t<T>::compare(bool & success, node_t * left, node_t * right) const {
	if (!left && !right) {

	}
	else if (left && right && left->value == right->value) {
		compare(success, left->left, right->left);
		compare(success, left->right, right->right);
	}
	else {
		success = false;
		return success;
	}
	return success;
}

template <typename T>
bool tree_t<T>::remove(T value) {

	node_t * curr_ = root_;
	node_t * newroot_ = root_;
	node_t * pred_ = root_;
	remser(value, newroot_, curr_);
	search(curr_, newroot_, pred_);
	if (curr_->value != value) {
		return false;
	}
	else if (curr_ == pred_) {
		if (curr_->right) {
			root_ = curr_->right;
			node_t * prav = root_;
			while (prav->left) {
				prav = prav->left;
			}
			prav->left = curr_->left;
		}
		else if (curr_->left){
			root_ = curr_->left;
		}
		else {
			root_ = nullptr;
		}
		delete curr_;
	}
	else if (curr_ != pred_){
		if (pred_->right == curr_) {
			if (curr_->right) {
				pred_->right = curr_->right;
				node_t * prav = curr_->right;
				while (prav->left) {
					prav = prav->left;
				}
					prav->left = curr_->left;
			}
			else if (curr_->left) {
				pred_->right = curr_->left;
			}
			else {
				pred_->right = nullptr;
			}
		}
		else if (pred_->left == curr_){
			if (curr_->right) {
				pred_->left = curr_->right;
				node_t * prav = curr_->right;
				while (prav->left) {
					prav = prav->left;
				}
					prav->left = curr_->left;
			}
			else if (curr_->left) {
				pred_->left = curr_->left;
			}
			else {
				pred_->left = nullptr;
			}
		}
		delete curr_;
	}
	return true;
}

template <typename T>
void tree_t<T>::print(std::ostream & stream) const {
	std::size_t count = 1;
	inorder(stream, root_, count);
}

template <typename T>
void tree_t<T>::inorder(std::ostream & stream, const node_t * curr_, std::size_t count) const {
	if (curr_) {
		if (curr_->right) {
			count++;
			inorder(stream, curr_->right, count);
		}

		if (!curr_->right) {
			for (std::size_t i = 0; i < count; ++i) {
				if (i == count - 1) {
					stream << "----";
				}
				else {
					stream << "    ";
				}
			}
			stream << curr_->value << std::endl;
		}
		else {
			count--;
			for (std::size_t i = 0; i < count; ++i) {
				if (i == count - 1) {
					stream << "----";
				}
				else {
					stream << "    ";
				}
			}
			stream << curr_->value << std::endl;
		}
		if (curr_->left) {
			count++;
			inorder(stream, curr_->left, count);
		}
		else {
			count--;
		}

	}
}

template <typename T>
bool tree_t<T>::read(std::istream & stream, std::ostream & ostream) {
	bool success = true;
	char symb;
	if (stream >> symb) {
		if (symb == '+' || symb == '?' || symb == '-') {
			T value;
			if (stream >> value && symb == '+') {
				insert(value);
			}
			else if (symb == '?') {
				find(value);
			}
			else if (symb == '-') {
				if (!remove(value)) {
					ostream << "Key not found\n";
				}
			}
		}
		else if (symb == '=') {
			print(ostream);
		}
		else if (symb == 'q') {
			success = false;
		}
	}
	return success;
}
