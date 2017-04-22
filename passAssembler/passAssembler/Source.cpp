#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_COUNT = 8;
const int HEX_VAL = 10;
const int HEX_BASE = 16;
const string COMMANDS[MAX_COUNT] = { "ADD", "ADDI", "SUB", "SUBI",
									    "MOVE", "ORG", "TRAP", "END" };
const string HEX_VALS = "0123456789ABCDEF";

string decHexConv(int numVal) {
	char hexString[HEX_VAL];

	_itoa_s(numVal, hexString, 16);
	return hexString;
}

string convDec2Hex(string numVal) {
	int val = atol(numVal.c_str());
	return decHexConv(val);
}

int convHex2Dec(string numVal) {
	int total = 0, val = 0;	
	int loc;
	for (int i = 0; i<numVal.size(); i++) {	
		loc = 0;
		for (int j = 0; j < HEX_VALS.size(); j++)
			if (toupper(numVal[numVal.size() - loc - 1]) == HEX_VALS[i])
				val = i;

		val = pow(HEX_BASE, loc) * val;
		total += val;
		loc++;
	}

	return total;
}

bool isCommand(string symInstruc) {
	string signCom = symInstruc;

	for (int i = 0; i < symInstruc.size(); i++)
		signCom.at(i) = toupper(signCom[i]);
	
	for (int j = 0; j < MAX_COUNT; j++)	{
		if (COMMANDS[j] == signCom)
			return true;
	}

	return false;
}

void spaceHexNum(string* numVal) {
	int val = 0;
	for (int i = 0; i < numVal->size(); i++)
	{
		if (val % 4 == 0 && val > 0)
		{
			numVal->insert(i, " ");
			val = 0;
		}
		else
			val++;
	}
}

void fillHexNum(string* numVal, int numMem) {

	for (int i = numVal->size(); i < numMem; i++)
		*numVal = "0" + *numVal;
}

class hexNumLibr {

	public:
		void setHex(string val) {
			hexVal = val;
			sDigit = val.size();
		}

		char revertHex(int decVal) {
			if (decVal == 0) 
				return '0';			
			else if (decVal == 1) 
				return '1';			
			else if (decVal == 2) 
				return '2';			
			else if (decVal == 3) 
				return '3';			
			else if (decVal == 4) 
				return '4';			
			else if (decVal == 5) 
				return '5';			
			else if (decVal == 6) 
				return '6';			
			else if (decVal == 7) 
				return '7';			
			else if (decVal == 8) 
				return '8';			
			else if (decVal == 9) 
				return '9';			
			else if (decVal == 10) 
				return 'A';			
			else if (decVal == 11) 
				return 'B';			
			else if (decVal == 12) 
				return 'C';			
			else if (decVal == 13) 
				return 'D';			
			else if (decVal == 14) 
				return 'E';			
			else if (decVal == 15)
				return 'F';
			else
				return 'x';
		}

		int convertDecimal(char decVal) {
			if (decVal == '0')
				return 0;
			else if (decVal == '1')
				return 1;
			else if (decVal == '2')
				return 2;
			else if (decVal == '3')
				return 3;
			else if (decVal == '4')
				return 4;
			else if (decVal == '5')
				return 5;
			else if (decVal == '6')
				return 6;
			else if (decVal == '7')
				return 7;
			else if (decVal == '8')
				return 8;
			else if (decVal == '9')
				return 9;
			else if (decVal == 'A')
				return 10;
			else if (decVal == 'B')
				return 11;
			else if (decVal == 'C')
				return 12;
			else if (decVal == 'D')
				return 13;
			else if (decVal == 'E')
				return 14;
			else if (decVal == 'F')
				return 15;
			else
				return 0;
		}

