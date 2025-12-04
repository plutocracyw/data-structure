/*
输入：英文小说文本文件 + 待统计词汇集合

处理：统计每个词的出现次数和位置

输出：次数 + 行号列表

技术要求：基于KMP算法，一次运行完成统计
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>
#include <set>
#include <fstream>

/*
数据结构选择：
map<string, pair<int, set<int>>>：核心数据结构，存储单词→(次数, 行号集合)

vector<string>：存储文本行和目标词汇

set<int>：自动去重行号
*/

using namespace std;

vector<int> computeNext(const string& pattern){
    int m=pattern.size();  //模式串长度
    vector<int> next(m,0);  // next数组初始化
    next[0] = -1;

    int i = 0;
    int j = -1;

    // 构建next数组
    while (i < m - 1) {
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    return next;
}

vector<int> KMPsearch(const string& text, const string& pattern, const vector<int>& next) {
    vector<int> positions;  // 存储匹配位置
    int n = text.size();
    int m = pattern.size();
    int i = 0;  // text指针
    int j = 0;  // pattern指针

    while (i < n) {
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
        if (j == m) {
            if(i-m==0 || !isalnum(text[i - m - 1])) { // 前边界检查
                if(i==n || !isalnum(text[i])) { // 后边界检查
                    positions.push_back(i - m); // 记录匹配位置
                }
            }
            j = next[j];  // 继续寻找下一个匹配
        }
    }
    return positions;
}

string tolower(const string& str){
    string result = str;
    for (auto& ch : result) {
        ch = std::tolower(ch);
    }
    return result;
}

class TextResearchAssistant {
private:
    map<string, pair<int, set<int>>> wordStats; // 单词统计数据
    vector<string> targetWords; // 目标词汇列表
    vector<string> textLines; // 文本行列表

public:
    bool readTextFile(const string& filename){
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filename << endl;
            return false;
        }

        textLines.clear();
        string line;

        while (getline(file, line)) {
            textLines.push_back(line);
        }

        file.close();
        cout<<"success read text file,sum "<<textLines.size()<<" lines"<<endl;
        return true;
    }

    void inputTargetWords(){
        cout<<string(60, '=')<<endl;
        cout<<"Please input target words, separated by spaces:"<<endl;
        string word;

        while(true){
            cout<<"> ";
            getline(cin, word);

            if(word.empty()) break;

            string lowerWord = tolower(word);

            if(find(targetWords.begin(), targetWords.end(), lowerWord) == targetWords.end()){
                targetWords.push_back(lowerWord);
                cout<<"Added word: "<<lowerWord<<endl;
            }
            else{
                cout<<"Word already exists: "<<lowerWord<<endl;
            }
        }

        cout<<"Total target words: "<<targetWords.size()<<endl;
    }

    void analyzeText(){
        cout<<string(60, '=')<<endl;
        cout<<"Analyzing text..."<<endl;

        for(size_t lineNum = 0; lineNum < textLines.size(); ++lineNum){
            string line = tolower(textLines[lineNum]);
            string lowerLine = tolower(line);

            // 对每个目标词进行KMP搜索
            for(const auto& word : targetWords){
                // 计算next数组
                vector<int> next = computeNext(word);
                // 执行KMP搜索
                vector<int> positions = KMPsearch(line, word, next);

                if(!positions.empty()){
                    wordStats[word].first += positions.size();
                    wordStats[word].second.insert(lineNum + 1); // 行号从1开始
                }
            }

            if((lineNum+1) % 1000 == 0){
                cout<<"Processed "<<(lineNum+1)<<" lines"<<endl;
            }
        }
        cout<<"Analysis complete."<<endl;
    }

    void displayResults(){
        cout<<string(60, '=')<<endl;
        cout<<"Results:"<<endl;

        for(const auto& entry : wordStats){
            const string& word = entry.first;
            int count = entry.second.first;
            const set<int>& lines = entry.second.second;

            cout<<"Word: "<<word<<", Count: "<<count<<", Lines: ";
            for(const auto& lineNum : lines){
                cout<<lineNum<<" ";
            }
            cout<<endl;
        }
    }

    void displayLineContent(int lineNum){
        if(lineNum < 1 || lineNum > static_cast<int>(textLines.size())){
            cout<<"Invalid line number."<<endl;
            return;
        }
        cout<<"Line "<<lineNum<<": "<<textLines[lineNum - 1]<<endl;
        cout<<textLines[lineNum - 1]<<endl;
    }

    int getTotalLines() const {
        return textLines.size();
    }
    
};

int main(){
    TextResearchAssistant assistant;

    cout<<"Welcome to the Literary Research Assistant!"<<endl;

    string filename;
    cout<<"Enter the text file name:"<<endl;
    getline(cin, filename);

    if(!assistant.readTextFile(filename)){
        return 1;
    }

    assistant.inputTargetWords();
    assistant.analyzeText();
    assistant.displayResults();

    while(true){
        cout<<"Enter a line number to view its content (0 to exit):"<<endl;
        int lineNum;
        cin>>lineNum;
        if(lineNum == 0) break;
        assistant.displayLineContent(lineNum);
    }

    cout << "\n" << string(60, '=') << endl;
    cout<<"Thank you for using the Literary Research Assistant. Goodbye!"<<endl;
    cout << string(60, '=') << endl;

    return 0;
}
