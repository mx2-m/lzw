#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>


using namespace std;

ofstream out;

string branje(const char s[]) {
    string ss;
    ifstream in(s);
    if (in.is_open()) {
        getline(in, ss, '\0');
    }
    in.close();
    return ss;
}

string inputText(const string &pot) {
    ifstream input(pot);
    stringstream sstream;

    if (!input.is_open()) {
        return string();
    }

    sstream << input.rdbuf();
    return sstream.str();
}

void izpis(vector<int> *polje, int len) {
    for (int i = 0; i < len; ++i) {
        out << polje->at(i) << ' ';
    }
    out << endl;
}

vector<int> kompresija(const string &file, int size) {
    string T;
    unordered_map<string, int> S;
    vector<int> izhod;
    int slovar = 256;
    for (int i = 0; i < 256; i++)
        S[string(1, i)] = i;

    for (string::const_iterator it = file.begin();
         it != file.end(); ++it) {
        char C = *it;
        string TC = T + C;
        if (S.find(TC) != S.end())
            T = TC;
        else {
            izhod.push_back(S[T]);
            S[TC] = slovar++;
            T = string(1, C);
        }
    }
    if (!T.empty())
        izhod.push_back(S[T]);

    return izhod;
}


void dekompresija(vector<int> vhod)
{
    int V = vhod[0];
    int n;
    unordered_map<int, string> S;
    string s = S[V];
    string c = "";
    c += s[0];
    cout << s;
    int slovar = 256;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        S[i] = ch;
    }


    for (int i = 0; i < vhod.size() - 1; i++) {
        n = vhod[i + 1];
        if (S.find(n) == S.end()) {
            s = S[V];
            s = s + c;
        }
        else {
            s = S[n];
        }
        cout << s;
        out<<s;
        c = "";
        c += s[0];
        S[slovar] = S[V] + c;
        slovar++;
        V  = n;
    }
}

int main(int argc, const char* argv[]) {

    const char* size=argv[2];


    if (argv[1][0] == 'c') {
        out.open("out.txt");
        vector<int> komp = kompresija(branje(argv[3]),10);
        cout << "KOMPRESIJA: "<<endl;
        for (unsigned int i = 0; i < komp .size(); i++) {
            cout << komp [i] << " ";
            out<<komp [i] << " ";

        }}
     else if(argv[1][0] == 'd') {
        out.open("out_d.txt");
        vector<int> komp = kompresija(branje(argv[3]),10);
        cout << "DEKOMPRESIJA: "<<endl;
        dekompresija(komp);



        }



    return 0;

}
