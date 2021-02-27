#include <iostream>
#include <vector>
#include <map>
using namespace std;

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
