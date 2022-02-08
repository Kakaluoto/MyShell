#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#define cd_failed 0
#define cd_success 1
using namespace std;

vector<string> argv;//存储当前命令所有参数
vector<string> history_cmds(100);//存放历史命令，因为时间有限功能还未实现
string cmd;//当前命令字符串
char* current_path = nullptr;//当前工作路径

void argparse(); //解析参数
void change_directory();//cd命令
void execute_cmd();//执行命令


int main() {
    current_path = getcwd(NULL, 0);//获取当前路径
    while (1) {
        // 前置输出提示这是一个shell
        printf("myshell:%s$ ", current_path);
        getline(cin, cmd);
        // 如果输入为exit 则结束当前进程
        if (strcmp(cmd.data(), "exit") == 0) {
            delete current_path;
            return 0;
        }
        argparse();
        execute_cmd();
        argv.clear();
        // 后面在do_cmd部分会解释为什么无循环结束条件
    }
}

void argparse() {//解析输入参数
    string param;
    for (char i:cmd + " ") {//因为要用到空格进行分割，为了防止最后一个参数分割不到加一个空格
        if (i != ' ') {
            param += i;
        } else {
            argv.push_back(param);
            param = "";
            continue;
        }
    }
}

int change_directory(int argc) {//cd命令
    if (argc == 2) {
        if (chdir(argv[1].data()) == 0) {//成功返回0，失败返回-1
            current_path = getcwd(NULL, 0);
            if (current_path != nullptr) {
                return cd_success;
            } else {
                cout << "No such file or directory!\n";
                return cd_failed;
            }
        } else {
            cout << "No such file or directory!\n";
            return cd_failed;
        }
    } else {
        cout << "too many arguments!\n";
        return cd_failed;
    }
}

void execute_cmd() {
    pid_t pid;
    int argc = argv.size();
    char** arguments = new char* [argc];//转换参数类型，以便能够喂到exec函数
    for (int i = 0; i < argc; i++) {
        arguments[i] = (char*) argv[i].data();
    }
    if (strcmp(arguments[0], "cd") == 0) {
        change_directory(argc);//执行cd命令
    } else {
        switch (pid = fork()) {
            //fork子进程失败
            case -1:
                cout << "Failed to create subprocess!\n";
                return;
                //处理子进程
            case 0:
                execvp(arguments[0], arguments);
                //子进程，没有成功执行
                cout << "invalid input command : \"" << arguments[0] << "\"" << endl;
                exit(1);
            default: {
                int status;
                waitpid(pid, &status, 0);//等待子进程返回
                int err = WEXITSTATUS(status); // 读取子进程的返回码
                if (err)cout << "Error: " << strerror(err) << endl;
            }
        }
    }
}


