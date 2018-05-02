#ifndef NETWORK_ASIO_H_INCLUDED
#define NETWORK_ASIO_H_INCLUDED

#include <iostream>
#include <string>
#include <set>
#include <boost/asio.hpp>

#include "TConsole.h"
#include "TBlockProcessor.h"

namespace network{

    using namespace boost::asio;

    struct session
      : public std::enable_shared_from_this<session>
    {
    public:
      session(ip::tcp::socket socket, std::set<std::shared_ptr<session>>& container, TConsolePtr console)
        : _socket(std::move(socket)),
            _symbol(0),
            _read_line(""),
            _container(container),
            _console(console),
            _blockCounter(0),
            _processor()
      {
      }

      virtual ~session(){}

      void start()
      {
        read();
      }

    private:
      void read()
      {
        auto self(shared_from_this());
        boost::asio::async_read(_socket,
            boost::asio::buffer(&_symbol, 1),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
              if (!ec)
              {
                  if('\n' != _symbol){
                    _read_line+=_symbol;
                  }
                  else {
                    if('\r' == _read_line.back())
                        _read_line.pop_back();

                    if("{" == _read_line){
                        if(0==_blockCounter)
                            _processor.parseCommand(_read_line);
                        ++_blockCounter;
                    }
                    else if ("}" == _read_line){
                        _processor.parseCommand(_read_line);
                        --_blockCounter;
                    }
                    else if (0==_blockCounter)
                        _console->commonInput(_read_line);
                    else _processor.parseCommand(_read_line);
                    _read_line.clear();
                  }

                  read();
              }
              else
              {

                _container.erase(self);
                _socket.close();
                if ( _container.empty())
                    _console->flush();
              }
            });
      }

      ip::tcp::socket _socket;
      char _symbol;
      std::string _read_line;
      std::set<std::shared_ptr<session>>& _container;

      TConsolePtr   _console;

      size_t _blockCounter;
      TBlockProcessor _processor;
    };

    using containerConnections = std::set<std::shared_ptr<session>>;

    class server
    {
    public:
      server(boost::asio::io_service& io_service,
          const ip::tcp::endpoint& endpoint,
          TConsolePtr console)
        : acceptor_(io_service, endpoint),
          socket_(io_service),
          clients(),
          _console(console)
      {
        do_accept();
      }

    private:
      void do_accept()
      {
        acceptor_.async_accept(socket_,
            [this](boost::system::error_code ec)
            {
              if (!ec){
                auto session_new = std::make_shared<session>(std::move(socket_), clients, _console);
                clients.insert(session_new);
                session_new->start();
              }
              do_accept();
            });
      }

      ip::tcp::acceptor acceptor_;
      ip::tcp::socket socket_;
      std::set<std::shared_ptr<session>> clients;
      TConsolePtr _console;
    };
}



#endif // NETWORK_ASIO_H_INCLUDED
