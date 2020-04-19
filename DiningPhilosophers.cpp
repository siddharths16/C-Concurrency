class DiningPhilosophers {
public:

    vector<std::mutex> lock_vec = vector<std::mutex>(5);
    DiningPhilosophers() {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        int id_lfork = philosopher;
        int id_rfork;
        if (philosopher == 4)
            id_rfork = 0;
        else
            id_rfork = philosopher + 1;
        
        std::unique_lock<std::mutex> lock_left(lock_vec[id_lfork], std::defer_lock);
        std::unique_lock<std::mutex> lock_right(lock_vec[id_rfork], std::defer_lock);
        
        std::lock(lock_left, lock_right);
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();   
            
    }
};
