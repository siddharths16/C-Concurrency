//https://leetcode.com/problems/fizz-buzz-multithreaded/

class FizzBuzz {
private:
    int n;
    int cur = 1;
    std::mutex mutex;
    std::condition_variable cond;
public:
    FizzBuzz(int n) {
        this->n = n;
        cond.notify_all();
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (true) {
            std::unique_lock<std::mutex> lk(mutex);
            cond.wait(lk, [this](){ return ((cur % 3 == 0) && (cur % 5)) || cur > n; });
            if (cur > n) break;
            printFizz();
            ++cur;
            cond.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (true) {
            std::unique_lock<std::mutex> lk(mutex);
            cond.wait(lk, [this](){ return ((cur % 5 == 0) && (cur % 3)) || cur > n; });
            if (cur > n) break;
            printBuzz();
            ++cur;
            cond.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            std::unique_lock<std::mutex> lk(mutex);
            cond.wait(lk, [this](){ return (cur % 15 == 0) || cur > n; });
            if (cur > n) break;
            printFizzBuzz();
            ++cur;
            cond.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (true) {
            std::unique_lock<std::mutex> lk(mutex);
            cond.wait(lk, [this](){ return ((cur % 3) && (cur % 5)) || cur > n; });
            if (cur > n) break;
            printNumber(cur);
            ++cur;
            cond.notify_all();
        }
    }
};
