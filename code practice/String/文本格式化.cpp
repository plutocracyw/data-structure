/*
文本格式化程序的核心任务是将输入的纯文本按照指定的版面参数重新排列，这涉及到：

文本分析：识别单词、句子结构

布局计算：根据页宽自动换行，避免单词被分割

分页管理：按页长分页，添加页眉页脚

格式控制：左对齐、空格压缩等
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct FormatParams {
    int pagelength;
    int pagewidth;
    int leftmargin;     // 左边距
    int headinglength;  // 页眉长度
    int footinglength;  // 页脚长度
    int startpage;      // 起始页码
};

class Word{
public:
    string content;
    int length;
    
    Word(const string& str) : content(str), length(str.length()) {}
};

class TextFormatter {
private:
    FormatParams params;
    vector<Word> words;
    vector<vector<string>> pages;

    // 读取单词列表
    void readWords(ifstream &inputFile)
    {
        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                words.emplace_back(word);
            }
        }
    }

    // 格式化文本
    void formatText()
    {
        int currentPage = 0;
        int currentLineInPage = 0;
        int currentWidth = 0;

        pages.emplace_back(); // 新建第一页
        vector<string> &currentPageLines = pages.back();

        // 添加页眉
        for (int i = 0;i<params.headinglength;++i){
            currentPageLines.push_back("");
            currentLineInPage++;
        }

        // 排版单词
        for(size_t i = 0; i < words.size(); ++i)
        {
            if (currentLineInPage >= params.pagelength - params.footinglength)
            {
                for (int j = 0;j<params.footinglength;++j){
                    currentPageLines.push_back("");
                }
                pages.emplace_back(); // 新建新页
                currentPageLines = pages.back();
                currentLineInPage = 0;
                for (int j = 0;j<params.headinglength;++j){
                    currentPageLines.push_back("");
                    currentLineInPage++;
                }
                currentWidth = 0;
            }

            if (currentWidth + words[i].length + (currentWidth > 0 ? 1 : 0) <= params.pagewidth - params.leftmargin)
            {
                if (currentWidth > 0)
                {
                    currentPageLines.back() += " ";
                    currentWidth += 1;
                }
                currentPageLines.back() += words[i].content;
                currentWidth += words[i].length;
            }
            else
            {
                currentPageLines.push_back(string(params.leftmargin, ' ') + words[i].content);
                currentLineInPage++;
                currentWidth = params.leftmargin + words[i].length;
            }
        }

        // 添加页脚
        addFooter(currentLineInPage,currentPage+params.startpage);
    }

    void addFooter(int &currentLineInPage,int pageNumber){
        vector<string> &currentPageLines = pages.back();
        for (int j = 0;j<params.footinglength-1;++j){
            currentPageLines.push_back("");
            currentLineInPage++;
        }
        // 添加页码
        string footer = "Page " + to_string(pageNumber);
        currentPageLines.push_back(string((params.pagewidth - footer.length()) / 2, ' ') + footer);
        currentLineInPage++;
    }

public:
    TextFormatter(const FormatParams& p) : params(p) {}

    // 处理文件
    void processFile(const string& filename)
    {
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        readWords(inputFile);
        inputFile.close();

        formatText();
    }

    // 输出格式化后的文本
    void displayFormattedText()
    {
        for (size_t i = 0; i < pages.size(); ++i)
        {
            for (const auto& line : pages[i])
            {
                cout << line << endl;
            }
            if (i < pages.size() - 1)
            {
                cout << string(params.pagewidth, '=') << endl; // 分页符
            }
        }
    }
};

int main(){
    FormatParams params;

    cout<<"Enter page length: "<<endl;
    cin>>params.pagelength;

    cout<<"Enter page width: ";
    cin>>params.pagewidth;

    cout<<"Enter left margin: ";
    cin>>params.leftmargin;

    cout<<"Enter heading length: ";
    cin>>params.headinglength;

    cout<<"Enter footing length: ";
    cin>>params.footinglength;

    cout<<"Enter start page number: ";
    cin>>params.startpage;

    TextFormatter formatter(params);
    string filename;
    cout<<"Enter the text file name:"<<endl;
    cin>>filename;
    string outfilename;
    cout<<"Enter the output file name:"<<endl;
    cin>>outfilename;

    formatter.processFile(filename);
    formatter.displayFormattedText();

    return 0;

}