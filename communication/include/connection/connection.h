
#ifndef INCLUDE_COMMUNICATION_CONNECTION_CONNECTION_H_
#define INCLUDE_COMMUNICATION_CONNECTION_CONNECTION_H_

namespace communication {

  template< typename IP_TYPE >
  class Connection {

    private:

      const IP_TYPE ip;
      
    private:

      int socket;

    public:
  
      Connection( const Connection& ) = delete;

      Connection() = delete;

    public:

      ~Connection();

      Connection( const IP_TYPE& );

      Connection( Connection&& );

      const bool operator==( const Connection& ) const;

      const bool operator!=( const Connection& ) const;

      const bool is_connected() const;

      const bool connect();

  };

}

#endif
