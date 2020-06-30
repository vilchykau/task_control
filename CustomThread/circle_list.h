#pragma once

template<typename T>
struct circle_list_node {
	T value;
	circle_list_node* prev;
	circle_list_node* next;
};

template<typename T>
class circle_list {
public:
	circle_list() :start_node(nullptr) {}

	T& insert(const T& new_value) {
		node* new_node;
		if (start_node) {
			new_node = new node{ new_value, start_node, start_node->next };
			start_node->next->prev = new_node;
			start_node->next = new_node;
		}
		else {
			new_node = new node{ new_value, nullptr, nullptr };
			new_node->next = new_node;
			new_node->prev = new_node;
			start_node = new_node;
		}
		return new_node->value;
	}

	T& next() {
		return start_node->next->value;
	}

	T& prev() {
		return start_node->prev->value;
	}

	T& get_now() {
		return start_node->value;
	}

	bool is_empty() const {
		return !start_node;
	}

	void go_next() {
		start_node = start_node->next;
	}

	void go_prev() {
		start_node = start_node->prev;
	}

	void pop_now() {
		if (start_node) {
			if (start_node == start_node->next) {
				delete start_node;
				start_node = nullptr;
			}
			else {
				auto prev = start_node->prev;
				auto next = start_node->next;
				delete start_node;
				prev->next = next;
				next->prev = prev;
				start_node = next;
			}
		}
	}
private:
	using node = circle_list_node<T>;

	node* start_node;
};

