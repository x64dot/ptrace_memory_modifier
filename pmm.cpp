#include <iostream>
#include <sys/ptrace.h>
#include <sys/wait.h>

using namespace std;


int main(){
    pid_t process_id = 0; /* Enter process_id of the running process */
    uintptr_t memory_address = 0; /* Enter the memory address of the value you want to change */
    long value = 0; /* Enter the new value */

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