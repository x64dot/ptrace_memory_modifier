#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/ptrace.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 4){
        cout << "Usage: " << argv[0] << " <process_id> <memory_address> <value>\n";
        return -1;
    }

    pid_t process_id = atoi(argv[1]);
    uintptr_t memory_address = strtol(argv[2], NULL, 16);
    long value = strtol(argv[3], NULL, 10);

    long ps1 = ptrace(PTRACE_ATTACH, process_id, NULL, NULL);

    if (ps1 == -1){
        cout << "[!] Couldn't attach to the process.\n";
        return -1;
    }

    cout << "[+] Attached to the process!\n";

    waitpid(process_id, NULL, 0);

    long ps2 = ptrace(PTRACE_POKEDATA, process_id, (void*)memory_address, (void*)value);

    if (ps2 == -1){
        cout << "[!] Couldnt modify value!\n";
        ptrace(PTRACE_DETACH, process_id, NULL, NULL);
        return -1;
    }

    cout << "[+] Value Modified!\n";

    ptrace(PTRACE_DETACH, process_id, NULL, NULL);

    return 0;
}
