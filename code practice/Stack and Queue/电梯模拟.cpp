#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

// Elevator state enumeration
enum ElevatorState
{
    Idle,
    GoingUp,
    GoingDown
};

const int FLOORS = 5;     // Total floors (0–4)
const int BASE_FLOOR = 1; // Base floor (returns here when idle)

// Passenger class: manages current floor, target floor, waiting time, etc.
class Passenger
{
public:
    int currentFloor;
    int targetFloor;
    int waitTime;
    bool isAbandoned;
    bool inElevator;

    Passenger(int cf, int tf)
        : currentFloor(cf), targetFloor(tf), waitTime(0), isAbandoned(false), inElevator(false) {}
};

// Elevator class: manages elevator movement, stops, and button logic
class Elevator
{
public:
    int currentFloor;
    ElevatorState state;
    vector<bool> callCar; // Elevator internal floor buttons
    queue<int> upStops;   // Upward stop queue
    queue<int> downStops; // Downward stop queue
    int idleTime;         // Idle time counter

    Elevator()
        : currentFloor(BASE_FLOOR), state(Idle), callCar(FLOORS, false), idleTime(0) {}

    // Handle internal button press
    void pressCarButton(int floor)
    {
        if (floor < 0 || floor >= FLOORS || floor == currentFloor)
            return;
        callCar[floor] = true;
        if (floor > currentFloor && state != GoingUp)
            state = GoingUp;
        else if (floor < currentFloor && state != GoingDown)
            state = GoingDown;
    }

    // Handle external call buttons
    void pressCallButton(int floor, bool isUp)
    {
        if (floor < 0 || floor >= FLOORS)
            return;
        if (isUp && floor < FLOORS - 1)
            upStops.push(floor);
        else if (!isUp && floor > 0)
            downStops.push(floor);
        if (state == Idle)
        {
            state = (floor > currentFloor) ? GoingUp : GoingDown;
        }
    }

    // Move one floor and update state
    void moveOneFloor()
    {
        if (state == GoingUp)
            currentFloor++;
        else if (state == GoingDown)
            currentFloor--;
        idleTime = 0;
    }

    // Handle stopping at a floor (passengers in/out, state changes)
    bool handleFloorStop(vector<Passenger> &passengers, int &time)
    {
        bool hasAction = false;

        // Passengers getting off
        if (callCar[currentFloor])
        {
            callCar[currentFloor] = false;
            cout << "Time " << time << "t: Elevator stops at " << getFloorName(currentFloor) << ", passengers exit.\n";
            hasAction = true;
        }

        // Passengers getting on
        bool hasUpCall = !upStops.empty() && upStops.front() == currentFloor;
        bool hasDownCall = !downStops.empty() && downStops.front() == currentFloor;
        if (hasUpCall || hasDownCall)
        {
            cout << "Time " << time << "t: Elevator stops at " << getFloorName(currentFloor) << ", passengers enter.\n";
            hasAction = true;
            if (hasUpCall)
                upStops.pop();
            if (hasDownCall)
                downStops.pop();

            // Passengers enter and press destination buttons
            for (auto &p : passengers)
            {
                if (!p.inElevator && !p.isAbandoned && p.currentFloor == currentFloor)
                {
                    p.inElevator = true;
                    pressCarButton(p.targetFloor);
                    cout << "  - Passenger enters at " << getFloorName(p.currentFloor)<< ", destination: " << getFloorName(p.targetFloor) << endl;
                }
            }
        }

        // State transitions
        if (state == GoingUp && currentFloor == FLOORS - 1)
            state = GoingDown;
        else if (state == GoingDown && currentFloor == 0)
            state = GoingUp;
        else if (state != Idle && upStops.empty() && downStops.empty() &&all_of(callCar.begin(), callCar.end(), [](bool b){ return !b; }))
        {
            state = Idle;
            idleTime = 0;
        }

        return hasAction;
    }

    // Convert floor index to name
    string getFloorName(int floor)
    {
        if (floor == 0)
            return "B1 (Basement)";
        else if (floor == BASE_FLOOR)
            return "Base Floor (1F)";
        else
            return to_string(floor) + "F";
    }
};

// Simulation class: manages passenger generation, time, and events
class Simulation
{
public:
    Elevator elevator;
    vector<Passenger> passengers;
    int time;
    default_random_engine rng;
    uniform_int_distribution<int> floorDist;
    uniform_int_distribution<int> timeDist;

    Simulation()
        : time(0), floorDist(0, 4), timeDist(10, 50)
    {
        rng.seed(static_cast<unsigned int>(::time(0)));
    }

    // Randomly generate a passenger and trigger a call
    void generatePassenger(){
    int cf = floorDist(rng);
    int tf;
    do
    {
        tf = floorDist(rng);
    } while (cf == tf);
        passengers.emplace_back(cf, tf);
        bool isUp = (tf > cf);
        elevator.pressCallButton(cf, isUp);
        cout << "Time " << time << "t: Passenger generated at " << elevator.getFloorName(cf)<< ", destination " << elevator.getFloorName(tf)<< (isUp ? " (Up)" : " (Down)") << endl;
    }

    // Check if passengers abandon after waiting too long
    void checkPassengerAbandon()
    {
        for (auto &p : passengers)
        {
            if (!p.inElevator && !p.isAbandoned)
            {
                p.waitTime++;
                if (p.waitTime > 300)
                {
                    p.isAbandoned = true;
                    cout << "Time " << time << "t: Passenger at " << elevator.getFloorName(p.currentFloor)<< " waited too long and left.\n";
                }
            }
        }
    }

    // Run the main simulation loop
    void run(int maxTime)
    {
        while (time < maxTime)
        {
            // Random passenger generation
            if (timeDist(rng) < 20)
            {
                generatePassenger();
            }

            // Idle timeout: return to base floor
            if (elevator.state == Idle)
            {
                elevator.idleTime++;
                if (elevator.idleTime > 300 && elevator.currentFloor != BASE_FLOOR)
                {
                    cout << "Time " << time << "t: Elevator idle too long, returning to "<< elevator.getFloorName(BASE_FLOOR) << endl;
                    elevator.state = (elevator.currentFloor > BASE_FLOOR) ? GoingDown : GoingUp;
                    elevator.idleTime = 0;
                }
            }

            // Elevator motion and stops
            if (elevator.state != Idle)
            {
                elevator.moveOneFloor();
                time += 1;
                bool hasStop = elevator.handleFloorStop(passengers, time);
                if (hasStop)
                {
                    cout << "Time " << time << "t: Elevator doors open.\n";
                    time += 20;
                    cout << "Time " << time << "t: Passengers enter/exit.\n";
                    time += 25;
                    cout << "Time " << time << "t: Elevator doors close.\n";
                    time += 20;
                }
            }
            else
            {
                time++;
            }

            // Check for passenger abandon
            checkPassengerAbandon();

            // Output elevator status
            cout << "Time " << time << "t: Elevator status: "<< (elevator.state == Idle ? "Idle" : (elevator.state == GoingUp ? "Going Up" : "Going Down"))<< ", current floor: " << elevator.getFloorName(elevator.currentFloor) << endl;
        }
    }
};

int main()
{
    Simulation sim;
    int maxTime;
    cout << "Enter simulation end time (500-10000): ";
    cin >> maxTime;
    sim.run(maxTime);
    return 0;
}
