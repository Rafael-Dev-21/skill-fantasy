#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <cassert>
#include <type_traits>

struct Handle {
  uint32_t idx;
  uint32_t gen;

  inline bool operator==(const Handle& h) const { return idx == h.idx && gen == h.gen; }
  inline bool operator!=(const Handle& h) const { return idx != h.idx || gen != h.gen; }
};

template<typename T, typename HT>
class HandleVector {
public:
  static constexpr HT null_handle{};

  HandleVector() {
    items.emplace_back(nullptr);
  }

  void clear()
  {
    items.clear();
    free_list.clear();
    items.emplace_back(nullptr);
  }
  template<typename U>
  HT add(U&& v)
  {
    if (!free_list.empty()) {
      HT h = free_list.back();
      free_list.pop_back();
      h.gen++;
      v.handle = h;
      items[h.idx] = std::make_unique<T>(std::forward<U>(v));
      return h;
    }

    uint32_t idx = static_cast<uint32_t>(items.size());
    v.handle.idx = idx;
    v.handle.gen = 1;
    items.push_back(std::make_unique<T>(std::forward<U>(v)));
    return items.back()->handle;
  }
  T& get(const HT& h)
  {
    assert(has(h) && "Invalid handle in HandleVector::get");
    if(has(h)) {
      return *items[h.idx];
    }
    static T dummy{};
    return dummy;
  }
  const T& get(const HT& h) const
  {
    assert(has(h) && "Invalid handle in HandleVector::get");
    if(has(h)) {
      return *items[h.idx];
    }
    static T dummy{};
    return dummy;
  }
  T* get_if(const HT& h)
  {
    if (has(h)) return items[h.idx].get();
    return nullptr;
  }
  const T* get_if(const HT& h) const
  {
    if (has(h)) return items[h.idx].get();
    return nullptr;
  }
  void remove(const HT& h)
  {
    if (has(h)) {
      free_list.push_back(h);
      items[h.idx].reset();
    }
  }
  bool has(const HT& h)
  {
    return h.idx > 0 && h.idx < items.size() 
      && items[h.idx]
      && items[h.idx]->handle == h;
  }

  size_t size() const
  {
    return items.size();
  }

  class iterator {
  private:
    typename std::vector<std::unique_ptr<T>>::iterator current;
    typename std::vector<std::unique_ptr<T>>::iterator end;

    void skip_nulls()
    {
      while (current != end && !(*current)) {
        ++current;
      }
    }

  public:
    iterator(typename std::vector<std::unique_ptr<T>>::iterator begin,
             typename std::vector<std::unique_ptr<T>>::iterator end) :
      current(begin), end(end)
    {
      skip_nulls();
    }

    iterator& operator++()
    {
      ++current;
      skip_nulls();
      return *this;
    }

    T& operator*() {
      return **current;
    }

    T* operator->() {
      return current->get();
    }

    bool operator!=(const iterator& other) const
    {
      return current != other.current;
    }
  };

  class const_iterator {
  private:
    typename std::vector<std::unique_ptr<T>>::const_iterator current;
    typename std::vector<std::unique_ptr<T>>::const_iterator end;

    void skip_nulls()
    {
      while (current != end && !(*current)) {
        ++current;
      }
    }

  public:
    const_iterator(typename std::vector<std::unique_ptr<T>>::const_iterator begin,
                   typename std::vector<std::unique_ptr<T>>::const_iterator end) :
      current(begin), end(end)
    {
      skip_nulls();
    }

    const_iterator& operator++()
    {
      ++current;
      skip_nulls();
      return *this;
    }

    const T& operator*() const
    {
      return **current;
    }

    const T* operator->() const
    {
      return current->get();
    }

    bool operator!=(const const_iterator& other) const
    {
      return current != other.current;
    }
  };

  iterator begin() { return iterator(items.begin(), items.end()); }
  iterator end() { return iterator(items.end(), items.end()); }
  const_iterator begin() const { return const_iterator(items.begin(), items.end()); }
  const_iterator end() const { return const_iterator(items.end(), items.end()); }

  inline T& operator[](const HT &h) { return get(h); }

private:
  std::vector<std::unique_ptr<T>> items;
  std::vector<HT> free_list;
};
