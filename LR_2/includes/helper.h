#ifndef HELPER_H
#define HELPER_H

enum value_info {
    START_OF_SEQUENCE = 0,
    MIDDLE_OF_SEQUENCE,
    END_OF_SEQUENCE,
    UNREACHABLE,
};

template<typename T>
struct packet_value {
    T value;
    value_info info;

    packet_value(T value, value_info info): value{value}, info{info} {};
    packet_value() noexcept: value{0}, info{value_info::UNREACHABLE} {};
    packet_value(int fd) {
        read(fd, this, sizeof(this));
    }
};

#endif