		string addHex(hexNumLibr hexNum) {
			int val = sDigit - 1;
			int carry = 0, sum;
			char val1, val2;
			for (int i = hexNum.sDigit - 1; i != -1; i--) {
				val1 = hexVal[val];
				val2 = hexNum.hexVal[i];		

				int sum;
				sum = convertDecimal(val1) + convertDecimal(val2) + carry;
				if (sum >= 16) {
					carry = 1;
					sum = sum - 16;
				}
				else
					carry = 0;

				hexVal[val] = revertHex(sum);
				val--;
			}
			sum = 0;
			while (carry > 0)	{
				if (val == -1)	{
					hexVal.insert(hexVal.begin(), revertHex(1));
					sDigit = sDigit + 1;
					val++;
					carry = 0;
				}
				val1 = hexVal[val];
				sum = convertDecimal(val1) + carry;
				if (sum >= 16) {
					carry = 1;
					sum -= 16;
					hexVal[val] = revertHex(sum);
					if (val == 0 && carry == 1) 	{
						hexVal.insert(hexVal.begin(), revertHex(1));
						sDigit = sDigit + 1;
						val++;
						carry = 0;
					}
					val--;
				}
				else {
					carry = 0;
					hexVal[val] = revertHex(sum);
					val--;
				}
			}
			return hexVal;
		}

		string getHex() {
			return hexVal;
		}	

private:
	string hexVal;
	int sDigit;	
};

string clearSpaces(string fixStr) {
	stringstream getString;
	string newString;

	getString << fixStr;
	getString >> newString;
	getString.flush();

	return newString;
}

class hexTable
{
	struct SymbolEn
	{
		string token;
		string memLoc;

	};

private:
	vector<SymbolEn> hexTable;

public:
	string findEntry(string numVal) {
		for (string::size_type i = 0; i<hexTable.size(); i++) {
			if (hexTable[i].token == numVal)
				return hexTable[i].memLoc;
		}
	}

	void addEntry(string x, string y) {

	}

	int getSize() {
		return hexTable.size();
	}

	string getSymbol(int val) {
		return hexTable[val].token;
	}

	string getAddress(int val) {
		return hexTable[val].memLoc;
	}
};

class TwoAssembler {
	
	public:
		void inputDataItems() {

			fstream fin;
			fin.open("dataFile.txt");
			cout << "Collecting Data from Data.txt" << endl;

			if (fin)
			{
				string TestString;

				while (fin)
				{
					getline(fin, TestString);
					macLine.push_back(TestString);


				}
			}
			else
				cout << "Could not read the file";

			string lastAddress;
			entryTemp.memLoc = "";
			entryTemp.macOper = "";
			entryTemp.oper = "";
			entryTemp.comMand = "";

			for (string::size_type i = 0; i<macLine.size() - 1; i++)
			{

				entryTemp.memLoc = "";
				entryTemp.macOper = "";
				entryTemp.oper = "";
				entryTemp.comMand = "";

				if (isLabel(i))
				{
					string wString = macLine[i].substr(10, 10);
					wString = clearSpaces(wString);
					if (wString == "ORG") {
						entryTemp.memLoc = wString.substr(5, 3);
						lastAddress = entryTemp.memLoc;
					}
					else {
						string Label;
						Label = macLine[i].substr(0, 10);
						Label = clearSpaces(Label);
						symTable.addEntry(Label, lastAddress);
						string machineCode = getCommand(i);

						if (machineCode == "END")
							break;

						entryTemp.macOper = machineCode;
						entryTemp.memLoc = lastAddress;

						int resolveAddress = getLocation(machineCode);

						hexNumLibr addressHex, incrementHex;
						char temp = incrementHex.revertHex(resolveAddress);
						string toSetIncrement;

						toSetIncrement.push_back(temp);
						addressHex.setHex(lastAddress);
						incrementHex.setHex(toSetIncrement);
						addressHex.addHex(incrementHex);
						lastAddress = addressHex.getHex();
						outputEnt.push_back(entryTemp);
					}
				}
				else {
					string wString = macLine[i].substr(10, 10);
					wString = clearSpaces(wString);
					if (wString == "ORG")
					{
						entryTemp.memLoc = macLine[i].substr(21, 3);
						lastAddress = entryTemp.memLoc;
					}
					else {
						string machineCode = getCommand(i);

						if (machineCode == "END")
							break;

						entryTemp.macOper = machineCode;
						entryTemp.memLoc = lastAddress;

						int resolveAddress = getLocation(machineCode);
						hexNumLibr addressHex, incrementHex;
						char temp = incrementHex.revertHex(resolveAddress);
						string toSetIncrement;

						toSetIncrement.push_back(temp);
						addressHex.setHex(lastAddress);
						incrementHex.setHex(toSetIncrement);
						addressHex.addHex(incrementHex);
						lastAddress = addressHex.getHex();
						outputEnt.push_back(entryTemp);
					}

				}
			}
		}

