#include "TaskStatus.h"

std::ostream& operator<<(std::ostream& os, TaskStatus status) {
    switch (status) {
    case TaskStatus::ON_HOLD:
        os << "ONHOLD";
        break;
    case TaskStatus::IN_PROCESS:
        os << "FINISHED";
        break;
    case TaskStatus::DONE:
        os << "OVERDUE";
        break;
    case TaskStatus::OVERDUE:
        os << "OVERDUE";
        break;
    }
    return os;
}