

#include <winsock.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::ifstream;
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::ofstream;

void fillList(vector<string>&, const string&);
string makeResponse(const string&, vector<string>&);
bool check(int, int, int, int);

int main(int argc, char** argv) {

	WSAData wsaData;
	
	if (WSAStartup(0x0202, &wsaData) || wsaData.wVersion != 0x0202) {
		cout << WSAGetLastError();
		return -1;
	}

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET) {
		cout << WSAGetLastError();
		return  -1;
	}
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(1026);
	sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (bind(s, (SOCKADDR*) &sa, sizeof(sa)) == SOCKET_ERROR) {
		cout << WSAGetLastError();
		return -1;
	}
	SOCKADDR_IN nsa;
	int nsaSize = sizeof(nsa);
	char request[1024];
	vector<string> text{};
	string inputFile = "input.txt";
	fillList(text, inputFile);
	int requestSize = sizeof(request);
	while (true) {
		/*for (auto it = text.begin(); it != text.end(); ++it) {
			if (sendto(s, (*it).c_str(), (*it).length() + 1, 0, (SOCKADDR*)&nsa, sizeof(nsa)) == SOCKET_ERROR) {
				cout << WSAGetLastError();
				return -1;
			}

		}*/
		if (recvfrom(s, request, requestSize, 0, (SOCKADDR*)&nsa, &nsaSize) == SOCKET_ERROR) {
			cout << WSAGetLastError();
			return -1;
		}
		/*if (string{ request } == "show") {
			string savedText{};
			for (auto it = text.begin(); it != text.end(); ++it) {
				savedText += ((*it) + '\n');
			}
			if (sendto(s, savedText.c_str(), savedText.length() + 1, 0, (SOCKADDR*)&nsa, sizeof(nsa)) == SOCKET_ERROR) {
				cout << WSAGetLastError();
				return -1;
			}
		}*/
		string response = makeResponse(string{ request }, text);
		if (sendto(s, response.c_str(), response.length() + 1, 0, (SOCKADDR*)&nsa, sizeof(nsa)) == SOCKET_ERROR) {
			cout << WSAGetLastError();
			return -1;
		}
	}
	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}

void fillList(vector<string>& text, const string& filePath){
	/*string str{};
	ifstream in(filePath);
	if (!in) {
		cout << "Can't open this file: " << filePath;
	}
	while (!in.eof()) {
		getline(in, str);
		text.push_back(str);
	}*/
	text.push_back("This is my first sockets programm.");
	text.push_back("So, I hope there would be amazing connection.");
	text.push_back("You can insert new symbols with command \"insert textRow position symbol\"");
	text.push_back("Deleting also available, format: \"delete row position\"");
	text.push_back("Replacement format: \"replace row position symbol\"");
}

string makeResponse(const string& str, vector<string>& text){
	int maxLen = 80;
	string clientRequest = str;
	int whiteSpacePosition = clientRequest.find_first_of(" ");
	string command = clientRequest.substr(0, whiteSpacePosition);
	cout << command;
	clientRequest  = clientRequest.substr(whiteSpacePosition + 1, clientRequest.size());
	string result{};
	
	if (command == "who") {
		result = "Yurii Belikov, K-26 Variant 1\n";
		return result;
	}
	else if (command == "show") {
		string savedText{};
		for (auto it = text.begin(); it != text.end(); ++it) {
			savedText += ((*it) + '\n');
		}
		return savedText;
	}
	else if (command == "insert") {
		whiteSpacePosition = clientRequest.find_first_of(" ");
		int row = stoi(clientRequest.substr(0 , whiteSpacePosition));
		clientRequest = clientRequest.substr(whiteSpacePosition + 1, clientRequest.size());
		whiteSpacePosition = clientRequest.find_first_of(" ");
		int positionAtString = stoi(clientRequest.substr(0, whiteSpacePosition));
		cout << row << positionAtString << text.size();
		if(!check(row, positionAtString, text.size(), maxLen)) return "Error: more than 5 lines is not allowed";
		clientRequest = clientRequest.substr(whiteSpacePosition + 1, clientRequest.size());
		string symbol = clientRequest;
		text[row].insert(positionAtString, symbol);
		if (text[row].size() > maxLen) return "Error: rows with length more than 50 is not allowed";
		return text[row];
	}
	else if (command == "delete") {
		whiteSpacePosition = clientRequest.find_first_of(" ");

		int linePosition = stoi(clientRequest.substr(0, whiteSpacePosition));
		clientRequest = clientRequest.substr(whiteSpacePosition + 1, clientRequest.size());
		whiteSpacePosition = clientRequest.find_first_of(" ");
		int positionAtString = stoi(clientRequest.substr(0, whiteSpacePosition));
		text[linePosition].erase(positionAtString, 1);
		return text[linePosition];
	}
	else if (command == "replace") {
		whiteSpacePosition = clientRequest.find_first_of(" ");
		int row = stoi(clientRequest.substr(0, whiteSpacePosition));
		clientRequest = clientRequest.substr(whiteSpacePosition + 1, clientRequest.size());
		whiteSpacePosition = clientRequest.find_first_of(" ");
		int positionAtString = stoi(clientRequest.substr(0, whiteSpacePosition));
		clientRequest = clientRequest.substr(whiteSpacePosition + 1, clientRequest.size());
		string symbol = clientRequest;
		text[row].replace(positionAtString, 1, symbol);
		return text[row];
	}
	return "Error: request doesn't fit any format!";
}
bool check(int row, int position, int numberOfRows, int maxLength) {
	cout << row << " " << numberOfRows;
	if (row > numberOfRows) {
		return false;
	}
	return true;
}