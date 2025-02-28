//
//  main.cpp
//  CS3360-Code5 - Queuing Theory
//
//  Created by Darren Bowers on 2/27/25, following Professor Manouchehr Mohandesi's examples.
//

#include <iostream> // For input/out
#include <queue> // for building queues
#include <cstdlib> // for random number generator (RNG)
#include <ctime> // for seeing the (RNG)
#include <cmath> // for math functions, specifically log() in this case

using std::cout; 
using std::endl;
using std::cin; 
using std::priority_queue;
using std::queue;
using std::vector;

// Function to generate random time based on Poisson distribution
double generateRandomTime(double rate){
    double r = ((double) rand() / (RAND_MAX)); // By dividing by RAND_MAX the number is guaranteed to be between 0.0 and 1.0 
    return -log(1-r) / rate;
}

// Even class to represent an arrival or departure
class Event {
public:
    double time;
    bool isArrival;

    Event(double t, bool arrival): time(t), isArrival(arrival){}
};

// Comparator for prioity queue to sort events by time - Optional: if prefering FIFO, adjust to just return e1, and create a queue in main instead
class CompareEvent{
public:
    bool operator() (Event const& e1, Event const& e2){
        return e1.time > e2.time; // Returns true/false depending on if e1.time is greater than e2. time to facilitate min-heap sort based on time
    }

};

int main(){
    srand(time(0)); // Seed the random number generator

    double arrivalRate, serviceRate,simulationTime; // Create user input parameters

    cout << "Enter the arrival rate (tasks per unit time - λ): ";
    cin >> arrivalRate;
    cout << "Enter the service rate (tasks per unit time - μ): ";
    cin >> serviceRate;
    cout << "Enter the total simulation time: ";
    cin >> simulationTime;

    double currentTime{0.0}; // Current simulation time

    priority_queue<Event, vector<Event>, CompareEvent> eventQueue; // Learning notes
    queue<double> taskQueue; // Queue for tasks waiting to be served

    double totalTasks{0.0}, totalWaitingTime{0.0}, tasksServed{0.0}; // Initialize countersdouble

    double nextArrivaltime = generateRandomTime(arrivalRate); // Initialize the first arrival event
    eventQueue.push(Event(nextArrivaltime, true));

    while (currentTime < simulationTime){ // Start the simulation
        Event currentEvent = eventQueue.top(); // Get the next event
        eventQueue.pop();
        currentTime = currentEvent.time;

        if (currentEvent.isArrival){
            cout << "Arrival at time: " << currentTime << endl; // Handled arrival event
            totalTasks++;
            taskQueue.push(currentTime);

            nextArrivaltime = currentTime +generateRandomTime(arrivalRate); // Schedule the next arrival
            if (nextArrivaltime < simulationTime){
                eventQueue.push(Event(nextArrivaltime, true));
            }

            if(taskQueue.size() == 1){ // If the server is idle, schedule a departure
                double serviceTime = generateRandomTime(serviceRate);
                eventQueue.push(Event(currentTime+serviceTime, false));
            }
        }else if(!taskQueue.empty()){
            double arrivalTime = taskQueue.front(); // Handle departure event
            taskQueue.pop();
            tasksServed++;
            double waitingTime = currentTime - arrivalTime;
            totalWaitingTime += waitingTime;

            cout << "Depature at time: " << currentTime << " (Waiting time: " << waitingTime << ")" << endl;

            if(!taskQueue.empty()) {
                double serviceTime = generateRandomTime(serviceRate);
                eventQueue.push(Event(currentTime + serviceTime, false));
            }
        }if (eventQueue.empty() && taskQueue.empty() && currentTime < simulationTime){ // Added to prevent infinite loop if both queues were emptied before simulationTime was met. 
            nextArrivaltime = currentTime +generateRandomTime(arrivalRate);
            eventQueue.push(Event(nextArrivaltime, true));
        }
    }

    cout << "\nSimulation Summary:" << endl; // Output results
    cout << "Total tasks arrived: " << totalTasks << endl;
    cout << "Tasks served: " << tasksServed << endl;
    cout << "Average waiting time: " << totalWaitingTime / tasksServed << endl;
    cout << "Utilization: " << tasksServed / totalTasks << endl;
    
    return 0;
}

