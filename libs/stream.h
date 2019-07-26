/*
 * Created by Federico Manuel Gomez Peter
 * Date: 26/04/19
 */

#ifndef __STREAM_H__
#define __STREAM_H__

#include <atomic>
#include <condition_variable>
#include <queue>

#include "exception.h"

namespace IO {
template <typename Msg>
class Stream {
   public:
    Stream() {}
    Stream(Stream &&other) = default;
    Stream &operator=(Stream &&other) = default;
    Stream &operator=(Stream &other) = delete;

    ~Stream() {
        this->close();
    }

    void push(const Msg &m) {
        std::unique_lock<std::mutex> lock(this->mutex);
        this->q.push(m);
        this->notEmpty.notify_all();
    }

    bool pop(Msg &m, bool block = true) {
        std::unique_lock<std::mutex> lock(this->mutex);
        while (this->q.empty() && !this->closed) {
            if (!block) {
                return false;
            }
            this->notEmpty.wait(lock);
        }

        if (this->closed) {
            throw Exception{"Stream closed"};
        }

        m = this->q.front();
        this->q.pop();
        return true;
    }

    Stream &operator<<(const Msg &m) {
        this->push(m);
        return *this;
    }

    Stream &operator>>(Msg &m) {
        this->pop(m);
        return *this;
    }

    void close() {
        if (this->closed) {
            return;
        }
        this->closed = true;
        this->notEmpty.notify_all();
    }

   private:
    std::queue<Msg> q;
    std::mutex mutex;
    std::condition_variable notEmpty;
    std::atomic<bool> closed{false};
};
}  // namespace IO
#endif  //__STREAM_H__