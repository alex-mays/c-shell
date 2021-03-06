#include "myShell.h"
#include <string.h>
#include <string>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[]){
    myShell ms;
    ms.execute();
}

void myShell::execute(){
    while(true){
        cout << greeting;
        cin >> command;

        parse_and_execute(command);
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* WaitFor(pid)                                                  *
* Waits for foreground processes...based on Rochkind's waitfor  *
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void myShell::WaitFor(int pid){
  int gotpid, status;

  while(true){
      gotpid = waitpid(pid, &status, 0);
      if(gotpid == pid) break;
  }
  cout << "Process [" << gotpid << "] Finished..." << endl;
}

void myShell::parse_and_execute(string c){
    int id = fork();
    if(id == 0){ // we are in the child process
        char* argv[10];
        argv[1] = NULL;
        argv[0] = (char*)c.c_str();
        execvp(argv[0], argv);
    }
    else{
        // Here we are in the parent
        WaitFor(id);
    }

    if(c.compare("exit") == 0){
        exit(0);
    }
    cout << "That sounds like a good idea." << endl;
}