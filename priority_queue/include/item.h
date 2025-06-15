
#ifndef INCLUDE_PRIORITY_QUEUE_ITEM_H_
#define INCLUDE_PRIORITY_QUEUE_ITEM_H_

#include <cstdint>
#include <memory>
namespace priority_queue {

  class Item {

    private:

      std::unique_ptr< uint8_t[] > data_mut;
      std::unique_ptr< Item > next_mut;

    private:

      const uint32_t data_size;
  
    public:

      Item() = delete;

      Item( const Item& ) = delete;

    public:

      Item( std::unique_ptr< uint8_t[] >&&, const uint32_t& ) noexcept;

      Item( Item&& ) noexcept;

      bool is_valid() const noexcept;

      void set_next( std::unique_ptr< Item >&& ) noexcept;


  };

}

#endif
