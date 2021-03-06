#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>

//#include "json.hh"

using namespace std;

class readersuffering{
    ifstream fileIn;
    string filename;
    string line;
    //this'll be great fun 
    //i love vectors now
    //also 2d vector because i like confusing myself
    //im sure this'll wont blow up in my face
    vector< vector <string> > dictionary;
    vector <string> key;
    //will be formated simplified version, actual word
    
    vector <char> letters;
    vector <char> used;
    public:
        bool openFile(string);
        void readAndProcess();
        vector <string> findword(string);
        void findAll(string);
        vector <string> combination;
};

void readersuffering::readAndProcess(){
    cout << "loading... \n";
    while(!fileIn.eof()){
        getline(fileIn, line);
        string copy = line;
        //load the word into dictionary
        sort(line.begin(), line.end());
        vector<char> v(line.begin(), line.end());
        //add a space because buffer value i could probably use a random unicode char instead but this is easier 
        v.insert(v.end(),' ');

        string finalstr = "";
        for(int index = 0; index < v.size();){
            char letter = v.at(index);
            int increment = 1;
            // these if statements are probably redundant but i really need this to NOT break so redundant it is
            // im sure the compiler is smarter than me and will fix this
            //if letter == letter to the right, then check the letter to the right of that one
            if ((index+increment) < v.size()){
                while(v.at(index) == v.at(index+increment)){
                    if ((index+increment) < v.size())
                    {
                        ++increment;
                    }
                    //oh wow i fixed it by adding a space to the end im so good at my job   
                }
            }
            //add the letter to the final output
            if(letter != ' '){
                //skip the space
                finalstr = finalstr + letter;
            }
            //skip over the repeating letters
            index = index + increment;
        }
        //cout << finalstr << endl;

        //find if sorted version already exists, if not then add it
        vector<string>::iterator it;
        it = find(key.begin(), key.end(), finalstr);
        if(it != key.end()){
            //it is there
            dictionary[distance(key.begin(), it)].push_back(copy);
            //cout << "dictionary added word " << copy << endl;

            //add word corresponding to the simplified version
        }
        else{
            //it is not there
            key.push_back(finalstr);
            vector <string> in;
            dictionary.push_back(in);
            dictionary[dictionary.size()-1].push_back(copy);
            //cout << "dictionary added new word " << copy << endl;
            //add the sorted version on a different vector cause im lazy and inefficient
            //add the word corresponding on row 2
        
        }
        //add the og word in the same row/ column depends on what i implememnt

    }

}
vector<string> readersuffering::findword(string inpls){
    sort(inpls.begin(), inpls.end());
    vector<string>::iterator it;
    it = find(key.begin(), key.end(), inpls);
    if(it != key.end()){
        //it is there
        return dictionary[distance(key.begin(), it)];
    }
    else{
        vector <string> sigh;
        //sigh.push_back("none cause ya messed up >:( \n");
        return sigh;
    }
}

bool readersuffering::openFile(string in){
    //why does this function exist it doesnt need to but ok
    fileIn.open(in);
    if (fileIn.is_open()){
        cout << "File Open \n";
        return true;
    }
    else{
        return false;
    }
}


void readersuffering::findAll(string str)
{   
    //stolen code from geeksforgeeks because i cant be bothered


    /* Number of subsequences is (2**n -1)*/
    int n = str.length();
    unsigned int opsize = pow(2, n);
  
    /* Generate all subsequences of a given string.
       using counter 000..1 to 111..1*/
    for (int counter = 1; counter < opsize; counter++)
    {
        string subs = "";
        for (int j = 0; j < n; j++)
        {
            /* Check if jth bit in the counter is set
                If set then print jth element from arr[] */
            if (counter & (1<<j))
                subs.push_back(str[j]);
        }
  
        /* Print current subsequence */

        combination.push_back(subs);        
    }
}
  
int main() {
    //jank
    string file= "moresanelist.txt";
    //first letter is required 
    readersuffering readerpain;
    if (readerpain.openFile(file)){
        readerpain.readAndProcess();
        cout << "done loading \n";
        string input;
        //
        while (input != "EXITPLS"){
            cout << "letters: \n";
            cin >> input;
            if (input == "EXITPLS"){
                break;
            }
            readerpain.findAll(input);
            //make an output vector and a temp vector
            vector <string> out;
            vector <string> temp;
            //for all the items in vector combination(what the function returns), find word from dictionary and add it to "out"
            cout << readerpain.combination.size() << endl;
            for(int qoq = 0; qoq < readerpain.combination.size(); qoq++){
                string str = readerpain.combination[qoq];
                temp = readerpain.findword(str);
                //cout << readerpain.combination[qoq] << endl;
                for(int qiqi = 0; qiqi < temp.size(); qiqi ++){
                    out.push_back(temp[qiqi]);
                }
            }
            cout << "words are: ";
            //print the words out :D
            for(int i=0; i < out.size(); i++){
                if(out[i].size() >3){
                    cout << out.at(i) << ' ';
                }
            }
            cout << "\n";
            readerpain.combination.clear();
        }
    }
    else{
        cout << "file aint existent";
        return -1;
    }
    
    return 0;
}