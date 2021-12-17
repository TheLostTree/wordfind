// REVIEW clang-format is your friend, use it, though I don't remeber if macos comes with it by default

#include <math.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility> // REVIEW: for std::move
#include <vector>

//#include "json.hh"

using namespace std;

class readersuffering {
public:
    ifstream fileIn;
    string filename;
    // REVIEW there is no need to put a bunch of these stuff as member variables
    // string line;

    /* REVIEW
      // this'll be great fun
      // i love vectors now
      // also 2d vector because i like confusing myself
      // im sure this'll wont blow up in my face
      vector<vector<string>> dictionary;
      vector<string> key;
    */

    map<string, vector<string>> dict;
    // will be formated simplified version, actual word

    vector<char> letters;
    vector<char> used;

public:
    bool openFile(string);
    void readAndProcess();
    // REVIEW
    // vector<string> findWord(string);
    // REVIEW use pointer to indicate value-or-nothing relationship
    // REVIEW `const` makes this member function (aka method) not allowed to modify `this`, making sure there is no unintended side effects
    const vector<string>* findWord(string) const;
    // REVIEW
    // void findAll(string);
    vector<string> findAll(string) const;

    // REIVEW why tf is used as output of a function
    // vector<string> combination;
};

bool readersuffering::openFile(string in) {
    // why does this function exist it doesnt need to but ok
    fileIn.open(in);
    if (fileIn.is_open()) {
        cout << "File Open \n";
        return true;
    } else {
        return false;
    }
}

void readersuffering::readAndProcess() {
    string line;
    cout << "loading... \n";
    while (!fileIn.eof()) {
        getline(fileIn, line);
        string copy = line;
        // load the word into dictionary
        sort(line.begin(), line.end());

        // Fun fact: std::string is an alias to std::basic_string, which is basically a fancy vector
        /* REVIEW
            vector<char> v(line.begin(), line.end());
            // add a space because buffer value i could probably use a random unicode
            // char instead but this is easier
            v.insert(v.end(), ' ');
        */

        // REVIEW begin
        string finalstr = "";
        for (int index = 0; index < line.size();) {
            char letter = line[index];
            int chunkSize = 1;

            // std::string is null terminated, aka there is always a \0 character at the end
            // this will safely stop when it reaches the end
            while (line[index] == line[index + chunkSize]) {
                ++chunkSize;
            }

            finalstr.push_back(letter);
            index += chunkSize;
        }
        // REVIEW end

        /* REVIEW
            string finalstr = "";
            for (int index = 0; index < v.size();) {
              char letter = v.at(index);
              int increment = 1;
              // these if statements are probably redundant but i really need this to
              // NOT break so redundant it is im sure the compiler is smarter than me
              // and will fix this
              // if letter == letter to the right, then check the letter to the right of
              // that one
              if ((index + increment) < v.size()) {
                while (v.at(index) == v.at(index + increment)) {
                  if ((index + increment) < v.size()) {
                    ++increment;
                  }
                  // oh wow i fixed it by adding a space to the end im so good at my job
                }
              }
              // add the letter to the final output
              if (letter != ' ') {
                // skip the space
                finalstr = finalstr + letter;
              }
              // skip over the repeating letters
              index = index + increment;
            }
            // cout << finalstr << endl;
        */

        // REVIEW begin
        auto iter = dict.find(finalstr);
        if (iter != dict.end()) {
            iter->second.push_back(copy);
        } else {
            vector<string> wordList{ copy };
            // emplace is just much better than insert since you don't have to deal with the pair<key,value> mess
            // (of course, this is c++, it generates much worse error message if you give it the wrong thing)
            dict.emplace(finalstr, std::move(wordList));
            // Alternatively:
            // dict.insert({finalstr, std::move(wordList)});
            // {value, value...} is a synatx added in C++11 that allows the class type to be deduced from where { ... } is going to
            // In this case the insert() function takes a std::pair, so { ... } is deduced to be pair<string, vector<string>>
            // There is also a whole other mess of difference between SomeClass() and SomeClass{} and the 11 different ways to initialize objects in c++,
            // and the 10000 line file SemaInit.cpp in clang to deal with this mess
            // Search C++ initialization if you want to learn more
        }
        // REVIEW end

        /* REVIEW
            // find if sorted version already exists, if not then add it
            auto it = find(key.begin(), key.end(), finalstr);
            if (it != key.end()) {
              // it is there
              dictionary[distance(key.begin(), it)].push_back(copy);
              // cout << "dictionary added word " << copy << endl;

              // add word corresponding to the simplified version
            } else {
              // it is not there
              key.push_back(finalstr);
              vector<string> in;
              dictionary.push_back(in);
              dictionary[dictionary.size() - 1].push_back(copy);
              // cout << "dictionary added new word " << copy << endl;
              // add the sorted version on a different vector cause im lazy and
              // inefficient add the word corresponding on row 2
            }
            // add the og word in the same row/ column depends on what i implememnt
        */
    }
}

