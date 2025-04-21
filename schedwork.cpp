#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
                    DailySchedule& sched, vector<int>& workerShifts, size_t day, size_t slot);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    size_t n = avail.size();       // number of days
    size_t k = avail[0].size();    // number of workers
    sched.clear();
    // Add your code below
    sched.resize(n, vector<Worker_T>());  // Resize schedule with empty rows for each day

    vector<int> workerShifts(k, 0);       // How many shifts each worker has been assigned

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);
}

bool scheduleHelper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
                    DailySchedule& sched, vector<int>& workerShifts, size_t day, size_t slot)
{
    if (day == sched.size()) {
        return true;  // All days scheduled
    }

    size_t k = avail[0].size(); // number of workers

    for (Worker_T w = 0; w < k; ++w) {
        if (avail[day][w] && workerShifts[w] < maxShifts) {
            if (find(sched[day].begin(), sched[day].end(), w) != sched[day].end()) {
                continue;
            }

            sched[day].push_back(w);
            workerShifts[w]++;


            if (sched[day].size() == dailyNeed) {
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day + 1, 0)) {
                    return true;
                }
            } else {
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day, slot + 1)) {
                    return true;
                }
            }

            sched[day].pop_back();
            workerShifts[w]--;
        }
    }

    return false;  // No valid assignment 
}

