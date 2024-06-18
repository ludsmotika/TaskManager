#include <iostream>
#include "Session.h"
#include "ProgramEngine.h"

int main()
{
    Session& session = Session::getInstance();
    session.init("users.dat", "tasks.dat", "collaborations.dat");
    ProgramEngine::run(session);
}