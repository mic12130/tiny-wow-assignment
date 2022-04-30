#pragma once

class TimedEventHandleable {
 public:
  virtual ~TimedEventHandleable() = default;
  virtual void OnTimedEvent(int counter) = 0;
};