		void operTable() {
			
		}

		void printLines() {
			ofstream fout("dataOUt.txt");

			cout << "Inputting Data to Output.txt" << endl;
			fout << "******************************************************************************" << endl;
			fout << "Input Data:" << endl;

			for (string::size_type i = 0; i< macLine.size() - 1; i++)
				fout << macLine[i] << endl;

			fout << "******************************************************************************" << endl << endl;
			fout << "Output Data:" << endl;

			fout << "Address" << "\t\t\t" << "Machine Code" << "\t\t\t" << "Operands"
				<< "\t\t\t" << "Instructions" << endl;

			for (string::size_type i = 0; i <outputEnt.size(); i++) {
				fout << outputEnt[i].memLoc << "\\t\t\t" << outputEnt[i].macOper
					<< "\t\t\t" << outputEnt[i].oper << "\t\t\t" << outputEnt[i].comMand
					<< endl;
			}

			fout << endl << endl << endl;
			fout << "Symbol" << "\t\t" << "Address" << endl;

			for (int i = 0; i< symTable.getSize() - 1; i++)
				fout << symTable.getSymbol(i) << "      " << symTable.getAddress(i) << endl;

			fout << "******************************************************************************" << endl;
		}

	private:
		struct OutlineEntry {
			string memLoc, macOper;
			string oper, comMand;
		};

		vector<string> macLine;
		vector<OutlineEntry> outputEnt;
		OutlineEntry entryTemp;

		bool isLabel(int val);
		string getCommand(int val);
		int getLocation(string machineCode);
		hexTable symTable;
};

class passAssem {
public:
	passAssem() {
		comment = "", instruction = "";
		rightOper = "", leftOper = "";
		lineName = "";
	}

	void setComment(string cmt) {
		this->comment = comment + " " + cmt;
	}

	void setInstruction(string instruc) {
		this->instruction = instruc;
	}

	void setLineName(string ln) {
		this->lineName = ln;
	}

	void setOper(string oper) {
		string::size_type posVal = oper.find(",", 0); 
		if (posVal == string::npos) {
			leftOper = oper;
		}
		else {
			rightOper = oper.substr(posVal + 1, oper.size() - posVal + 1);
			leftOper = oper.substr(0, posVal);
		}
	}

