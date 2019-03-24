#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

int char2int(char input){
	if(input >= '0' && input <= '9')
		return input - '0';
	if(input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if(input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	return -1;
}

void hex2bin(const char* src, char* target){
	while(*src && src[1]){
		*(target++) = char2int(*src)*16 + char2int(src[1]);
		src += 2;
	}
}

bool mct2binary(const std::string& inputFile, const std::string& outputFile){
	std::ifstream in(inputFile.c_str());
	std::ofstream out(outputFile.c_str(), std::ios::binary);
	if(in && out){
		std::string line;
		char buffer[16];
		while(!in.eof()){
			std::getline(in, line);
			if(line[0]!='+'){
				hex2bin(line.c_str(), buffer);
				out.write(buffer, 16);
			}
		}
		return true;
	}
	return false;
}

bool binary2mct(const std::string& inputFile, const std::string& outputFile){
	std::ifstream in(inputFile.c_str(), std::ios::binary);
	std::ofstream out(outputFile.c_str());
	if(in && out){
		char buffer[16];
		for(int i=0 ; i<16 ; i++){
			out << "+Sector: " << std::dec << i << std::endl;
			for(int j=0 ; j<4 ; j++){
				in.read(buffer, 16);
				for(int k=0 ; k<16 ; k++){
			    	out << std::setfill('0') << std::setw(2) << std::hex << (int) (unsigned char) buffer[k];
				}
				out << std::endl;
			}
		}
		return true;
	}
	return false;
}

std::map<std::string, std::string> getArgs(int argc, char* argv[]){
	std::map<std::string, std::string> args;
	for(int i=1 ; i<argc ; i++){
		if(i+1<argc && argv[i+1][0]!='-'){
			args[argv[i]] = argv[i+1];
		} else{
			args[argv[i]] = "";
		}
	}
	return args;
}

bool has(const std::map<std::string, std::string>& args, const std::string& flag){
	return args.find(flag) != args.end();
}

void printHelp(){
	printf("PARAMETERS :\n");
	printf("\t-f :\tfile to convert\n");
	printf("\t-bin :\tconvert to binary format (libnfc)\n");
	printf("\t-mct :\tconvert to Mifare Classic Tool format (Android App)\n");
	printf("OPTIONS :\n");
	printf("\t-o :\toutput file - default to ($input)_{bin|mct}\n");
}

int main(int argc, char* argv[]){
	std::map<std::string, std::string> args = getArgs(argc, argv);
	if(has(args, "-f") && has(args, "-bin")){
		std::string inputFile = args["-f"];
		std::string outputFile = has(args, "-o") ? args["-o"] : inputFile+"_bin";
		bool done = mct2binary(inputFile, outputFile);
		printf("%s\n", done ? "Success." : "Error. Could not read input file.");
	}
	else if(has(args, "-f") && has(args, "-mct")){
		std::string inputFile = args["-f"];
		std::string outputFile = has(args, "-o") ? args["-o"] : inputFile+"_mct";
		bool done = binary2mct(inputFile, outputFile);
		printf("%s\n", done ? "Success." : "Error. Could not read input file.");
	}
	else{
		printHelp();
	}
}