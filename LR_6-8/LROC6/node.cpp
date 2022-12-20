#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

#include "zmq_f.h"


int main(int argc, char *argv[]) {
	if (argc != 2 && argc != 3) {
		std::cout << "Wrong arguments Not enough parameters!\n";
		exit(1);
	}
	int current_id = std::atoi(argv[1]);
	int child_id = -1;
	if (argc == 3) {
		child_id = std::atoi(argv[2]);
	}
	std::string adr = argv[1];

	zmq::context_t context;
	zmq::socket_t parent_socket(context, ZMQ_REP);
	connect(parent_socket, current_id);

	zmq::socket_t child_socket(context, ZMQ_REQ);
	child_socket.setsockopt(ZMQ_SNDTIMEO, 5000);
	parent_socket.setsockopt(ZMQ_SNDTIMEO, 5000);

	std::string message;

	while (1) {
		zmq::message_t message_main;
		message = receive_message(parent_socket);
		std::string recieved_message(static_cast<char*>(message_main.data()), message_main.size());
		std::istringstream request(message);
		int dest_id;
	
		request >> dest_id;

		std::string command;
		request >> command;

		if(command == "heartbeat") {
			std::string ans = std::to_string(current_id) + ":Ok; ";
			if (child_id != -1) {
				int timeout;
				request >> timeout;
				int fl = 0;
				for (int att=0; att < 4; att++) {
					send_message(child_socket, message);
					std::string repl = receive_message(child_socket);
					if (repl != "Error ......") {
						ans += repl;
						fl = 1;
						break;
					}
					sleep(timeout/1000);
				}
				if (fl == 0) {ans += "Node " + std::to_string(child_id) + " is not avail";}
			}
			send_message(parent_socket, ans);
		}
		else if (dest_id == current_id) {
			if (command == "pid") {
				send_message(parent_socket, "OK: " + 					std::to_string(getpid()));
			} else if (command == "create") {
				int new_child_id;
				request >> new_child_id;
				if (child_id != -1) {
					unbind(child_socket, child_id);
				}
				bind(child_socket, new_child_id);
				pid_t pid = fork();
				if (pid < 0) {
					perror("Can't create new process!\n");
					exit(1);
				}
				if (pid == 0) {
					execl("node", "node", std::to_string(new_child_id).c_str(), std::to_string(child_id).c_str(), NULL);
					perror("Can't create new process!\n");
					exit(1);
				}
				send_message(child_socket, std::to_string(new_child_id) + "pid");
				child_id = new_child_id;
				send_message(parent_socket, receive_message(child_socket));
			} else if (command == "remove") {
				send_message(parent_socket, "OK");
				disconnect(parent_socket, current_id);
				break;
			}
			else if (command == "exec") {
				std::string msg = "OK: ";
				std::string str;
				std::string sub;
				request >> str;
				request >> sub;
				std::vector<size_t> positions;

				size_t pos = str.find(sub, 0);
				while(pos != std::string::npos){
					positions.push_back(pos);
					pos = str.find(sub,pos+1);
				}
				if (positions.size() == 0) {
					msg = "Error: pattern is wrong";
				} else {
					for(size_t position : positions) {
						msg += std::to_string(position) + ", ";
					}
					msg[msg.length()-2] = ';';
				}
				send_message(parent_socket, msg);
			}
		} else if (child_id != -1) {
			send_message(child_socket, message);
			send_message(parent_socket, receive_message(child_socket));
			if (child_id == dest_id && command == "remove") {
				child_id = -1;
			}
		} else {
			send_message(parent_socket, "Error: node is unavailable!\n");
		}
	}
}
