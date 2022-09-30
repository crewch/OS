#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "../includes/helper.h"

#define OUTPUT 0
#define INPUT 1

int main(int argc, char const* argv[])
{
    int pipefd[2];
    pipefd[OUTPUT] = std::stoi(argv[0]);
    pipefd[INPUT] = std::stoi(argv[1]);

    int file = open(argv[2], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if (file == -1) {
        std::cerr << "ERR open file\n";
        return 1;
    }

    packet_value<float> first_packet{};

    while (true) {
        packet_value<float> packet(pipefd[OUTPUT]);
        // read(pipefd[OUTPUT], &packet, sizeof(packet));
        
        // std::cout << packet.info << std::endl;
        // std::cout << packet.value << std::endl;

        switch(packet.info) {
        case START_OF_SEQUENCE:
            first_packet = packet;
            // std::cout << "start" << std::endl;
            break;
        case MIDDLE_OF_SEQUENCE:
            if (packet.value == 0) {
                goto kill_parent_process;
            }

            first_packet.value /= packet.value;
            // std::cout << "mid" << std::endl;
            break;
        case END_OF_SEQUENCE:
            if (packet.value == 0) {
                goto kill_parent_process;
            }

            first_packet.value /= packet.value;
            std::cout << "ANS = " << first_packet.value << std::endl;

            std::string buf = std::to_string(first_packet.value) + "\n";

            write(file, buf.c_str(), strlen(buf.c_str()));

            // std::cout << "end" << std::endl;
            break;
        }


    }

    goto end;

kill_parent_process:
    kill(std::stoi(argv[3]), SIGKILL);
end:
    close(pipefd[OUTPUT]);
    close(pipefd[INPUT]);
    close(file);
    return 0;
}