#include "world/TimedEventDispatcher.h"

void TimedEventDispatcher::AddHandler(
    std::shared_ptr<TimedEventHandleable> handler) {
  handlers.push_back(handler);
}

void TimedEventDispatcher::OnTick(int counter) {
  for (const auto& h : handlers) {
    h->OnTimedEvent(counter);
  }
}