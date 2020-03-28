﻿//820.单词的压缩编码
//给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A
//
//例如，如果这个列表是["time", "me", "bell"]，我们就可以将其表示为 S = "time#bell#" 和 indexes = [0, 2, 5]
//
//对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，直到 "#" 结束，来恢复我们之前的单词列表
//
//那么成功对给定单词列表进行编码的最小字符串长度是多少呢？
//
//
//
//示例：
//
//输入 : words = ["time", "me", "bell"]
//输出 : 10
//说明 : S = "time#bell#" ， indexes = [0, 2, 5] 
//
//提示：
//
//1. 1 <= words.length <= 2000
//2. 1 <= words[i].length <= 7
//3. 每个单词都是小写字母 

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class TrieNode {
    TrieNode* children[26];
public:
    int count;
    TrieNode() 
    {
        for (int i = 0; i < 26; i++)children[i] = NULL;
        count = 0;
    }
    TrieNode* get(char c) 
    {
        if (children[c - 'a'] == NULL)
        {
            children[c - 'a'] = new TrieNode();
            count++;
        }
        return children[c - 'a'];
    }
};
int minimumLengthEncoding(vector<string>& words) {
    TrieNode* trie = new TrieNode();
    unordered_map<TrieNode*, int> nodes;

    for (int i = 0; i < words.size(); i++)
    {
        TrieNode* cur = trie;
        for (int j = words[i].length() - 1; j >= 0; j--)
        {
            cur = cur->get(words[i][j]);
        }
        nodes[cur] = i;
    }
    int ans = 0;
    for (auto a : nodes)
    {
        if (a.first->count == 0)
            ans += words[a.second].length() + 1;
    }
    return ans;
}

int main()
{
    cout << endl;
    return 0;
}
