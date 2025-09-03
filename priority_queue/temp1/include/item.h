
#ifndef INCLUDE_PRIORITY_QUEUE_ITEM_H_
#define INCLUDE_PRIORITY_QUEUE_ITEM_H_

#include <cstdint>
#include <memory>

namespace priority_queue {

  class Item {

    private:

      friend class Priority_Slot;

      std::unique_ptr< uint8_t[] > data_mut;

    private: 

    public:

      const uint32_t data_size;
  
    public:

      Item( const Item& ) = delete;

    public:

      Item() noexcept;

      Item( std::unique_ptr< uint8_t[] >&&, const uint32_t& ) noexcept;

      Item( Item&& ) noexcept;

      bool is_valid() const noexcept;

      const uint8_t* get_data() const noexcept;

  };

}

#endif // INCLUDE_PRIORITY_QUEUE_ITEM_H_
