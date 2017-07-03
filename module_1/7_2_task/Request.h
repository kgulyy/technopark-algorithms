#ifndef TASKS_REQUEST_H
#define TASKS_REQUEST_H

class Request {
 private:
  int start;
  int finish;
  
 public:
  Request() {}
  Request(int start, int finish) : start(start), finish(finish) {}
  int getStart() const {
    return start;
  }
  int getFinish() const {
    return finish;
  }
};

#endif //TASKS_REQUEST_H