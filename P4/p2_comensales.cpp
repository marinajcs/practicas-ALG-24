#include <bits/stdc++.h>
#include <deque>
#include <tuple>
using namespace std;
#define V 4

// Function to find the minimum weight Hamiltonian Cycle
void backtrackComensales(vector<vector<int>> & C, vector<bool> &CV, int currPos, const int & nodes, int level, int current_sum, int& max_sum, const int starting_node, std::deque<int> branch)
{

	// If last node is reached and it has a link to the starting node i.e the source then
	// keep the minimum value out of the total current_sum of traversal and "max_sum"
	// Finally return to check for more possible values
	if (level == nodes) {
        std::cout << "JUMP FROM " << currPos << " TO: " << starting_node << " VALUE: " << C[currPos][starting_node] << " FINAL MAX: " << current_sum+C[currPos][starting_node] << std::endl;
		max_sum = max(max_sum, current_sum + C[currPos][starting_node]);
		branch.push_back(starting_node);

		std::cout << "BRANCH OF STARTING POINT OF:  " << starting_node << std::endl;
		while (!branch.empty()){
			std::cout << branch.front() << std::endl;
			branch.pop_front();
		}
		return;
	}

	// BACKTRACKING STEP
	// Loop to traverse the adjacency list of currPos node and increasing the level by 1 and current_sum by C[currPos][i] value
	for (int i = 0; i < nodes; i++) {
		if (!CV[i]) {
			// Mark as visited
			CV[i] = true;
			branch.push_back(i);
			std::cout << "JUMP FROM " << currPos << " TO: " << i << " VALUE: " << C[currPos][i] << " ACTUAL VALUE: " << current_sum+C[currPos][i] << std::endl;

			backtrackComensales(C, CV, i, nodes, level + 1, current_sum + C[currPos][i], max_sum, starting_node, branch);
			branch.pop_back();
			// Mark ith node as unvisited for the next recursive branch after the returning
			CV[i] = false;
		}
	}
};

int main()
{
	// n is the number of nodes i.e. V
	int n = 4;

	std::vector<vector<int>> C = {
        {0, 50, 80, 30},
        {50, 0, 30, 60},
        {80, 30, 0, 20},
        {30, 60, 20, 0}
	};

	// Boolean array to check if a node
	// has been visited or not
	std::vector<bool> CV(n);
	for (int i = 0; i < n; i++)
		CV[i] = false;

    int starting_node = 0;

	// Mark 0th node as visited
	CV[starting_node] = true;
	std::deque<int> branch;
	branch.push_back(starting_node);
	int max_sum = 0;

	// Find the maximum weight Hamiltonian Cycle
	backtrackComensales(C, CV, starting_node, n, 1, 0, max_sum, starting_node, branch);

	// max_sum is the maximum weight Hamiltonian Cycle
	std::cout << max_sum << std::endl;

	return 0;
}
