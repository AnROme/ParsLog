#include<regex>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include<functional>

using namespace std;

typedef map<string, unsigned int> statAppear;
typedef multimap<int, string, std::greater<int>> sortedMultiMap;



int parsLog(string fileName, statAppear &domains, statAppear &paths){

        ifstream reader(fileName);
        if(!reader.is_open()){
                cout << "Can't open file " << fileName << endl;
                return -1;
        }

        regex refer("(https?://)([a-zA-Z0-9.-]+)(/?)([a-zA-Z0-9.,/+_]*)");
		
        string domainName, path;

        unsigned int countUrls = 0;
        for (string str; getline(reader, str);) {

                sregex_iterator It, curIt;

                /**** all detected URLs in read string *****/
                It = curIt = sregex_iterator(str.begin(), str.end(), refer);
                sregex_iterator endIter;

                smatch match;

                while(It != endIter) {
                        ++countUrls;
                        match = *It++;

                        domainName = match[2];
                        auto iter = domains.find(domainName);


                        if (iter != domains.end()) {
                                ++(iter->second);
                        }
                        else {
                                /* value first met */
                                domains[domainName] = 1;
                        }

                        int countMatches = match.size();

                        if (countMatches == 4 || countMatches == 3)
                                path = "/";
                        else if (countMatches == 5)
                        {
                                path = "/";
                                if(match[3] == "/")
                                        path += match[4];

                        }

                        iter = paths.find(path);
                        if (iter != paths.end()) {
                                ++(iter->second);
                        }
                        else {
                                paths[path] = 1;
                        }

                }
        }

        reader.close();
        return countUrls;
}

int collectStatistics_URLs(string inFileName, string outFileName, int topCount){

        /* In these containers, strings(domains and paths) will be arranged in lexicographical order */
        statAppear domains, paths;

        /* The log file is read and collect statistics of the contains URLs therein */

        int countUrls = parsLog(inFileName, domains, paths);

        if(countUrls < 0)
                return 0;
        if(countUrls == 0){
                cout << "Urls absent in file " << inFileName << endl;
                return 0;
        }

        sortedMultiMap sortedDomains, sortedPaths;

        for (auto it = domains.begin(); it != domains.end(); ++it) {
                auto pair = it;
                sortedDomains.insert(make_pair(pair->second, pair->first));
        }

        for (auto it = paths.begin(); it != paths.end(); ++it)
        {
                auto pair = it;
                sortedPaths.insert(make_pair(pair->second, pair->first));
        }

        /* write result in the file */

        string res;

        ofstream writer(outFileName);

        if(!writer.is_open()){
                cout << "Can't open file " << outFileName << endl;
                return -1;
        }

        /* General statistics */
        res = string("total urls ") + to_string(countUrls) + string(", domains ") +
                to_string(domains.size()) + string(", paths ") + to_string(paths.size());

        res += '\n';

        /* Write the frequency of encountered domains */

        res += string("\ntop domains\n");

        int countLines = (topCount == 0 || topCount > domains.size()) ? domains.size() : topCount;

        auto iter = sortedDomains.begin();
        string val_stat;
        string val_str;

        writer << res;
        res.clear();

        int cur = 0;

        while (cur < countLines)
        {
                val_stat = to_string(iter->first);
                val_str = iter->second;

                res += val_stat + ' ' + val_str + '\n';
                ++cur;
                ++iter;
        }

        writer << res;
        res.clear();

        /*Write the frequency of encountered paths */

        res += string("\ntop paths\n");

        countLines = (topCount == 0 || topCount > paths.size()) ? paths.size() : topCount;

        iter = sortedPaths.begin();
        cur = 0;

        while (cur < countLines)
        {
                val_stat = to_string(iter->first);
                val_str = iter->second;

                res += val_stat + ' ' + val_str + '\n';
                ++cur;
                ++iter;
        }

        writer << res;
        writer.close();

        return 0;
}



int main(int argc, char **argv) {

        string helpString = "Use format:\n\tmyTest [-n NNN] in.txt out.txt\nAllowed a format:\n\tmyTest in.txt\n";

        if (argc <= 1)
        {
                cout << "Program need more input information.\n" << helpString << endl;
                getchar();
                return 0;
        }

        string inFileName, outFileName;
        int topCount = 0;

        if (argc == 2) {
                /* Only the input file is specified */
                inFileName = argv[1];
                outFileName = "out.txt";
        }
        else if (argc == 3)
        {
                inFileName = argv[1];
                outFileName = argv[2];
        }
        else if (argc <= 5)
        {
                if (!strcmp(argv[1], "-n"))
                {
                        if (sscanf(argv[2], "%d", &topCount) != 1) {
                                cout << "'-n' requires  integer parameter." << endl;
                                return 0;
                        }

                        if(topCount < 0)
                        {
                                cout << "'-n' requires positive integer parameter." << endl;
                                return 0;
                        }
                        else {

                                inFileName = argv[3];
                                if (argc == 5)
                                        outFileName = argv[4];
                                else
                                        outFileName = "out.txt";
                        }

                }
                else
                {
                        cout << "False param name or order input params\n" << helpString << endl;
                        return 0;
                }
        }

         collectStatistics_URLs(inFileName, outFileName, topCount);

         return 0;
}
