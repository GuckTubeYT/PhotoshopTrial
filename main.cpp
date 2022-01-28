#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <string>

bool isOpen = false;
using namespace std;

void deleteCharStr(std::string& str, const std::string& from, bool deleteCharBefore) {
    if (deleteCharBefore) str.replace(0, from.length() + str.find(from), "");
    else str.replace(str.find(from), from.length(), "");
}

string trialNumGen(string trialNum) {
	string strNum = "0123456789";
	srand(time(0));
	trialNum[(rand() % 25) + 5] = strNum[(rand() % 10) + 1];
	return trialNum;
}

void resGen(string nameFile) {
	ifstream ifs(nameFile);
	if (ifs) {
		string line;
		string res;
		while (getline(ifs, line)) {
			if (line.find("TrialSerialNumber") != string::npos) {
				deleteCharStr(line, "<Data key=\"TrialSerialNumber\">", true);
				deleteCharStr(line, "</Data>", false);
				res += "        <Data key=\"TrialSerialNumber\">" + trialNumGen(line) + "</Data>\n";
			} else res += line + "\n";
		}
		ifs.close();
		ofstream ofs(nameFile);
		ofs << res << endl;
		ofs.close();
	} else ifs.close();
}

int main() {
	cout << "[LOG] PhotoshopTrial (C) GuckTube YT" << endl;
	cout << "[LOG] Make sure, this application is run as administrator" << endl;
	cout << "[LOG] Otherwise this application not working properly" << endl;
	cout << "[LOG] Press any key if you run this app as administrator" << endl;
	cout << "[LOG] If you forgot run this app as administrator, please close this app, and run this app as administrator" << endl;
	system("pause > nul");
	string photoshopFolder[4] = {
		"C:\\Program Files\\Adobe\\Adobe Photoshop CS6 (64 Bit)\\AMT\\application.xml",
		"C:\\Program Files (x86)\\Adobe\\Adobe Photoshop CS6\\AMT\\application.xml",
		"C:\\Program Files\\Adobe\\Adobe Photoshop CS6 (64 Bit)\\Photoshop.exe",
		"C:\\Program Files (x86)\\Adobe\\Adobe Photoshop CS6\\Photoshop.exe"
	};
	cout << "[LOG] Killing process PDapp.exe" << endl;
	system("taskkill /f /im pdapp.exe > nul");
	cout << "[LOG] PDapp.exe has been killed\n[LOG] Disable network..." << endl;
	system("netsh interface set interface \"Ethernet\" disable > nul");
	cout << "[LOG] Network has been disabled!" << endl;
	for (int a = 0; a < 2; a++) resGen(string(photoshopFolder[a]));
	cout << "[LOG] Photoshop has been reseted to 30 days!" << endl;
	cout << "[LOG] Opening Adobe Photoshop..." << endl;
	for (int a = 2; a < 4; a++) {
		ifstream checkFile(photoshopFolder[a]);
		if (checkFile) if (!isOpen) system(("start \"\" \"" + photoshopFolder[a] + "\" /B").c_str()), isOpen = true;
	}
	cout << "[LOG] Enable network..." << endl;
	system("netsh interface set interface \"Ethernet\" enable > nul");
	cout << "[LOG] Network has been enabled!\n";
	cout << "[LOG] Press any key to close..." << endl;
	system("pause > nul");
}
