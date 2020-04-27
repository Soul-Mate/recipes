#include <event2/event.h>
#include <cassert>
class EventBase
{
public:
    EventBase();
    EventBase(struct event_config *cfg);
    ~EventBase();

private:
    struct event_base *eb_;
};

EventBase::EventBase()
{
    eb_ = event_base_new();
    assert(eb_);
}

EventBase::EventBase(struct event_config *cfg)
{
}

EventBase::~EventBase()
{
    event_base_free(eb_);
}