// REVIEW
// vector<string> readersuffering::findWord(string inpls) {
const vector<string>* readersuffering::findWord(string inpls) const {
    sort(inpls.begin(), inpls.end());

    auto iter = dict.find(inpls);
    if (iter != dict.end()) {
        return &iter->second;
    } else {
        return nullptr;
    }

    /* REVIEW
      vector<string>::iterator it;
      it = find(key.begin(), key.end(), inpls);
      if (it != key.end()) {
        // it is there
        return dictionary[distance(key.begin(), it)];
      } else {
        vector<string> sigh;
        // sigh.push_back("none cause ya messed up >:( \n");
        return sigh;
      }
    */
}

// REVIEW
// void readersuffering::findAll(string str) {
vector<string> readersuffering::findAll(string str) const {
    // stolen code from geeksforgeeks because i cant be bothered

    // REVIEW
    vector<string> result;

    /* Number of subsequences is (2**n -1)*/
    int n = str.length();
    unsigned int opsize = pow(2, n);

    /* Generate all subsequences of a given string.
       using counter 000..1 to 111..1*/
    for (int counter = 1; counter < opsize; counter++) {
        string subs = "";
        for (int j = 0; j < n; j++) {
            /* Check if jth bit in the counter is set
                If set then print jth element from arr[] */
            if (counter & (1 << j))
                subs.push_back(str[j]);
        }

        /* Print current subsequence */

        result.push_back(subs);
    }

    return result;
}

int main() {
    // jank
    string file = "words_alpha.txt";
    // first letter is required
    readersuffering readerpain;
    if (readerpain.openFile(file)) {
        readerpain.readAndProcess();

		// REVIEW begin
		/* Used to make dump.txt
		for (auto& [key, words] : readerpain.dict) {
			cout << key << ": ";
			for (auto& word : words) {
				cout << word << ' ';
			}
			cout << '\n';
		}
		return 0;
		*/
		// REVIEW end

        cout << "done loading \n";
        string input;
        // REVIEW redundent condition
        // while (input != "EXITPLS") {
        while (true) {
            cout << "letters: \n";
            cin >> input;
            if (input == "EXITPLS") {
                break;
            }

            // REVIEW begin
            // `auto` is type inference
            vector<string> out;
            auto combinations = readerpain.findAll(input);
            for (auto& word : combinations) {
                // C++17 construct, equivalent to
                /*
                auto relatedWords = readerpain.findWord(word);
                if (relatedWords) {
                  ...
                }
                */

                if (auto relatedWords = readerpain.findWord(word)) {
                    out.insert(out.end(), relatedWords->begin(), relatedWords->end());
                    // Alternatively
                    /*
                    for (auto& word : relatedWords) {
                      out.push_back(word);
                    }
                    */
                }
            }

            cout << "searching for " << combinations.size() << " different permutations, found: ";
            for (auto& word : out) {
                if (word.size() > 3) {
                    cout << word << ' ';
                }
            }
            cout << '\n';
            // REVIEW end

            /* REVIEW
                  readerpain.findAll(input);
                  // make an output vector and a temp vector
                  vector<string> out;
                  vector<string> temp;
                  // for all the items in vector combination(what the function returns),
                  // find word from dictionary and add it to "out"
                  cout << readerpain.combination.size() << endl;
                  for (int qoq = 0; qoq < readerpain.combination.size(); qoq++) {
                    string str = readerpain.combination[qoq];
                    temp = readerpain.
					findWord(str); // TODO
                    // cout << readerpain.combination[qoq] << endl;
                    for (int qiqi = 0; qiqi < temp.size(); qiqi++) {
                      out.push_back(temp[qiqi]);
                    }
                  }
                  cout << "words are: ";
                  // print the words out :D
                  for (int i = 0; i < out.size(); i++) {
                    if (out[i].size() > 3) {
                      cout << out.at(i) << ' ';
                    }
                  }
                  cout << "\n";
                  readerpain.combination.clear();
            */
        }
    } else {
        cout << "file aint existent";
        return -1;
    }

    return 0;
}
