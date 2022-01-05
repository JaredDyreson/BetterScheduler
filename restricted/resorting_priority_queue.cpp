#include <any>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <thread>

// AUTHOR: https://stackoverflow.com/a/38553502

class Accessor;

using topic_type = std::string;
using timestamp_clock = std::chrono::system_clock;
using timestamp_type = timestamp_clock::time_point;

struct node {
  topic_type topic;
  timestamp_type timestamp;
};

bool topic_equals(const node& l, const topic_type& r) { return l.topic == r; }
bool topic_equals(const topic_type& l, const node& r) { return l == r.topic; }

bool age_after(const node& l, const node& r) {
  return l.timestamp > r.timestamp;
}

bool age_after(const node& l, const timestamp_type& r) {
  return l.timestamp > r;
}

bool age_after(const timestamp_type& l, const node& r) {
  return l > r.timestamp;
}

struct greater_age {
  template <class T, class U>
  bool operator()(const T& l, const U& r) const {
    return age_after(l, r);
  }
};

template <class T>
struct pending_queue_traits;

template <>
struct pending_queue_traits<node> {
  using container_type = std::vector<node>;
  using predicate_type = greater_age;
  using type = std::priority_queue<node, container_type, predicate_type>;
};

class pending_node_queue : private pending_queue_traits<node>::type {
  using traits_type = pending_queue_traits<node>;
  using base_class = traits_type::type;

 public:
  // export the constructor
  using base_class::base_class;

  // and any other members our clients will need
  using base_class::pop;
  using base_class::size;
  using base_class::top;

  bool conditional_add(topic_type topic,
                       timestamp_type timestamp = timestamp_clock::now()) {
    auto same_topic = [&topic](auto& x) { return topic_equals(topic, x); };
    auto i = std::find_if(std::begin(c), std::end(c), same_topic);
    if (i == std::end(c)) {
      this->push(node{std::move(topic), std::move(timestamp)});
      return true;
    } else {
      if (timestamp < i->timestamp) {
        i->timestamp = std::move(timestamp);
        reorder();
        return true;
      }
    }
    return false;
  }
  friend class Accessor;

 private:
  void reorder() { std::make_heap(std::begin(c), std::end(c), comp); }
};

class Accessor {
 public:
   Accessor(pending_node_queue _queue) {
     this->myQueue = _queue;
   }
  inline static pending_node_queue myQueue;

  static void reorderQueue() { 
    std::cout << "I am reordering because I was told to" << std::endl;
    myQueue.reorder(); 
  }
  bool isQueueEmpty() const { return this->myQueue.empty(); }
};

// attempt to steal only the base class...
void try_to_slice(pending_queue_traits<node>::type naughty_slice) {
  // danger lurks here
}
void run() {
  // I want this block of code to be run
  // every....1 second
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "We need to update the queue now" << std::endl;
}

void timer_start(std::function<void(void)> func, unsigned int interval) {
  std::thread([func, interval]() {
    while (true) {
      auto x = std::chrono::steady_clock::now() +
               std::chrono::milliseconds(interval);
      func();
      std::this_thread::sleep_until(x);
    }
  }).detach();
}

void do_something() { std::cout << "I am doing something" << std::endl; }

int main() {
  using namespace std::literals;
  auto pn = pending_node_queue();
  auto accessor = Accessor(pn);

  timer_start(accessor.reorderQueue, 1000);

  auto now = timestamp_clock::now();
  pn.conditional_add("bar.baz", now);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  pn.conditional_add("foo.bar", now + 1000ms);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  pn.conditional_add("foo.bar", now + 2000ms);
  pn.conditional_add("foo.bar", now - 2000ms);
  // pn.conditional_add("foo.foo", now + 200ms);

  // assert that there are only 2 nodes
  assert(pn.size() == 2);
  assert(pn.top().topic == "foo.bar");
  pn.pop();
  assert(pn.top().topic == "bar.baz");
  pn.pop();
  assert(pn.size() == 0);

  // std::cout << "manually invoking reording" << std::endl;

  // accessor.reorderQueue(pn);
  // std::cout << "complete!" << std::endl;

  // try to slice the container. these expressions won't compile.
  //    try_to_slice(pn);
  //    try_to_slice(std::move(pn));
  return 0;
}

