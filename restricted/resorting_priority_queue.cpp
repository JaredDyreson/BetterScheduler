#include <queue>
#include <string>
#include <chrono>
#include <cassert>
#include <iostream>

using topic_type = std::string;
using timestamp_clock = std::chrono::system_clock;
using timestamp_type = timestamp_clock::time_point;

struct notification {
    topic_type topic;
    timestamp_type timestamp;
};

bool topic_equals(const notification& l, const topic_type& r) {
    return l.topic == r;
}
bool topic_equals(const topic_type& l, const notification& r) {
    return l == r.topic;
}

bool age_after(const notification& l , const notification& r) {
    return l.timestamp > r.timestamp;
}

bool age_after(const notification& l , const timestamp_type& r) {
    return l.timestamp > r;
}

bool age_after(const timestamp_type& l , const notification& r) {
    return l > r.timestamp;
}

struct greater_age
{
    template<class T, class U>
    bool operator()(const T& l, const U& r) const {
        return age_after(l, r);
    }
};

template<class T>
struct pending_queue_traits;

template<>
struct pending_queue_traits<notification>
{
    using container_type = std::vector<notification>;
    using predicate_type = greater_age;
    using type = std::priority_queue<notification, container_type, predicate_type>;
};

class pending_notification_queue
: private pending_queue_traits<notification>::type
{
    using traits_type = pending_queue_traits<notification>;
    using base_class = traits_type::type;

public:


    // export the constructor
    using base_class::base_class;

    // and any other members our clients will need
    using base_class::top;
    using base_class::pop;
    using base_class::size;

    bool conditional_add(topic_type topic, timestamp_type timestamp = timestamp_clock::now())
    {
        auto same_topic = [&topic](auto& x) { return topic_equals(topic, x); };
        auto i = std::find_if(std::begin(c), std::end(c), same_topic);
        if (i == std::end(c)) {
            this->push(notification{std::move(topic), std::move(timestamp)});
            return true;
        }
        else {
            if (timestamp < i->timestamp) {
                i->timestamp = std::move(timestamp);
                reorder();
                return true;
            }
        }
        return false;
    }

private:
    void reorder() {
        std::make_heap(std::begin(c), std::end(c), comp);
    }
};

// attempt to steal only the base class...
void try_to_slice(pending_queue_traits<notification>::type naughty_slice)
{
    // danger lurks here
}
int main()
{
    using namespace std::literals;

    auto pn = pending_notification_queue();

    auto now = timestamp_clock::now();
    pn.conditional_add("bar.baz", now);
    pn.conditional_add("foo.bar", now + 5ms);
    pn.conditional_add("foo.bar", now + 10ms);
    pn.conditional_add("foo.bar", now - 10ms);

    // assert that there are only 2 notifications
    assert(pn.size() == 2);
    assert(pn.top().topic == "foo.bar");
    pn.pop();
    assert(pn.top().topic == "bar.baz");
    pn.pop();

    // try to slice the container. these expressions won't compile.
//    try_to_slice(pn);
//    try_to_slice(std::move(pn));

}
