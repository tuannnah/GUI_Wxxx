#include "RandWExcel.h"
CSVWriter::CSVWriter() {
    firstC = new Cookie;
}
CSVWriter::~CSVWriter() {
}
void CSVWriter::writeEx(string a, string* fileDir) {
    // current date/time based on current system
    time_t now = time(0);
   // tm* ltm = gmtime(&now);
    // convert now to string form
    std::stringstream ss1;
   // ss1 << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year;
    std::string ts1 = ss1.str();
    //
	ofstream MyExcelFile2;
	MyExcelFile2.open(*fileDir + "\\" + ts1 + ".csv", ios::app);
    std::stringstream ss2;
   // ss2 <<ltm->tm_sec << "," << ltm->tm_min << "," << ltm->tm_hour + 7 ;
    std::string ts2 = ss2.str();
	MyExcelFile2 << ts2 << "," << a << endl;
	MyExcelFile2.close();
}
void CSVWriter::writeText(string fileName, string* fileDir, string Note) {
    // current date/time based on current system
    ofstream textFile;
    textFile.open(*fileDir + "\\" + fileName + ".txt", ios::trunc);
    textFile << Note << endl;
    textFile.close();
}
void CSVWriter::writeAllDays(string* fileDir) {
    // current date/time based on current system
    time_t now = time(0);
    //tm* ltm = gmtime(&now);
    // convert now to string form
    std::stringstream ss;
    //ss << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year;
    std::string ts = ss.str();
    ofstream iTextFile;
    iTextFile.open(*fileDir + "\\" + "allDays.txt", ios::app);
    ifstream oTextFile;
    oTextFile.open(*fileDir + "\\" + "allDays.txt", ios::in);
    vector<std::string> vectorStr;
    if (oTextFile.is_open()) { //checking whether the file is open
        string tp;
        while (getline(oTextFile, tp)) {
            vectorStr.push_back(tp);
        }
        oTextFile.close();
    }
    bool checkExist = false;
    for (unsigned int i = 0; i < vectorStr.size(); i++) {
        if (vectorStr[i] == ts) checkExist = true;
    }
    if (checkExist == false) {
        iTextFile << ts << endl;
    }
    iTextFile.close();
}

void CSVWriter::writeCookie(string content, TypeC type) {
    // current date/time based on current system
    
    ifstream CookieTextFileR;
    CookieTextFileR.open("Cookie.txt", ios::in);

    if (CookieTextFileR.is_open()) {
        std::vector<std::vector<std::string> > dataList;
        std::string line = "";
        // Iterate through each line and split the content using delimeter
        while (getline(CookieTextFileR, line))
        {
            std::vector<std::string> vec;
            std::string word = "";
            stringstream s(line);
            while (getline(s, word, ',')) {
                vec.push_back(word);
            }
            if (sizeof(vec) > 0) {
                firstC->portName = vec[0];
                firstC->FileDir = vec[1];
                firstC->saveCycle = vec[2];

            }
        }
        // Close the File
    }
    CookieTextFileR.close();
    ofstream CookieTextFileW;
    CookieTextFileW.open("Cookie.txt", ios::trunc);
    if (CookieTextFileW.is_open()) {
        switch (type)
        {
        case TypeC::FILE_DIR: {
            firstC->FileDir = content;
            CookieTextFileW << firstC->portName << "," << firstC->FileDir << "," << firstC->saveCycle << endl;
            break;
            }
        case TypeC::PORT_NAME: {
            firstC->portName = content;
            CookieTextFileW << firstC->portName << "," << firstC->FileDir << "," << firstC->saveCycle << endl;
            break;
            }
        case TypeC::SAVE_INTERVAL: {
            firstC->saveCycle = content;
            CookieTextFileW << firstC->portName << "," << firstC->FileDir << "," << firstC->saveCycle << endl;
            break;
        }
        default:
            break;
        }
        CookieTextFileW.close();
    }
}




/***********************************Reader***************************************/
/* Parses through csv file line by line and returns the data
* in vector of vector of strings.*/

string CSVReader::Time() {
    // current date/time based on current system
    time_t now = time(0);
    //tm* ltm = gmtime(&now);
    // convert now to string form
    std::stringstream ss;
    //ss << ltm->tm_mday << "-" << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year;
    std::string ts = ss.str();
    return ts;
}
std::vector<std::vector<std::string> > CSVReader::readEx(string filename, string* filePath)
{

    std::ifstream file(*filePath + "\\" + filename + ".csv", ios::in);
    std::vector<std::vector<std::string> > dataList;
    std::string line = "";
    
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        std::vector<std::string> vec;
        std::string word = "";
        stringstream s(line);
        while (getline(s, word, ',')){
            vec.push_back(word);
        }
        dataList.push_back(vec);
    }
    // Close the File
    file.close();
    return dataList;
}
std::vector<std::string> CSVReader::readText(string fileName, string* fileDir) {
    // current date/time based on current system
    ifstream textFile;
    textFile.open(*fileDir + "\\" + fileName + ".txt", ios::app);
    if (textFile.is_open()) { //checking whether the file is open
        string tp;
        vector<std::string> vectorStr;
        while (getline(textFile, tp)) {
            vectorStr.push_back(tp);
        }
        return vectorStr;
    }
    textFile.close();
}
std::vector<std::string> CSVReader::readAllDays(string* fileDir) {
    // current date/time based on current system
    ifstream textFile;
    vector<std::string> vectorStr;
    textFile.open(*fileDir + "\\" + "allDays.txt", ios::app);
    if (textFile.is_open()) { //checking whether the file is open
        string tp;
        while (getline(textFile, tp)) {
            vectorStr.push_back(tp);
        }
        return vectorStr;
    }
    textFile.close();
    return vectorStr;
}

Cookie CSVReader::readCookie() {
    ifstream CookieTextFileR;
    Cookie firstC;
    CookieTextFileR.open("Cookie.txt", ios::app);
    if (CookieTextFileR.is_open()) { //checking whether the file is open
        std::string line = "";
        while (getline(CookieTextFileR, line))
        {
            std::vector<std::string> vec;
            std::string word = "";
            stringstream s(line);
            while (getline(s, word, ',')) {
                vec.push_back(word);
            }
            if (sizeof(vec) > 0) {
                firstC.portName = vec[0];
                firstC.FileDir = vec[1];
                firstC.saveCycle = vec[2];
            }
        }
        CookieTextFileR.close();
    }
    return firstC;
}