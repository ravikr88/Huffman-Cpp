#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class HuffTree
{
public:
    int val;
    char letter;
    HuffTree *left;
    HuffTree *right;

    HuffTree(int val, char c)
    {
        this->val = val;
        this->letter = c;
        this->left = NULL;
        this->right = NULL;
    }
};

class Compare
{
public:
    bool operator()(HuffTree *a, HuffTree *b)
    {
        if (a->val > b->val)
            return true;
        else
        {
            return false;
        }
    }
};

vector<pair<int, char>> FrequencyDect(string s)
{
    map<char, int> mp;
    for (int i = 0; i < s.size(); i++)
    {
        mp[s[i]]++;
    }
    vector<pair<int, char>> v;
    for (int i = 0; i < s.size(); i++)
    {
        if (mp[s[i]] != 0)
        {
            v.push_back(make_pair(mp[s[i]], s[i]));
            mp[s[i]] = 0;
        }
    }
    return v;
}

HuffTree *makeTree(vector<pair<int, char>> &frq)
{
    priority_queue<HuffTree *, vector<HuffTree *>, Compare> q;
    for (int i = 0; i < frq.size(); i++)
    {
        q.push(new HuffTree(frq[i].first, frq[i].second));
    }

    while (q.size() > 1)
    {
        HuffTree *left = q.top();
        q.pop();
        HuffTree *right = q.top();
        q.pop();

        HuffTree *nd = new HuffTree(left->val + right->val, '~');
        nd->left = left; // Fixed: Assign left and right subtrees
        nd->right = right;
        q.push(nd);
    }

    return q.top();
}

void InOrder(HuffTree *tree)
{
    if (tree)
    {
        InOrder(tree->left);
        cout << tree->val << endl;
        InOrder(tree->right);
    }
}

void getValues(HuffTree *root, string s, vector<pair<char, string>> &vtr)
{
    if (!root)
    {
        return;
    }

    if (root->letter != '~')
    {
        vtr.push_back(make_pair(root->letter, s));
    }

    getValues(root->left, s + '0', vtr);
    getValues(root->right, s + '1', vtr);
}

int main()
{
    cout << "Enter a string\n";
    string s;
    cin >> s;

    vector<pair<int, char>> frq = FrequencyDect(s);

    // Uncomment to print frequencies
    // for (int i = 0; i < frq.size(); i++) {
    //     cout << frq[i].first << " " << frq[i].second << endl;
    // }

    vector<pair<char, string>> vtr;

    HuffTree *tree = makeTree(frq);
    InOrder(tree);
    getValues(tree, "", vtr);

    string res = "";
    for (auto i : vtr)
    {
        cout << i.first << " " << i.second << endl;
        res += i.second;
    }

    cout << "************" << endl;
    cout << s << endl;
    cout << res << endl;

    return 0;
}
