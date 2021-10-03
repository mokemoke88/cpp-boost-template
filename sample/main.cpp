/**
 * @file sample/main.cpp
 */

#include <cstdlib>
#include <chrono>
#include <boost/asio.hpp>

#include <iostream>

namespace asio = boost::asio;
namespace chrono = std::chrono;


int main(int argc, char** argv){
  (void)argc;
  (void)argv;

  asio::io_context ioc(0);

  asio::steady_timer longtimer(ioc);
  asio::steady_timer shorttimer(ioc);

  auto longHandler = [&](const boost::system::error_code& ec){
    if(ec == asio::error::operation_aborted){
      std::cerr << "longtimer canceled" << std::endl;
      return;
    }
    std::cerr << "longtimer expired" << std::endl;
    ioc.stop();
  };

  // ショートタイマ側の満了前にキャンセルされたなら, ロングタイマの期限を延長.
  auto shortHandler = [&](const boost::system::error_code& ec){
    if(ec == asio::error::operation_aborted){
      auto n = longtimer.expires_from_now(chrono::seconds(60));
      if(n != 0){
        longtimer.async_wait(longHandler);
      }
      return;
    }
    std::cerr << "shorttimer expired" << std::endl;
  };


  boost::system::error_code ec;
  shorttimer.expires_from_now(chrono::seconds(3), ec);
  longtimer.expires_from_now(chrono::seconds(60), ec);

  longtimer.async_wait(longHandler);
  shorttimer.async_wait(shortHandler);

  ioc.run();

  return EXIT_SUCCESS;
}