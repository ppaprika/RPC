#include <iostream>
#include <boost//asio.hpp>
#include <thread>
#include <chrono>

int g_count = 0;

void reset_timer(boost::asio::deadline_timer& timer) {
	timer.expires_from_now(boost::posix_time::seconds(1));
	timer.async_wait([&timer](const boost::system::error_code& ec) //Òì²½µÈ´ý
		{
			if (ec) {
				std::cout << ec.message() << std::endl;
				return;
			}

			if (g_count == 10) return;

			g_count++;

			std::cout << "Cool" << std::endl;
			reset_timer(timer);
		});
}

int main() {
	boost::asio::io_service io_service;
	boost::asio::deadline_timer timer(io_service);
	timer.expires_from_now(boost::posix_time::seconds(5));
	std::cout << "Starting syn wait." << std::endl;
	timer.wait();
	std::cout << "Finished syn wait." << std::endl;

	reset_timer(timer);
	
	std::this_thread::sleep_for(std::chrono::seconds(10));
	io_service.run();
	return 0;
}