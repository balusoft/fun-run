/*
332. Reconstruct Itinerary   My Submissions QuestionEditorial Solution
Total Accepted: 8700 Total Submissions: 36366 Difficulty: Medium
Given a list of airline tickets represented by pairs of departure and arrival
airports [from, to], reconstruct the itinerary in order. All of the tickets
belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
If there are multiple valid itineraries, you should return the itinerary that
has the smallest lexical order when read as a single string. For example, the
itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets =
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it
is larger in lexical order.


*/

using Graph=std::unordered_map<std::string, std::multiset<std::string>>;
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        /**
         * 1) make a graph
         * 2) make DFS:
         *    2.1) add to result
         *    2.2) if no chlideren && result.len == tick.len mark done, and return.
         *    2.3) if no childern && result.len != tick.len pop(), and return
         *    2.4) for (v : g[u]) {
         *            if (v is not visited) {
         *    2.5)    dfs(g, v, res);
         *            } else { res.add v }
         *    2.6)    if res.len == it.len : done = true, return
         */
         if (tickets.empty()) {
             //return {};
         }
         Graph g;
         makeGraph(g, tickets);
         std::vector<std::string> res;
         res.reserve(g.size());
         dfs(g, "JFK", res);
         res.shrink_to_fit();
         return res;
    }
    void makeGraph(Graph &g, const std::vector<std::pair<std::string, std::string>> &tickets) {
        for (const auto &e : tickets) {
            g[e.first].insert(e.second);
        }
    }
    void dfs(Graph &g, const std::string &u, std::vector<std::string> &res) {
        std::stack<std::string> stack;
        stack.push(u);
        while (!stack.empty()) {
            const std::string &top = stack.top();
            // has outgoing edges?
            if (g[top].empty()) {
                // add it to result
                res.push_back(top);
                // now done with that node in stack
                stack.pop();
            } else {
                // Now add outgoing edge node to stack.
                stack.push(*(g[top].begin()));
                g[top].erase(g[top].begin());
            }
        }
        std::reverse(res.begin(), res.end());
    }
};
