
#ifndef INCLUDE_COMMUNICATION_SERVER_SERVER_H_
#define INCLUDE_COMMUNICATION_SERVER_SERVER_H_

namespace communication {

  template< typename IP_TYPE >
  class Server {

    private:

      const IP_TYPE ip;
      const int listen_size;

    private:

      int socket;

    public:

      Server( const Server& ) = delete;

      Server() = delete;

    public:

      ~Server();

      Server( const IP_TYPE&, const int );

      Server( Server&& );

      const bool operator==( const Server& ) const;

      const bool operator!=( const Server& ) const;

      const bool is_up() const;

      const bool start();

  };

}

#endif
