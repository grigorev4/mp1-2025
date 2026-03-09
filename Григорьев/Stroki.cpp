#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Movie {
	string author;
	string title;
	int year;
	double duration;
};

bool isYear(string word) {
	if (word.length() != 4) return false;
	for (int i = 0; i < 4; i++) {
		if (!isdigit(word[i])) return false;
	}
	return true;
}

bool isDuration(string word) {
	for (int i = 0; i < word.length(); i++) {
		if (word[i] == '.') return true;
	}
	return false;
}

bool isTitle(string word) {
	if (word.length() < 2) return false;
	return (word[0] == '"' && word[word.length() - 1] == '"');
}

Movie parseLine(string line) {
	Movie kino;
	kino.year = 0;
	kino.duration = 0;

	stringstream slova(line);
	string word;

	while (slova >> word) {
		if (isYear(word)) {
			kino.year = stoi(word);
		}
		else if (isDuration(word)) {
			kino.duration = stod(word);
		}
		else if (isTitle(word)) {
			kino.title = word;
		}
		else {
			kino.author = word;
		}
	}
	return kino;
}

int main() {
	vector<Movie> catalog;
	string line;

	cout << "Vvedite filmy. Dlya vyhoda nazhmite enter" << endl;
	cout << "Primer: Nolan \"Inception\" 2010 2.28" << endl;
	cout << ">";
	getline(cin, line);

	while (line != "") {
		catalog.push_back(parseLine(line));
		cout << ">";
		getline(cin, line);
	}
	cout << endl << "Vsego fiimov:" << catalog.size() << endl;

	int choice;
	do {
		cout << endl;
		cout << "MENU" << endl;
		cout << "1. Nayti filmy po avtoru" << endl;
		cout << "2. Nayti filmy po godu" << endl;
		cout << "3. Pokazat vse filymi" << endl;
		cout << "4. Filvi dlinshe 2 chasov" << endl;
		cout << "0. viyti" << endl;
		cin >> choice;
		cin.ignore();

		if (choice == 1) {
			string author;
			cout << "Vvedite avtora: ";
			getline(cin, author);

			cout << endl << "filmi " << author << ":" << endl;
			int found = 0;
			for (int i = 0; i < catalog.size(); i++) {
				if (catalog[i].author == author) {
					cout << "- " << catalog[i].title << " " << catalog[i].year << " " << catalog[i].duration << endl;
					found++;
				}
			}
			if (found == 0) {
				cout << "Net filmov" << endl;
			}
			else {
				cout << "Naideno filmov: " << found << endl;
			}
		}
		else if (choice == 2) {
			int year;
			cout << "Vvedite god: ";
			cin >> year;
			cin.ignore();

			cout << endl << "Filmy " << year << " goda:" << endl;
			int found = 0;
			for (int i = 0; i < catalog.size(); i++) {
				if (catalog[i].year == year) {
					cout << "- " << catalog[i].title << " " << catalog[i].author << " " << catalog[i].duration << endl;
					found++;
				}
			}
			if (found == 0) {
				cout << "Net filmov" << endl;
			}
			else {
				cout << "Naideno filmov: " << found << endl;
			}
		}
		else if (choice == 3) {
			cout << endl << "Vse filmy:" << endl;
			for (int i = 0; i < catalog.size(); i++) {
				cout << i + 1 << ". " << catalog[i].title << " "
					<< catalog[i].author << " " << catalog[i].year
					<< " " << catalog[i].duration << endl;
			}
		}
		else if (choice == 4) {
			int count = 0;
			for (int i = 0; i < catalog.size(); i++) {
				if (catalog[i].duration > 2) {
					count++;
				}
			}
			cout << endl << "Filmov dlitelnostyu bolee 2 chasov: " << count << endl;
		}

	} while (choice != 0);

	return 0;
}