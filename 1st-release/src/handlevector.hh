#pragma once

#include <cstdint>
#include <vector>

struct Handle {
  uint32_t idx;
  uint32_t gen;

  inline bool operator==(const Handle& h) const { return idx == h.idx && gen == h.gen; }
  inline bool operator!=(const Handle& h) const { return idx != h.idx || gen != h.gen; }
};

template<typename T, typename HT>
class HandleVector {
public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  void clear()
  {
    items.clear();
    free_list.clear();
  }
  HT add(T& v)
  {
    if (free_list.size() > 0) {
      auto h = free_list.back();
      free_list.pop_back();
      h.gen++;
      v.handle = h;
      items[h.idx] = v;
      return h;
    }

    if (items.size() == 0) {
      items.push_back({});
    }

    uint32_t idx = static_cast<uint32_t>(items.size());
    v.handle.idx = idx;
    v.handle.gen = 1;
    items.push_back(v);
    return v.handle;
  }
  T& get(const HT& h)
  {
    if(h.idx > 0 && h.idx < items.size() && items[h.idx].handle == h)
      return items[h.idx];
    else
      return items[0];
  }
  void remove(const HT& h)
  {
    if (h.idx > 0 && h.idx < items.size() && items[h.idx].handle == h) {
      free_list.push_back(h);
      items[h.idx] = {};
    }
  }
  bool has(const HT& h)
  {
    return h.idx > 0 && h.idx < items.size() && items[h.idx].handle == h;
  }

  inline iterator begin() { return items.begin()+1; }
  inline iterator end() { return items.end(); }
  inline const_iterator cbegin() { return items.cbegin()+1; }
  inline const_iterator cend() { return items.cend(); }

  inline T& operator[](const HT &h) { return get(h); }

private:
  std::vector<T> items;
  std::vector<HT> free_list;
};
