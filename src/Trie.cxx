#include "Trie.hxx"

Trie::Trie() { root = std::make_unique<TrieNode>(); }

void Trie::insert(const std::string& word)
{
  TrieNode *node = root.get();
  for (const auto& c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      node->children[index] = std::make_unique<TrieNode>();
    }
    node = node->children[index].get();
  }
  node->endOfWord = true;
}

bool Trie::search(const std::string& word)
{
  TrieNode *node = root.get();
  for (const auto& c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      return false;
    }
    node = node->children[index].get();
  }
  return node->endOfWord;
}

bool Trie::startsWith(const std::string& prefix)
{
  TrieNode *node = root.get();
  for (const auto& c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      return false;
    }
    node = node->children[index].get();
  }
  return true;
}

void Trie::deleteWord(const std::string& word)
{
  TrieNode *node = root.get();
  for (const auto& c : word) {
    int index = c - 'a';
    if (!node->children[index]) {
      return;
    }
    node = node->children[index].get();
  }
  if (nodr->endOfWord)
    node->endOfWord = false;
}
