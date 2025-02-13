#include <concepts>
#include <cstddef>
#include <stdexcept>

namespace moon {

template <class Arr, class T>
concept has_data_size = requires(Arr arr) {
  { std::data(arr) } -> std::convertible_to<T*>;
  { std::size(arr) } -> std::same_as<size_t>;
};

template <class T>
struct Span {
  T* data;
  std::size_t size;

  template <has_data_size<T> Arr>
  Span(Arr&& arr) : data(std::data(arr)), size(std::size(arr)) {}

  explicit Span(T* data, size_t size) : data(data), size(size) {}

  Span Subspan(size_t start, size_t length = (size_t)-1) const {
    if (start > size) {
      throw std::out_of_range("subspan start out of range");
    }
    auto maxLength = size - start;
    if (length > maxLength) {
      length = maxLength;
    }
    return Span(data + start, length);
  }
};

}  // namespace moon
