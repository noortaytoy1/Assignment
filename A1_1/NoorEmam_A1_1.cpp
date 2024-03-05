#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream>

class Compare {
public:
    bool operator()(const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() > b.size(); // Defining priority on the basis of frequency
    }
};

int main() {
    std::vector<std::vector<int>> V;
    int count=4;
    for (int fileIndex = 0; fileIndex < count; ++fileIndex) {
        
        std::ifstream infile("/Users/noorabdelaziz/Desktop/Tracing/Tracing/numbers_"+ std::to_string(fileIndex+1)+".txt");
        if (!infile.is_open()) {
            std::cerr << "Error opening input file." << std::endl;
            return 1; // Return error code
        }
        
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::vector<int> nums;
            int num;
            while (iss >> num) {
                nums.push_back(num);
            }
            V.push_back(nums);
        }
        infile.close();
    }

    std::ofstream outfile("/Users/noorabdelaziz/Desktop/Tracing/Tracing/resultss.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1; // Return error code
    }

    int l = 0;
    while (l != V.size()) {
        std::sort(V[l].begin(), V[l].end());
        l++;
    }

    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Compare> Merged;

    // Push only non-empty vectors into the priority queue
    for (const auto& vec : V) {
        if (!vec.empty()) {
            Merged.push(vec);
        }
    }

    while (Merged.size() > 1) {
        std::vector<int> a1 = Merged.top();
        Merged.pop();
        std::vector<int> a2 = Merged.top();
        Merged.pop();
        std::vector<int> a3;
        int n = 0, m = 0;
        while (n < a1.size() && m < a2.size()) {
            if (a1[n] < a2[m]) {
                a3.push_back(a1[n]);
                n++;
            } else {
                a3.push_back(a2[m]);
                m++;
            }
        }
        while (n < a1.size()) {
            a3.push_back(a1[n]);
            n++;
        }
        while (m < a2.size()) {
            a3.push_back(a2[m]);
            m++;
        }
        Merged.push(a3);
    }

    if (!Merged.empty()) {
        for (int num : Merged.top()) {
            outfile << num << " ";
            std::cout << num << " ";
        }
        std::cout << std::endl; // Print a newline after printing to console
    }

    // Close the files
    outfile.close();

    return 0;
}
