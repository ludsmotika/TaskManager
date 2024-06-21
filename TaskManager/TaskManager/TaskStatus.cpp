#include "TaskStatus.h"

std::ostream& operator<<(std::ostream& os, TaskStatus status) {
    switch (status) {
    case TaskStatus::ON_HOLD:
        os << "ON_HOLD";
        break;
    case TaskStatus::IN_PROCESS:
        os << "IN_PROCESS";
        break;
    case TaskStatus::DONE:
        os << "DONE";
        break;
    case TaskStatus::OVERDUE:
        os << "OVERDUE";
        break;
    }
    return os;
}