	string computeDecHex(string curLoc, vector<string>& codeItems,
		           vector<string>& symTable) {
		string strAddress, strCom = instruction, valLeftOper;
		string valRightOper, valOper;
		
		fillHexNum(&curLoc, 4);

		if (lineName != "") {
			spaceHexNum(&curLoc);
			strAddress = lineName + "\t" + curLoc;
			symTable.push_back(strAddress);
		}
		
		for (int i = 0; i < strCom.size(); i++)
			strCom.push_back(toupper(strCom[i]));

		int val = convHex2Dec(curLoc);

		if (strCom == "ADD") {
			if (leftOper.at(0) == '$') {
				valLeftOper = leftOper.substr(1, leftOper.size() - 1);
				fillHexNum(&valLeftOper, 4);
				spaceHexNum(&valLeftOper);
				valLeftOper = "d079 " + valLeftOper;
				codeItems.push_back(valLeftOper);
				return decHexConv(val + 6);
			}
			else {
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valRightOper = "d179 " + valRightOper;
				codeItems.push_back(valRightOper);
				return decHexConv(val + 6);
			}
		}
		else if (strCom == "ADDI") {
			if (leftOper.at(0) == '#' && rightOper.at(0) != '$') {
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valOper = "0640 " + valOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 4);
			}
			else {
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valOper = "0679 " + valOper + " " + valRightOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 8);
			}
		}
		else if (strCom == "SUB") {
			if (leftOper.at(0) == '#')
			{
				valLeftOper = leftOper.substr(1, leftOper.size() - 1);
				fillHexNum(&valLeftOper, 4);
				spaceHexNum(&valLeftOper);
				valLeftOper = "9079 " + valLeftOper;
				codeItems.push_back(valLeftOper);
				return decHexConv(val + 6);
			}
			else
			{
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valRightOper = "9179 " + valRightOper;
				codeItems.push_back(valRightOper);
				return decHexConv(val + 6);
			}
		}
		else if (strCom == "SUBI") {
			if (leftOper.at(0) == '#' && rightOper.at(0) != '$')
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valOper = "0440 " + valOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 4);
			}
			else
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valOper = "0479 " + valOper + " " + valRightOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 8);
			}
		}
		else if (strCom == "MOVE") {
			if (leftOper.at(0) == '#' && rightOper.at(0) == '$')
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valOper = "33fc " + valOper + " " + valRightOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 8);
			}
			else if (leftOper.at(0) == '#' && rightOper.at(0) != '$')
			{
				valOper = convDec2Hex(leftOper.substr(1, leftOper.size() - 1));
				fillHexNum(&valOper, 2);
				valOper = "303c " + valOper;
				codeItems.push_back(valOper);
				return decHexConv(val + 4);
			}			
			else if (leftOper.at(0) == '$') 	{
				valLeftOper = leftOper.substr(1, leftOper.size() - 1);
				fillHexNum(&valLeftOper, 4);
				spaceHexNum(&valLeftOper);
				valLeftOper = "3039 " + valLeftOper;
				codeItems.push_back(valLeftOper);
				return decHexConv(val + 6);
			}
			else {
				valRightOper = rightOper.substr(1, rightOper.size() - 1);
				fillHexNum(&valRightOper, 4);
				spaceHexNum(&valRightOper);
				valRightOper = "33c0 " + valRightOper;
				codeItems.push_back(valRightOper);
				return decHexConv(val + 6);
			}
		}
		else if (strCom == "TRAP") {
			if (leftOper == "#0")
			{
				codeItems.push_back("4e40");
				return decHexConv(val + 2);
			}
			else if (leftOper == "#1")
			{
				codeItems.push_back("4e41");
				return decHexConv(val + 2);
			}
			else if (leftOper == "#2")
			{
				codeItems.push_back("4e42");
				return decHexConv(val + 2);
			}
		}
		else if (strCom == "ORG") {
			return leftOper.substr(1, leftOper.size() - 1);
		}
		else if (strCom == "END") {
			return curLoc;
		}
	}

private:
	string comment, instruction;
	string rightOper, leftOper;
	string lineName;
};

int main() {

	ifstream infile;
	ofstream outfile;
	infile.open("dataFile.txt");
	outfile.open("outFile.txt");

	passAssem machLine;

	vector<string> codeItems, instrucTable;
	string memAddress = "0", newLine, symbol;
	int symNum, comNum;
	bool instruc = false;

	while (!infile.eof()) {
		
		getline(infile, newLine);
		symNum = 1, comNum = 5;

		for (int i = 0; i < newLine.size(); i++) {
			
			if (isspace(newLine[i]) || i == newLine.size() - 1) {
				
				if (i == newLine.size() - 1)
					symbol.append(1, newLine[i]);

				if (symbol.size() > 0) {

					if (symNum == 1 && isCommand(symbol)) {
						symNum = 3;
						instruc = true;
						cout << symbol << "\t";
						outfile << symbol << "\t";

						machLine.setInstruction(symbol);
					}
					else if (symNum == 2 && isCommand(symbol)) {
						symNum = 4;
						instruc = true;
						cout << symNum << "\t";
						outfile << symNum << "\t";
						machLine.setInstruction(symbol);
					}
					else if (instruc) {
						instruc = false;
						cout << symbol << "\t";
						outfile << symbol << "\t";
						machLine.setOper(symbol);
					}														
					else if (symNum >= comNum) {
						cout << symbol << " ";
						outfile << symbol << " ";
						machLine.setComment(symbol);
					}
					else {
						cout << symbol << "\t";
						outfile << symbol << "\t";
						machLine.setLineName(symbol);
					}
					symNum++;
				}
				else {
					cout << "\t";
					outfile << "\t";
				}
				symbol = "";
			}
			else {
				symbol.append(1, newLine[i]);
			}
		}
			memAddress = machLine.computeDecHex(memAddress, codeItems, instrucTable);
			cout << endl;
		}
	
	return 0;
}