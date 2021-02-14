#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
    string current_time = "00:02:34";
    bool key = true;
    bool flag = false;
    if (!key) {
        throw system_error(error_code());
    } else if (!flag) {
        throw exception();
    } else {
        return current_time;
    }
}

class TimeServer {
public:
    string GetCurrentTime() {
        try {
            last_fetched_time = AskTimeServer();
            return last_fetched_time;
        } catch (system_error&) {
            return last_fetched_time;
        }  
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
