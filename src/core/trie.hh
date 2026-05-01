#pragma once

#include <memory>
#include <array>
#include <string>

class TrieNode {
public:
  bool endOfWord{false};
  std::array<std::unique_ptr<TrieNode>, 26> children{};
};

class Trie {
private:
  std::unique_ptr<TrieNode> root;

public:
  Trie();
  void insert(const std::string& word);
  bool search(const std::string& word);
  bool startsWith(const std::string& prefix);
  void deleteWord(const std::string& word);
};
