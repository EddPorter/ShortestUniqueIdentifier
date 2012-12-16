// ShortestUniqueIdentifier
// reads in a list of unique strings and creates the shortest unique identifier
// for each such that searching for "*<id>*" returns only one string.

#include <iostream>     // cin, cout
#include <map>          // map
#include <ostream>      // endl
#include <numeric>      // accumulate
#include <set>          // set
#include <string>       // string

using namespace std;

int main() {

  set<string> inputs;

  char inputLine[255];
  while (true) {
    cin >> inputLine;
    string input(inputLine);
    if (input == "end") { break; }

    if (inputs.find(input) != inputs.end()) {
      cout << "\tDuplicate input. Ignoring." << endl;
    }

    inputs.insert(input);
  }

  map<string, string> uniqueStrings;
  for (auto i = inputs.begin(); i != inputs.end(); ++i) {
    string input = *i;
    //cout << "Processing: " << input << endl;

    auto best = uniqueStrings.find(input);
    if (best != uniqueStrings.end() && (*best).second.length() == 1) {
      // Can't get much better than that.
      continue;
    }

    for (auto firstIt = input.begin(); firstIt != input.end(); ++firstIt) {
      for (auto secondIt = firstIt + 1; secondIt != input.end() && (best == uniqueStrings.end() || (*best).second.length() != 1); ++secondIt) {
        const string candidate = input.substr(firstIt - input.begin(), secondIt - firstIt);
        //cout << "\tTrying: " << candidate << endl;

        int count = accumulate(inputs.begin(), inputs.end(), 0, [candidate](int acc, string in) {
          if (in.find(candidate) != string::npos) {
            return acc + 1;
          } else {
            return acc;
          }
        });

        if (count == 1) {
          if (best == uniqueStrings.end()) {
            // not previous candidate found, so just add and update
            uniqueStrings[input] = candidate;
            //cout << "\tFound new best match: " << candidate << endl;
            best = uniqueStrings.find(input);
          } else {
            if (candidate.length() < (*best).second.length()) {
              uniqueStrings[input] = candidate;
              //cout << "\tFound new best match: " << candidate << endl;
            }
          }
        }
      }
    }
  }

  for (auto i = uniqueStrings.begin(); i != uniqueStrings.end(); ++i) {
    cout << (*i).first << "\t" << (*i).second << endl;
  }

  return 0;
}