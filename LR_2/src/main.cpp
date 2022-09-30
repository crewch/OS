#include <bits/stdc++.h>
#include <unistd.h>

#include "../includes/helper.h"

#define OUTPUT 0
#define INPUT 1
 
int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        std::cerr << "ERR pipe\n";
        return 1;
    }

    printf("Name of file: ");
    std::string file_name;
    if (!getline(std::cin, file_name)) {
        std::cerr << "ERR create file\n";
        return 1;
    }

    switch (auto pid = fork()) {
    case -1:
        std::cerr << "ERR fork\n";
        break;
    case 0:
        execlp("./child", std::to_string(pipefd[OUTPUT]).c_str(), std::to_string(pipefd[INPUT]).c_str(), file_name.c_str(), std::to_string(pid).c_str());
        break;
    default:
        float x;
        auto flag = true;
        char c;

        while (c != EOF) {
            std::cin >> x;

            if (flag) {
                packet_value<float> packet(x, value_info::START_OF_SEQUENCE);
                write(pipefd[INPUT], &packet, sizeof(packet));
                flag = false;
            } else {
                c = getchar();
                if (c == '\n') {
                    packet_value<float> packet(x, value_info::END_OF_SEQUENCE);
                    write(pipefd[INPUT], &packet, sizeof(packet));
                    flag = true;
                } else {
                    packet_value<float> packet(x, value_info::MIDDLE_OF_SEQUENCE);
                    write(pipefd[INPUT], &packet, sizeof(packet));
                }
            }
        }

        break;
    }

    close(pipefd[OUTPUT]);
    close(pipefd[INPUT]);
    return 0;
}