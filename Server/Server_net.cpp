#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#pragma warning(disable : 4996)

using boost::asio::ip::tcp;
using namespace std;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

        while (true)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            string message = make_daytime_string();

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
            cout << "Server start!" << endl;
        }
        
    }
    catch (exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}