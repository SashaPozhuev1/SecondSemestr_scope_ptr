#include <iostream>
#include <sstream>

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
public:
	tree_t();
	~tree_t();
	void insert(T value);
	bool find(T value) const;
	void print(std::ostream & stream) const;
	bool read(std::istream & stream);
	
	node_t * root() {
		return *root_;
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

	if (success) {
		std::cout << "true\n";
	}
	else {
		std::cout << "false\n";
	}
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
bool tree_t<T>::read(std::istream & stream) {
	bool success = true;
	char symb;
	if (stream >> symb) {
		if (symb == '+' || symb == '?') {
			T value;
			if (stream >> value && symb == '+') {
				insert(value);
			}
			else if (symb == '?') {
				find(value);
			}
		}
		else if (symb == '=') {
			print(std::cout);
		}
		else if (symb == 'q') {
			success = false;
		}
	}
	return success; 
}
