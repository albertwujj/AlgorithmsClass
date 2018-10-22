//
//  Scheduler.hpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/21/18.
//

#ifndef Scheduler_hpp
#define Scheduler_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <unordered_map>


using std::string;
using std::cout;
using std::vector;
using std::endl;
using std::istringstream;

struct Job {
    string desc;
    int id;
    int num_proc;
    int num_ticks;
};

struct Job_Comp {
    bool operator()(const Job &lhs, const Job &rhs) const
    {
        //break ties by id (lowest first)
        if (lhs.num_ticks == rhs.num_ticks) {
            return lhs.id > rhs.id;
        }
        return lhs.num_ticks > rhs.num_ticks;
    }
};

#endif /* Scheduler_hpp */

class Scheduler {
public:
    Scheduler(int processors);
    void tick(bool test, string job_string);
    bool done();

private:
    Job insertJob(string desc, int id, int num_proc, int num_tick);
    vector<Job> assignJobs();
    Job findShortest();
    void deleteShortest();
    bool checkAvailability(int pi);
    void runJob(Job & job);
    vector<Job> releaseProcs();
    void printJob(Job job);
    void decrementTimer();

    int p;
    int curr_p;
    int time_id;
    int job_id;

    vector<Job> jobq;
    std::unordered_map<int, vector<Job>> running_jobs;
};
