
#ifndef PRIORITY_QUEUE_INCLUDE_ITEM_H
#define PRIORITY_QUEUE_INCLUDE_ITEM_H

#include <cstdint>
#include <memory>


namespace priority_queue {

  class Item {

    private:

      std::unique_ptr< uint8_t[] > data;
      const uint64_t size;

    public:

      Item( const Item& ) = delete;

      explicit Item( std::unique_ptr< uint8_t[] >&&, const uint64_t& ) noexcept;

      explicit Item( Item&& ) noexcept;

      const uint8_t* get_data() const noexcept;

      const uint64_t& get_size() const noexcept;

  };

} // namespace priority_queue

#endif // PRIORITY_QUEUE_INCLUDE_ITEM_H
