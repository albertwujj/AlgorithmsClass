//
//  Scheduler.cpp
//  DSA_Xcode
//
//  Created by Albert Wu on 10/21/18.
//

#include "Scheduler.hpp"

Scheduler::Scheduler(int processors) {
    this->p = processors;
    this->curr_p = processors;

    this->time_id = 0;
    this->job_id = 1;
    std::make_heap(jobq.begin(),jobq.end(), Job_Comp());
}

void Scheduler::tick(bool test, string job_string) {
    cout << "Tick " << time_id << endl;
    //print available processors at start of tick
    cout << "Available processors: " << curr_p << endl;

    if(!test) {
        cout << "Enter a job please\n";
        getline(std::cin, job_string);
    }
    bool has_new_job = !(job_string == "");
    if (has_new_job) {
        //parse string into new job, insert
        string desc;
        int num_proc;
        int num_ticks;
        istringstream iss(job_string);
        iss >> desc >> num_proc >> num_ticks;
        if(desc == "exit") {
            std::exit(0);
        }
        Job new_job = this->insertJob(desc, job_id, num_proc, num_ticks);
        this->job_id++;
        cout << "New Job: ";
        printJob(new_job);
        cout << endl;
    }
    vector<Job> jobs_r = this->releaseProcs(); //jobs released this tick
    vector<Job> jobs_a = this->assignJobs(); //jobs assigned this tick

    //print any assigned jobs this tick
    if (!jobs_a.empty()) {
        cout << "Jobs Assigned: ";
        for (std::vector<Job>::iterator i = jobs_a.begin(); i != jobs_a.end(); i++) {
            printJob(*i);
        }
        cout << endl;
    } else {
        if (!jobq.empty()) {
            cout << "Not enough processors to assign: ";
            printJob(findShortest());
            cout << endl;
        }
    }
    //print any released jobs this tick
    if (!jobs_r.empty()) {
        cout << "Jobs Released: ";
        for (std::vector<Job>::iterator i = jobs_r.begin(); i != jobs_r.end(); i++) {
            printJob(*i);
        }
    }
    cout << endl << endl;
    this->decrementTimer();
}

Job Scheduler::insertJob(string desc, int id, int num_proc, int num_ticks) {
    if (num_proc > this->p) {
        throw std::invalid_argument( "num_proc greater than p");
    }
    if (num_proc <= 0) {
        throw std::invalid_argument( "num_proc <= 0");
    }
    if (num_ticks <= 0) {
        throw std::invalid_argument( "num_ticks <= 0");
    }

    Job job;
    job.desc = desc;
    job.id = id;
    job.num_proc = num_proc;
    job.num_ticks = num_ticks;
    this->jobq.push_back(job);  std::push_heap(this->jobq.begin(),this->jobq.end(), Job_Comp());
    return job;
}

vector<Job> Scheduler::assignJobs() {
    vector<Job> jobs_a;
    while (!jobq.empty()) {
        Job job = findShortest();
        if (!checkAvailability(job.num_proc)) {
            break;
        }
        runJob(job);
        deleteShortest();
        jobs_a.push_back(job);
    }
    return jobs_a;
}

void Scheduler::runJob(Job & job) {
    this->curr_p -= job.num_proc;
    //put running jobs into map indexed by completion time
    running_jobs[this->time_id + job.num_ticks].push_back(job);
}

Job Scheduler::findShortest() {
    return jobq.front();
}

void Scheduler::deleteShortest() {
    std::pop_heap(this->jobq.begin(),this->jobq.end(), Job_Comp());
    jobq.pop_back();
}
bool Scheduler::checkAvailability(int pi) {
    return this->curr_p >= pi;
}
void Scheduler::decrementTimer() {
    //increasing time by 1 gets us 1 closer to each job's completion time
    this->time_id++;
}

vector<Job> Scheduler::releaseProcs() {
    vector<Job> jobs_r = running_jobs[time_id]; //get all jobs completing at this time
    running_jobs.erase(time_id);
    for(vector<Job>::iterator i = jobs_r.begin(); i != jobs_r.end(); i++) {
        this->curr_p += i->num_proc;
    }
    return jobs_r;
}

void Scheduler::printJob(Job job) {
    cout << "Job ID: " << job.id << ", ";
    cout << "description: " << job.desc << ", ";
    cout << "processors: " << job.num_proc << ", ";
    cout << "ticks: " << job.num_ticks << ". ";
}

bool Scheduler::done() {
    return jobq.empty() && running_jobs.empty();
}
