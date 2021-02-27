#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) {
    return PersonsTasks[person];
  }
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
    ++PersonsTasks[person][TaskStatus::NEW];
  }
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
        TasksInfo update_tasks = {{}};
        TasksInfo untouched_tasks = PersonsTasks[person];
        for (auto [key, value] : PersonsTasks[person]) {
          if (key != TaskStatus::DONE && task_count > 0) {
            int temp = task_count <= value ? task_count : value;
            update_tasks[ChangeProgress(key)] += temp;
            untouched_tasks[key] -= temp;
            task_count -= temp;
          }
        }
        DeleteZeroKey(update_tasks);
        DeleteZeroKey(untouched_tasks);
        PersonsTasks[person] = MergeMap(update_tasks, untouched_tasks);
        untouched_tasks[TaskStatus::DONE] = 0;
        DeleteZeroKey(untouched_tasks);
        return tie(update_tasks, untouched_tasks);
      }

private:
  map<string, TasksInfo> PersonsTasks;

  void DeleteZeroKey( TasksInfo& tasks_info) {
    TasksInfo result = tasks_info;
    for (auto [key, value] : result) {
      if (value == 0) {
        tasks_info.erase(key);
      }
    }
  }

  void AddMap(map<TaskStatus, int>& result, const TasksInfo& task_info) {
    for (auto [key, value]: task_info) {
      result[key] += value;
    }
  }

  map<TaskStatus, int> MergeMap(const TasksInfo& lhs, const TasksInfo& rhs) {
    map<TaskStatus, int> result;
    AddMap(result, lhs);
    AddMap(result, rhs);
    return result;
  }

  TaskStatus ChangeProgress(const TaskStatus& task_status) {
    switch (task_status){
    case TaskStatus::NEW:
      return TaskStatus::IN_PROGRESS;
      
    case TaskStatus::IN_PROGRESS:
      return TaskStatus::TESTING;
    }

    return TaskStatus::DONE;
  }
};

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  
  for (int i = 0; i < 5; i++) {
    tasks.AddNewTask("Alica");
  }
  
  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alica", 5);
  cout << "Updated Alica's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alica's tasks: ";
  PrintTasksInfo(untouched_tasks);

  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alica", 5);
  cout << "Updated Alica's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alica's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alica", 1);
  cout << "Updated Alica's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alica's tasks: ";
  PrintTasksInfo(untouched_tasks);

  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  for (int i = 0; i < 5; i++) {
    tasks.AddNewTask("Alica");
  }

  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alica", 2);
  cout << "Updated Alica's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alica's tasks: ";
  PrintTasksInfo(untouched_tasks);

  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alica", 4);
  cout << "Updated Alica's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alica's tasks: ";
  PrintTasksInfo(untouched_tasks);

  cout << "Alica's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alica"));

  return 0;
}