#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

void iscorrect(fstream& xmlfile , ofstream& correctxml) {
    string in;
    int line = 0;
    stack<string> tags;
    stack<int> lines;
    int errors = 0;

    while (!xmlfile.eof()) {
        getline(xmlfile,in);
        line++;
        bool body = true;
        bool print = true;
        for (int i = 0; i < in.size(); i++) {
            if (in[i] == '<' && in[i + 1] != '/') {
                string s;
                body = false;
                i++;
                while (in[i] != '>') {
                    s.push_back(in[i++]);
                    if (in[i] == '>') { break; }
                }
                tags.push(s);
                lines.push(line);
                for (int n = 0; n < in.size(); n++) {
                    if (in[n] == '<' && in[n + 1] == '/') {
                        print = false;
                    }
                }
                if (print) {
                    correctxml << in << endl;
                }
            }
            if (in[i] == '<' && in[i + 1] == '/') {
                string m;
                body = false;
                i = i + 2;
                int n1 = i;
                while (in[i] != '>') {
                    m.push_back(in[i++]);
                    if (in[i] == '>') { break; }
                }
				if (tags.empty()) {
						in = "";
						errors++;
						cout << "error at line the close tag at line " << line <<endl;
						error->WriteLine(xx);
					}
                if (!tags.empty() && m == tags.top()) {
                    tags.pop();
                    lines.pop();
                    correctxml << in << endl;
                    while (!tags.empty() && m == tags.top()) {
                        cout << "error at line the open tag at line " << lines.top() << " and the close tag at line " << line << endl;
                        errors++;
                        cout << tags.top() << endl;
                        tags.pop();
                        lines.pop();
                        correctxml << in << endl;
                    }
                }
                else {
				if(!tags.empty()){
	                    cout << "error at line the open tag at line " << lines.top() << " and the close tag at line " << line << endl;
	                    errors++;
	                    cout << tags.top() << endl;
	                    string old = in;
	                    in.replace(n1, m.size(), tags.top());
	                    tags.pop();
	                    lines.pop();
	                    correctxml << in << endl;
	                    while (!tags.empty() && m == tags.top()) {
	                        tags.pop();
	                        lines.pop();
	                        correctxml << old << endl;
	                    }
					}
                }
            }
        }
        if (body) {
            correctxml << in << endl;
        }
    }
    while (!tags.empty()) {
        cout << "error at line " << lines.top() << endl;
        errors++;
        correctxml << "</" << tags.top() << ">" << endl;
        tags.pop();
        lines.pop();
    }
    cout << "errors " << errors;
}

void compress(fstream& xmlfile, ofstream& compressedxml) {
    string in;
    while (!xmlfile.eof()) {
        getline(xmlfile, in);
        in.erase(remove(in.begin(), in.end(), ' '), in.end());
        bool body = true;
        for (int i = 0; i < in.size(); i++) {
            if (in[i] == '<' && in[i + 1] != '/') {
                string m;
                string news;
                body = false;
                i++;
                int n2 = i;
                while (in[i] != '>') {
                    m.push_back(in[i++]);
                }
                if (m == "users") {
                    news = "!";
                }
                if (m == "user") {
                    news = "@";
                }
                if (m == "id") {
                    news = "#";
                }
                if (m == "name") {
                    news = "$";
                }
                if (m == "posts") {
                    news = "%";
                }
                if (m == "post") {
                    news = "^";
                }
                if (m == "body") {
                    news = "&";
                }
                if (m == "topics") {
                    news = "*";
                }
                if (m == "topic") {
                    news = "+";
                }
                if (m == "followers") {
                    news = "-";
                }
                if (m == "follower") {
                    news = "[";
                }
                in.replace(n2, m.length(), news);
                i = i - m.size() + 1;
            }
            if (in[i] == '<' && in[i + 1] == '/') {
                string m;
                body = false;
                string news2;
                i = i + 2;
                int n1 = i;
                while (in[i] != '>') {
                    m.push_back(in[i++]);
                }
                if (m == "users") {
                    news2 = "!";
                }
                if (m == "user") {
                    news2 = "@";
                }
                if (m == "id") {
                    news2 = "#";
                }
                if (m == "name") {
                    news2 = "$";
                }
                if (m == "posts") {
                    news2 = "%";
                }
                if (m == "post") {
                    news2 = "^";
                }
                if (m == "body") {
                    news2 = "&";
                }
                if (m == "topics") {
                    news2 = "*";
                }
                if (m == "topic") {
                    news2 = "+";
                }
                if (m == "followers") {
                    news2 = "-";
                }
                if (m == "follower") {
                    news2 = "[";
                }
                in.replace(n1, m.size(), news2); 
                i = i - m.size() + 1;
            }
        }
        compressedxml << in;
    }
}

int main()
{
    fstream xmlfile;
    ofstream correctxml("correct.xml");
    xmlfile.open("sample.xml");
    iscorrect(xmlfile, correctxml);
    //ofstream compressedxml("compressed.xml");
    //compress(xmlfile, compressedxml);

}
