#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <cstring>
using namespace std;
void worker(int id) {
    cout << "Worker " << id << " (PID: " << getpid() << ") started." << endl;
    while (true) {
        sleep(1);  //
    }
}

int main() {
    const int num_processes = 4;
    vector<pid_t> pids;

    for (int i = 0; i < num_processes; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            
            worker(i + 1);
            return 0; 
        } else if (pid > 0) {
            
            pids.push_back(pid);
            cout << "Started process " << i + 1 << " with PID " << pid << endl;
        } else {
            cerr << "Fork failed: " << strerror(errno) << endl;
            return 1;
        }
    }

    sleep(10);

    for (size_t i = 0; i < pids.size(); ++i) {
        cout << "Killing process with PID " << pids[i] << endl;
        kill(pids[i], SIGTERM);  
        waitpid(pids[i], nullptr, 0);  
        cout << "Process with PID " << pids[i] << " terminated." << endl;
    }

    return 0;
}