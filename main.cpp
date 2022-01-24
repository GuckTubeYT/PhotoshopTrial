#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

void deleteCharStr(std::string& str, const std::string& from, bool deleteCharBefore) {
    if (deleteCharBefore) str.replace(0, from.length() + str.find(from), "");
    else str.replace(str.find(from), from.length(), "");
}

string trialNumGen(string trialNum) {
	string strNum = "0123456789";
	srand(time(0));
	trialNum[(rand() % 10) + 1] = strNum[(rand() % 10) + 1];
	return trialNum;
}

int main() {
	ifstream ifs("application.xml");
	string line; 
	string res;
	while (getline(ifs, line)) {
		if (line.find("TrialSerialNumber") != string::npos) {
			deleteCharStr(line, "<Data key=\"TrialSerialNumber\">", true);
			deleteCharStr(line, "</Data>", false);
			res += "        <Data key=\"TrialSerialNumber\">" + trialNumGen(line) + "</Data>\n";
		} else res += line + "\n";
	}
	ofstream ofs("application1.xml");
	ofs << res;
	ofs.close();
	ifs.close();
	return 0;
}
