#include <iostream>

class tree_t
{
private:
	struct node_t {
		node_t * left;
		node_t * right;
		int value;
	};
private:
	node_t * root_;
	void destroy(node_t * curr_);
	bool search(int value, const node_t * curr_, bool & success) const;
	void inorder(std::ostream & stream, const node_t * curr_, int count) const;
public:
	tree_t();
	~tree_t();
	void insert(int value);
	bool find(int value) const;
	void print(std::ostream & stream) const;
};

tree_t::tree_t() {
	root_ = nullptr;
}

tree_t::~tree_t() {
	destroy(root_);
}

void tree_t::destroy(node_t * curr_) {
	if (curr_) {
		destroy(curr_->right);
		destroy(curr_->left);
		delete curr_;
	}
}

void tree_t::insert(int value) {
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

bool tree_t::find(int value) const {
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

bool tree_t::search(int value, const node_t * curr_, bool & success) const {
	if (curr_) {
		if (curr_->value != value) {
			search(value, curr_->left, success);
			search(value, curr_->right, success);
		}
		else if (curr_->value == value) {
			success = true;
		}
	}
	return true;
}

void tree_t::print(std::ostream & stream) const {
	int count = 1;
	inorder(stream, root_, count);
}

void tree_t::inorder(std::ostream & stream, const node_t * curr_, int count) const {
	if (curr_) {
		if (curr_->right) {
			count++;
			inorder(stream, curr_->right, count);
		}

		if (!curr_->right) {
			for (int i = 0; i < count; ++i) {
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
			for (int i = 0; i < count; ++i) {
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
