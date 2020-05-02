//https://leetcode.com/problems/print-zero-even-odd/
//Zero function acts as a Coordinator and determines which function even/odd should acquire the lock
//based on the current value of count. 
//Exiting the function happens in a clock fashion. Zero is responsible for make even exit and even is responsible //for make odd exit.


class ZeroEvenOdd {
private:
    int n;
    int cnt;
    int call_flag;
    std::mutex m;
    std::condition_variable cond_var;
    
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        cnt = 0;
        call_flag = 0;
    }

    void zero(function<void(int)> printNumber) {
        
        while (true) {
            
            std::unique_lock<std::mutex> lk(m);
            cond_var.wait(lk, [this] {return call_flag == 0;});
            
            if (cnt >= n) {
                cnt = -1;
                //make even exit
                call_flag = 2;
                lk.unlock();
                cond_var.notify_all();
                return;
            }
            
            printNumber(0);
            cnt++;
            if (cnt%2 == 0) {
                call_flag = 2;
            } else {
                call_flag = 1;
            }
            
            lk.unlock();
            cond_var.notify_all();
            
        }
        
    }

    void even(function<void(int)> printNumber) {
        
        while (true) {
            std::unique_lock<std::mutex> lk(m);
            cond_var.wait(lk, [this] {return call_flag == 2;});
            
            if (cnt == -1) {
                //make odd exit
                call_flag = 1;
                lk.unlock();
                cond_var.notify_all();
                return;
            }
            
            printNumber(cnt);
            call_flag = 0;
            lk.unlock();
            cond_var.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        
         while (true) {
            std::unique_lock<std::mutex> lk(m);
            cond_var.wait(lk, [this] {return call_flag == 1;});
            
            if (cnt == -1) {
                call_flag = 0;
                lk.unlock();
                cond_var.notify_all();
                return;
            }
            
            printNumber(cnt);
            call_flag = 0;
            lk.unlock();
            cond_var.notify_all();
        }
    }
};
