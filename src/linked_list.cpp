#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* paste_node = new Node(value);
    if (front_ == nullptr) {
      front_ = paste_node;
      back_ = paste_node;
    } else {
      back_->next = paste_node;
      back_ = paste_node;
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    Node* paste_node = new Node(value);
    if (index <= size_ and index >= 0) {
      if (front_ == nullptr){
        front_ = paste_node;
        back_ = paste_node;
        size_ += 1;
        return true;
      }
      if (index == 0){
        paste_node->next = front_;
        front_ = paste_node;
        size_ += 1;
        return true;
      }
      if (index == size_){
        back_->next = paste_node;
        back_ = paste_node;
        size_ += 1;
        return true;
      }
//      Node* paste_node = new Node(value);
      Node* change_perem = front_;
      if (0 < index and index < size_){
        Node* previous = FindNode((index - 1));
        paste_node->next = previous->next;
        previous->next = paste_node;
        size_++;
        return true;
      }
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < size_ and index >= 0) {
      Node* change_perem = front_;
      int i = 1;
      while (change_perem != nullptr) {
        if (i == index) {
          change_perem->value = new_value;
          return true;
        }
        change_perem = change_perem->next;
        i += 1;
      }
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < size_ and index >= 0 and front_ != nullptr) {
      if (index == 0){
        Node* prev = front_;
        int ans = prev->value;
        front_ = front_->next;
        size_-=1;
        prev->next = nullptr;
        return ans;
      }
      if (index == size_-1){
        Node* prev_last = FindNode(index-1);
        int ans = back_->value;
        back_ = prev_last;
        size_ -=1;
        back_->next = nullptr;
        return ans;
      }
//      Node* change_perem = front_;
      if (0 < index and index < size_){
        int ans = FindNode(index)->value;
        Node* previous = FindNode((index - 1));
        Node* next = FindNode(index+1);
        previous->next = next;
        size_-=1;
        FindNode(index)->next = nullptr;
        return ans;
      }
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /**/) {
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < size_ and index >= 0) {
      Node* change_perem = front_;
      int i = 0;
      while (change_perem != nullptr) {
        if (i == index) {
          return change_perem->value;
        }
        change_perem = change_perem->next;
        i += 1;
      }
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* change_perem = front_;
    int i = 0;
    while (change_perem != nullptr) {
      if (change_perem->value == value) {
        return i;
      }
      change_perem = change_perem->next;
      i += 1;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* change_perem = front_;
    int i = 0;
    while (change_perem != nullptr) {
      if (change_perem->value == value) {
        return true;
      }
      change_perem = change_perem->next;
      i += 1;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < size_ and index >= 0) {
      Node* change_perem = front_;
      int i = 0;
      while (change_perem != nullptr) {
        if (i == index) {
          return change_perem;
        }
        change_perem = change_perem->next;
        i += 1;
      }
    }
    return nullptr;
  }
  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment