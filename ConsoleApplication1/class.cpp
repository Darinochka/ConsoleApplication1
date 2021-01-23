#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void add(vector <vector <string>>& work, int& q, string plan, string date) {
	int i;
	for (i = 0; i < work.size() && work[i][0] != date; i++);
	if (i < work.size()) {
		work[i].push_back(plan);
	}
	else {
		work.resize(q + 1);
		work[q].push_back(date);
		work[q].push_back(plan);
		q++;
	}
}

void sort(vector<vector<string>>& work) {
	bool key = true;
	while (key) {
		key = false;
		for (int i = 0; i < work.size()-1; i++) {
			if (stoi(work[i][0]) > stoi(work[i + 1][0])) {
				vector <string> temp = work[i];
				work[i] = work[i + 1];
				work[i + 1] = temp;
				key = true;
			}
		}
	}
	
}

int main() {
	int n, i, j, q = 0, month = 1, iter_dump = 0;
	string command, plan, date;
	bool key;
	vector <vector <string>> work;
	vector <vector <string>> plans_on_date;
	vector <int> next_30 = { 3, 5, 8, 10 };

	cin >> n;

	for (int iter = 0; iter < n; iter++) {
		cin >> command;

		if (command == "ADD") {
			cin >> date >> plan;
			add(work, q, plan, date);
		}

		if (command == "DUMP") {
			cin >> date;
			key = false;
			plans_on_date.resize(iter_dump + 1);
			for (auto plans : work) {
				if (plans[0] == date) {
					plans_on_date[iter_dump].push_back(to_string(plans.size() - 1));
					for (i = 1; i < plans.size(); i++)
						plans_on_date[iter_dump].push_back(plans[i]);
					key = true;
				}
			}
			if (!key) {
				plans_on_date[iter_dump].push_back("0");
			}
			iter_dump++;
		}

		if (command == "NEXT") {
			string last_day = "31";

			auto found = find(next_30.begin(), next_30.end(), month);
			if (month == 1)
				last_day = "28";
			else if (found != next_30.end())
				last_day = "30";

			if (work.size() != 0) {
				i = 0;
				sort(work);
				while (i < work.size()) {
					if (stoi(work[i][0]) > stoi(last_day)) {
						for (j = 1; j < work[i].size(); j++) {
							add(work, q, work[i][j], last_day);
						}
						work.erase(work.begin() + i);
						q--;
						i--;
					}
					i++;
				}
			}
			if (month == 12) {
				month = 1;
			}
			else {
				month++;
			}
		}
	}

	for (i = 0; i < plans_on_date.size(); i++) {
		for (j = 0; j < plans_on_date[i].size(); j++) {
			cout << plans_on_date[i][j] << " ";
		}
		cout << endl;
	}
}
