#include <iostream>
#include <boost/asio.hpp>

int main() {
	using boost::asio::io_context;
	using boost::asio::ip::tcp;

	io_context ctx;

	auto listen_endpoint = *tcp::resolver(ctx).resolve("127.0.0.1:12345", "tcpdemo", tcp::resolver::passive).begin();
	tcp::acceptor acceptor(ctx, listen_endpoint);
	// TODO
	return 0;
}