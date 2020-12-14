#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,         // новая
  IN_PROGRESS, // в разработке
  TESTING,     // на тестировании
  DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

constexpr TaskStatus NextTaskStatus(TaskStatus s) {
  switch (s) {
  case TaskStatus::NEW:
    return TaskStatus::IN_PROGRESS;
  case TaskStatus::IN_PROGRESS:
    return TaskStatus::TESTING;
  case TaskStatus::TESTING:
  case TaskStatus::DONE:
  default:
    return TaskStatus::DONE;
  }
}

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo &GetPersonTasksInfo(const std::string &person) const {
    return tasks_.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const std::string &person) {
    tasks_[person][TaskStatus::NEW]++;
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string &person,
                                                      int task_count);

private:
  std::map<std::string, TasksInfo> tasks_;
};

std::tuple<TasksInfo, TasksInfo>
TeamTasks::PerformPersonTasks(const std::string &person, int task_count) {
  const auto it = tasks_.find(person);
  if (it == tasks_.end())
    return {{}, {}};

  TasksInfo tasks, updated, untouched;
  for (const auto &[status, value] : it->second) {
    // NOTE(udalovmax): я более чем уверен, что можно сделать что-то такое:
    // const int diff = std::min(std::max(task_count, 0), value);
    // task_count = task_count > diff ? task_count - diff : 0;

    // tasks[NextTaskStatus(status)] += diff;
    // tasks[status] -= std::max(diff, 0);

    // diff > 0 ? updated[NextTaskStatus(status)] += diff
    //          : untouched[status] += value;
    //
    // но я слишком хочу спать, чтобы думать о том, как переписать этот цикл
    // таким образом, чтобы не итерироваться по value, а победить просто
    // арифметикой.
    switch (status) {
    case TaskStatus::NEW:
    case TaskStatus::IN_PROGRESS:
    case TaskStatus::TESTING: {
      int nv = value;
      while (nv > 0 && task_count > 0) {
        tasks[NextTaskStatus(status)]++;
        updated[NextTaskStatus(status)]++;
        nv--;
        task_count--;
      }
      if (nv > 0) {
        tasks[status] += nv;
        untouched[status] += nv;
      }
      break;
    }
    case TaskStatus::DONE:
    default:
      if (value > 0) {
        tasks[status] += value;
      }
      break;
    }
  }

  tasks_[person] = tasks;
  return {updated, untouched};
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  std::cout << tasks_info[TaskStatus::NEW] << " new tasks"
            << ", " << tasks_info[TaskStatus::IN_PROGRESS]
            << " tasks in progress"
            << ", " << tasks_info[TaskStatus::TESTING]
            << " tasks are being tested"
            << ", " << tasks_info[TaskStatus::DONE] << " tasks are done"
            << std::endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }

  std::cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));

  std::cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  std::tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  std::cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);

  std::cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  std::tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  std::cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);

  std::cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
