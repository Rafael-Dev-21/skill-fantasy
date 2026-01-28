#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <optional>

/*
 * Item is no object, but handle or enum
 * Non-stackable game
 */
template<typename Item, std::size_t Size, std::size_t Columns>
class Inventory {
  static_assert(Size > 0, "Inventory size must be > 0");
  static_assert(Columns > 0, "Number of columns must be > 0");

public:
  using container_type = std::array<Item, Size>;
  using value_type = Item;
  using size_type = std::size_t;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;

  static constexpr Item null_item{};
  static constexpr size_type capacity = Size;
  static constexpr size_type columns = Columns;

  constexpr Inventory() noexcept = default;
  constexpr Inventory(const Inventory&) = default;
  constexpr Inventory(Inventory&&) noexcept = default;
  constexpr Inventory& operator=(const Inventory&) = default;
  constexpr Inventory& operator=(Inventory&&) noexcept = default;

  constexpr size_type size() const noexcept { return count_; }
  constexpr bool empty() const noexcept { return count_ == 0; }
  constexpr bool full() const noexcept { return count_ == capacity; }
  constexpr size_type rows() const noexcept
  {
    return (capacity + columns - 1) / columns;
  }

  constexpr std::optional<size_type> pick(const Item& item)
  {
    if (full())
      return std::nullopt;
    items_[count_] = item;
    return count_++;
  }
  constexpr Item drop(size_type index)
  {
    if (index >= count_)
      return null_item;

    Item dropped = items_[index];
    if (index != count_ -1)
      items_[index] = items_[count_-1];
    --count_;
    return dropped;
  }
  constexpr bool has(const Item& item) const noexcept
  {
    for (size_type i = 0; i < count_; i++)
      if (items_[i] == item)
        return true;
    return false;
  }
  constexpr const Item& get(size_type index) const noexcept
  {
    if (index >= count_)
      return null_item;
    return items_[index];
  }
  constexpr Item& get(size_type index) noexcept
  {
    if (index >= count_)
      return const_cast<Item&>(null_item);
    return items_[index];
  }
  constexpr std::optional<size_type> find(const Item& item) const noexcept
  {
    for (size_type i = 0; i < count_; ++i)
      if (items_[i] == item)
        return i;
    return std::nullopt;
  }

  iterator begin() noexcept { return items_.begin(); }
  const_iterator end() noexcept { return items_.begin() + count_; }
  const_iterator begin() const noexcept { return items_.cbegin(); }
  const_iterator end() const noexcept { return items_.cbegin() + count_; }
  const_iterator cbegin() const noexcept { return items_.cbegin(); }
  const_iterator cend() const noexcept { return items_.cbegin() + count_; }

  struct Coord { std::size_t row; std::size_t col; };
  constexpr Coord coord_of(size_type index) const noexcept
  {
    return { index / columns, index % columns };
  }

  constexpr const container_type& data() const noexcept { return items_; }
  constexpr container_type& data() noexcept { return items_; }

private:
  container_type items_{};
  size_type count_{0};
};

/*
 * Slot is also enum
 */
template <typename Item, typename Slot>
class EquipSet {
public:
  using slot_type = Slot;
  using item_type = Item;

  std::optional<Item> equip(Slot slot, const Item& item)
  {
    auto it = slots_.find(slot);
    if (it != slots_.end()) {
      std::optional<Item> prev = std::move(it->second);
      it->second = item;
      return prev;
    }
    slots_.emplace(slot, item);
    return std::nullopt;
  }
  std::optional<Item> unequip(Slot slot)
  {
    auto it = slots_.find(slot);
    if (it == slots_.end())
      return std::nullopt;
    std::optional<Item> removed = std::move(it->second);
    slots_.erase(it);
    return removed;
  }
  std::optional<Item> peek(Slot slot) const
  {
    auto it = slots_.find(slot);
    if (it == slots_.end())
      return std::nullopt;
    return it->second;
  }
  bool has(Slot slot) const noexcept { return slots_.count(slot) != 0; }
  void clear() noexcept { slots_.clear(); }

  auto begin() const noexcept { return slots_.begin(); }
  auto end() const noexcept { return slots_.end(); }
  auto begin() noexcept { return slots_.begin(); }
  auto end() noexcept { return slots_.end(); }

private:
  std::unordered_map<Slot, Item> slots_;
};
