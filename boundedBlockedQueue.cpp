//Size of the queue is intialized using constructor call. Synchronization is done using condition variables.
//Push function waits for the condition variable from pop when the size of the queue is full.
//Pop function waits for the condition variable from push function when queue is empty.
class BoundedBlockingQueue {
public:
    queue<int> bq;
    std::mutex m;
    std::condition_variable push_cond;
    std::condition_variable pop_cond;
    const int sz;
    
    BoundedBlockingQueue(int capacity) : sz(capacity) {}
    
    void enqueue(int element) {
        
        std::unique_lock<std::mutex> lk(m);
        if (bq.size() == sz) {
            pop_cond.wait(lk, [this] { return (bq.size() != sz); });  
        }
        
        bq.push(element);
        push_cond.notify_one();
    }
    
    int dequeue() {
        
        std::unique_lock<std::mutex> lk(m);
        if (bq.size()==0) {
            push_cond.wait(lk, [this] { return (bq.size() != 0);} );
        }
        
        int ret = bq.front();
        bq.pop();
        pop_cond.notify_one();
        return ret;
    }
    
    int size() {
        
        std::unique_lock<std::mutex> lk(m);
        return bq.size();
    }
};
