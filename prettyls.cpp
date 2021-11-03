// Program to print "ls" output in a pretty format

#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  char *argv[3];
  int pipefd[2];
  string s;

  argv[0] = "ls";
  argv[1] = "-l";
  argv[2] = 0;

  pipe(pipefd);

  int a = fork();

  if (a == 0) { // Child
    close(pipefd[0]);
    close(1);
    dup(pipefd[1]);
    execvp("ls", argv);
    cout << "That was not fun!!!" << endl;
  } else { // Parent
    close(pipefd[1]);
    close(0);
    dup(pipefd[0]);
    while (getline(cin, s))
      cout << " *** " << s << " xxx " << endl;
    cout << "That was fun!!!" << endl;
  }
}