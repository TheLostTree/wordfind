#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string.h>
#include <vector>
//#include "json.hh"

using namespace std;
class mappain{
    //haha look the map declaration is in a class im so good at coding wow
    map<string, vector<string> > connect;
    public:
        int addtomap(string, string);
        void findinmap(string);
};
int mappain::addtomap(string sorted,string original){
    //ofstream writerbs("indexingshit.txt");
    //writerbs.open("indexingshit.txt", ios::trunc);
    vector <string> possible;
    map<string, vector<string> >::iterator locat = connect.find(sorted);
    //if the value isnt then just add it
    if(locat == connect.end()){
        possible.insert(possible.begin(), original);
        connect.insert(make_pair(sorted, possible));
    }
    //if the sorted version of the word is already in the dictionary append the original word to the list
    else{
        possible = locat->second;
        possible.insert(possible.begin(), original);
        connect[sorted] = possible;
    }
    return 1;
}
void mappain::findinmap(string in){
    
    map<string, vector<string> >::iterator location = connect.find(in);
    vector<string> storage = location->second;
    cout << "i ran\n";
    for(int temptemp=0; temptemp < storage.size(); temptemp++){
        cout << storage.at(temptemp) << '\n';
    }
}
//process a giant word list and categorize by letters, eventually
int parse(int ct, string fileinp,mappain sufferingagain) {
    //decleare filereader named reader
    ifstream reader;
    //open up the words list
    reader.open(fileinp);
    //cout << "Opened file "<< "\n";
    //oh god wordlist.txt has 370,103 words in it if i didnt count wrong
    //move the reader to the next word, iterated in main
    reader.seekg(ct);
    //cout << "moved to " << ct << "\n";
    // im sure creating a variable like 100 times to itrate 100 times is terrible but eh
    string line = "";
    //make sure this is open, else return -1
    if (reader.is_open()) {
        //pull a line from ifstream (var line here has nothing to do with it)
        reader >> line;
        string copy = line;
        //output it (replace cout with an actual function)
        //cout << line << "\n";
        //bruh i spent so much time and apparently theres a function that does all the work for me im fine

        //oh yay this next block of code woulda been in a different function but oh well        
        //sort it
        sort(line.begin(), line.end());
        //removeduplicate letters
        char ch[line.length()];
        //convert str to char array :vomit
        string finalstr = "";
        strcpy(ch, line.c_str());
        for(int index = 0; index < sizeof(ch);){
            char letter = ch[index];
            int increment = 1;
            while(ch[index] == ch[index+increment]){
                increment++;
            }
            finalstr = finalstr + letter;
            index = index + increment;
        }
        line = finalstr;
        cout << line << "\n";
        sufferingagain.addtomap(line, copy);


        //end of file, close reader and return 0
        if (reader.eof()) {
            reader.close();
            cout << "End of file" << "\n";
            return -10;
        }
        //write reader loc to a var so i can both return and close the reader
        int iguess = reader.tellg();
        //cout << "location: " << iguess << "\n";
        reader.close();
        //yay i fixed the jank
        if(iguess!= -10){
            parse(iguess, fileinp, sufferingagain);
        }
    }
    else {
        cout << "uhoh it didnt open ;-;" << "\n";
        return -9;
    }
    return -9;
}
int main() {
    //jank
    string file= "words_test.txt";
    mappain suffering;
    parse(0,file,suffering);
    suffering.findinmap("lameness");

    return 0;
}