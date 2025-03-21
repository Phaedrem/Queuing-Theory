# Queuing-Theory

This simulation models a basic queuing system by simulating the arrival and departure of tasks based on Poisson-distributed interarrival and service times, representing a single-server queue. The system processes two types of events:
1.	Arrival Events: A new task arrives and enters the queue.
2.	Departure Events: A task is removed from the queue and processed by the server.
Each event is represented by an Event class, containing:
  -	time: The timestamp when the event occurs.
  -	isArrival: A boolean indicating whether the event is an arrival (true) or a departure (false).
A priority queue is used to manage events in chronological order. Event occurrences are generated based on the Poisson process using generateRandomTime. The simulation process begins with initialization: 
3.	The user inputs the arrival rate (λ), service rate (μ), and total simulation time.
4.	The first arrival event is scheduled and pushed into the priority queue.
5.	The simulation starts with currentTime set to zero.
The simulation runs a loop processing events in chronological order:
6.	Fetch the Next Event: The top event from the priority queue is retrieved, and currentTime is updated to this event's timestamp.
7.	Handling Arrivals:
  -	The task count (totalTasks) is incremented.
  -	The arrival is recorded in a queue (taskQueue).
  -	The next arrival time is scheduled.
  -	If the server is idle, a departure is scheduled.
8.	Handling Departures:
  -	The first task in taskQueue is removed.
  -	The task is counted as served (tasksServed).
  -	The waiting time is calculated (waitingTime = currentTime - arrivalTime).
  -	If tasks remain in the queue, another departure is scheduled.
The simulation continues until either:
  -	The priority queue runs out of events, or
  -	currentTime reaches simulationTime.
At the end of the simulation, key performance metrics are displayed:
  -	Total tasks arrived: The number of arrivals processed.
  -	Total tasks served: The number of completed departures.
  -	Average waiting time: The mean time tasks spent waiting in the queue.
  - Utilization: The proportion of tasks served out of total arrivals.
