//https://leetcode.com/problems/traffic-light-controlled-intersection/

class TrafficLight {
public:
    TrafficLight() : greenRoad(1) {}

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        
        std::scoped_lock<std::mutex> lock_a(mutex_road);
        if (roadId != greenRoad) {
            greenRoad = roadId;
            turnGreen();
        }
        
        crossCar();
    }
    
private:
    std::mutex mutex_road;
    int greenRoad;
    
};
