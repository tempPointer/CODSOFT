#include <iostream>
#include <vector>
#include <algorithm>

class Task {
private:
    std::string description;
    bool completed;

public:
    Task(const std::string& desc) : description(desc), completed(false) {}

    const std::string& getDescription() const {
        return description;
    }

    bool isCompleted() const {
        return completed;
    }

    void markComplete() {
        completed = true;
    }

    void markIncomplete() {
        completed = false;
    }
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    void addTask(const std::string& description) {
        tasks.emplace_back(description);
    }

    void displayTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks in the to-do list." << std::endl;
        } else {
            std::cout << "To-Do List:" << std::endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << i + 1 << ". " << tasks[i].getDescription();
                if (tasks[i].isCompleted()) {
                    std::cout << " (Completed)";
                }
                std::cout << std::endl;
            }
        }
    }

    void markTaskComplete(int index) {
        if (isValidIndex(index)) {
            tasks[index - 1].markComplete();
            std::cout << "Task marked as completed: " << tasks[index - 1].getDescription() << std::endl;
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }

    void markTaskIncomplete(int index) {
        if (isValidIndex(index)) {
            tasks[index - 1].markIncomplete();
            std::cout << "Task marked as incomplete: " << tasks[index - 1].getDescription() << std::endl;
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }

    void removeTask(int index) {
        if (isValidIndex(index)) {
            tasks.erase(tasks.begin() + index - 1);
            std::cout << "Task removed successfully." << std::endl;
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }

private:
    bool isValidIndex(int index) const {
        return index > 0 && index <= static_cast<int>(tasks.size());
    }
};

int main() {
    ToDoList myToDoList;

    while (true) {
        std::cout << "\nOptions:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Mark Task as Completed\n";
        std::cout << "4. Mark Task as Incomplete\n";
        std::cout << "5. Remove Task\n";
        std::cout << "6. Exit\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string taskDescription;
                std::cout << "Enter task description: ";
                std::cin.ignore();  // Consume the newline character left in the buffer
                std::getline(std::cin, taskDescription);
                myToDoList.addTask(taskDescription);
                break;
            }
            case 2:
                myToDoList.displayTasks();
                break;
            case 3: {
                int index;
                std::cout << "Enter the task index to mark as completed: ";
                std::cin >> index;
                myToDoList.markTaskComplete(index);
                break;
            }
            case 4: {
                int index;
                std::cout << "Enter the task index to mark as incomplete: ";
                std::cin >> index;
                myToDoList.markTaskIncomplete(index);
                break;
            }
            case 5: {
                int index;
                std::cout << "Enter the task index to remove: ";
                std::cin >> index;
                myToDoList.removeTask(index);
                break;
            }
            case 6:
                std::cout << "Exiting the to-do list manager.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
