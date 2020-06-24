#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

void Logsearch(std::string path, std::string fileName, std::string device, bool& isEmpty, int i){
	std::fstream readFile; 
	readFile.open(path); 

	while (!readFile.eof()){ 
		std::string info, time, second, str, deviceName;
		int index = 0; 
		getline(readFile, str);
		if (str.length() == 0 || str.find("garbage") != -1) {
			continue;
		}
		

		for (int i = 0; i < str.length(); i++){ 
			if(str[i] == ':') {
				index = i; 
				break; 
			}
		}
		if(index == 2) {
			second = str.substr(0, index);
		} else {
			second = "0" + str.substr(0, index);
		}
		
		str.replace(0, index + 1, "");
		index = 0; 

		for (int i = 0; i < str.length(); i++){ 
			if(str[i] == ':') {
				index = i; 
				break;
			}
		}
		deviceName = str.substr(0, index); 
		if (deviceName != device) { 
			continue;
		}
		str.replace(0, index + 1, "");
		info = str;
		isEmpty = false; 
		time = fileName.substr(5, fileName.length() - 10);
		std::cout << i << " DATA | " << time << "-" << second << " | INFO | " << info << std::endl; 
	}
	readFile.close(); 
}

int main() {
	std::string path, device;
	std::cout << "Enter device name: "; getline(std::cin, device);
	std::cout << "Enter path:"; getline(std::cin, path);

	std::vector<std::string> v_pathFile;
	std::vector<std::string> v_File;
	bool isEmpty = true;
	try {
		for (auto& pointer : std::filesystem::directory_iterator(path)) { 
		auto fileName = pointer.path().filename().string(); 
		auto pathFile = pointer.path().string(); 
		v_pathFile.push_back(pathFile); 
		v_File.push_back(fileName);
		}
	}
	catch(const std::exception e) {
		std::cout << "Invalid path!" << std::endl;
		return 0;
	}

	for (int i = 0; i < v_File.size(); i++) { 
		Logsearch(v_pathFile[i], v_File[i], device, isEmpty, i);
	}

	if(isEmpty) { 
		std::cout << "Not find!" << std::endl;
	}
}
