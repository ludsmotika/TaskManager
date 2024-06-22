#include "User.h"
#include "Dashboard.h"
#pragma warning (disable : 4996)

User::User(MyString username, MyString password) :username(username), password(password) {}

const MyString& User::getUsername() const
{
	return this->username;
}

const MyString& User::getPassword() const
{
	return this->password;
}

const Vector<unsigned>& User::getTasksIds() const
{
	return this->tasksIds;
}

void User::setTasksIds(const Vector<unsigned>& ids)
{
	for (size_t i = 0; i < ids.size(); i++)
		tasksIds.push_back(ids[i]);
}

void User::addTaskId(unsigned id)
{
	tasksIds.push_back(id);
}

bool User::isOwnerOfTheTaskById(unsigned taskId)
{
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (taskId == tasksIds[i])
			return true;
	}

	return false;
}


unsigned User::getDashboardTasksIdsCount() const
{
	return dashboard.getTasksCount();
}

Dashboard User::getDashboard() const
{
	return this->dashboard;
}

void User::printDashboard() const
{
	if (dashboard.getTasksCount() == 0)
	{
		std::cout << "There aren't any tasks added to the dashboard!" << std::endl;
		return;
	}

	for (size_t i = 0; i < dashboard.getTasksCount(); i++)
	{
		if (!dashboard[i].expired())
			dashboard[i].lock()->print();
	}
}


void User::addTaskToDashboard(SharedPtr<Task> task)
{
	dashboard.addTask(task);
}

void User::removeTaskFromDashboardById(unsigned taskId)
{
	dashboard.removeTaskById(taskId);
}

void User::initDashboard(const TasksCollection& tasksCollection)
{
	time_t today = time(nullptr);
	tm* localTime = localtime(&today);

	int year = localTime->tm_year + 1900;
	int month = localTime->tm_mon + 1;
	int day = localTime->tm_mday;

	for (size_t i = 0; i < dashboard.getTasksCount(); i++)
	{
		if (!dashboard[i].expired())
		{
			try
			{
				TaskStatus currentTaskStatus = dashboard[i].lock()->getStatus();

				if (currentTaskStatus == TaskStatus::OVERDUE)
				{
					dashboard.removeTaskById(dashboard[i].lock()->getId());
					i--;
				}
			}
			catch (const std::exception&)
			{
				continue;
			}
		}
	}

	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		try
		{
			time_t dueDate = tasksCollection.getTaskById(tasksIds[i])->getDueDate();
			tm* localTime2 = localtime(&dueDate);

			int currentTaskYear = localTime2->tm_year + 1900;
			int currentTaskMonth = localTime2->tm_mon + 1;
			int currentTaskDay = localTime2->tm_mday;

			if (currentTaskYear == year && currentTaskMonth == month && currentTaskDay == day)
			{
				bool isTaskAlreadyInTheDashboard = false;
				for (size_t i = 0; i < dashboard.getTasksCount(); i++)
				{
					if (tasksCollection.getTaskById(tasksIds[i])->getId() == tasksIds[i])
					{
						isTaskAlreadyInTheDashboard = true;
						break;
					}
				}

				if (!isTaskAlreadyInTheDashboard)
					dashboard.addTask(tasksCollection.getTaskById(tasksIds[i]));

			}

		}
		catch (const std::exception&)
		{
			continue;
		}
	}

}

void User::removeTaskId(unsigned taskId)
{
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksIds[i] == taskId)
		{
			tasksIds.erase(i);
			break;
		}
	}
}
