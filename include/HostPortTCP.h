
#ifndef HOSTPORTTCP_H
#define HOSTPORTTCP_H

#include <memory> 
#include <string>
#include "sockpp/tcp_connector.h"
#include "sockpp/version.h"

#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>

/*! \brief A class for host communication via TCP/IP protocol.
    \details Class for host communication via TCP/IP protocol with a specified communication protocol.
    Data packet consists of
    - 4-bytes header
    - data (with specified length)
    - 4-bytes terminator
    No check sum is performed.
    \author Stefano Lovato
    \date 2022
*/
class HostPortTCP {
public:

    /*! \brief Constructor.
		\details Default constructor. 
	*/
    HostPortTCP();

    /*! \brief Desctructor.
		\details Default destructor. It automatically destroy the serial object.
	*/
    ~HostPortTCP();

    /*! \brief Begin the host port.
		\details Function to begin the host port communication with default header, terminator, and timeout.
        \param ipaddr The IP address to use.
        \param port The socket port to use.
        \return true if success, false otherwise.
	*/
    bool begin(std::string ipaddr, unsigned short port);

    /*! \brief Begin the host port.
		\details Function to begin the host port communication with given header and terminator and default timeout.
        \param ipaddr The IP address to use.
        \param port The socket port to use.
        \param header The header to use (as a HEX number of 4-bytes).
        \param terminator The terminator to use (as a HEX number of 4-bytes).
        \return true if success, false otherwise.
	*/
    bool begin(std::string ipaddr, unsigned short port, unsigned int header, unsigned int terminator);

    /*! \brief Begin the host port.
		\details Function to begin the host port communication with given header, terminator and timeout.
        \param ipaddr The IP address to use.
        \param port The socket port to use.
        \param header The header to use (as a HEX number of 4-bytes).
        \param terminator The terminator to use (as a HEX number of 4-bytes).
        \param timeout The timeout of the serial communcication.
        \return true if success, false otherwise.
	*/
    bool begin(std::string ipaddr, unsigned short port, unsigned int header, unsigned int terminator, unsigned int timeout);
    
    /*! \brief Read data buffer.
		\details Function to read a data buffer with given length from the host port.
        Host port must be opened before.
        \param packetPtr The pointer to the data buffer.
        \param size The size of the data buffer.
        \return true if success, false otherwise.
	*/
    bool read(unsigned char* packetPtr, unsigned int size);

    /*! \brief Write data buffer.
		\details Function to write a data buffer with given length to the host port.
        Host port must be opened before.
        \param packetPtr The pointer to the data buffer.
        \param size The size of the data buffer.
        \return true if success, false otherwise.
	*/
    bool write(unsigned char* packetPtr, unsigned int size); 

    /*! \brief Close the host port.
		\details Function to close the host port.
        Host port must be opened before.
        \return true if success, false otherwise.
	*/
    bool close(void); 

    /*! \brief Restart the host port.
		\details Function to restart the host port.
        Host port must be opened before.
        \return true if success, false otherwise.
	*/
    bool restart(void);

    /*! \brief Flush the port.
		\details Function to flush the port.
        Host port must be opened before.
        \return true if success, false otherwise.
	*/
    bool flush(void);

    /*! \brief Set the serial port.
		\details Function to set the socket port. The restart function must be called to make the change effective.
        \return true if success, false otherwise.
	*/
    bool setPort(unsigned short port);

    /*! \brief Set the IP address.
		\details Function to set the IP address of the socket communiation. The restart function must be called to make the change effective.
        \return true if success, false otherwise.
	*/
    bool setIP(std::string ipaddr); 

    /*! \brief Set the header.
		\details Function to set the header of the host communication. The restart function must be called to make the change effective.
        \return true if success, false otherwise.
	*/
    bool setHeader(unsigned int header); //set the header

    /*! \brief Set the terminator.
		\details Function to set the terminator of the host communication. The restart function must be called to make the change effective.
        \return true if success, false otherwise.
	*/
    bool setTerminator(unsigned int terminator); 

    /*! \brief Set the timeout.
		\details Function to set the timeout of the host communication. The restart function must be called to make the change effective.
        \return true if success, false otherwise.
	*/
    bool setTimeout(unsigned int timeout); 

    /*! \brief Get the serial port.
		\details Function to get the serial port used for the host communication. 
        \return The serial port number.
	*/
    unsigned short getPort(void);

    /*! \brief Get the IP address.
		\details Function to get the IP address used for the socket communication. 
        \return The baudrate.
	*/
    std::string getIP(void);
    
    /*! \brief Get the header.
		\details Function to get the header used for the host communication. 
        \return The header.
	*/
    unsigned int getHeader(void); 

    /*! \brief Get the terminator.
		\details Function to get the terminator used for the host communication. 
        \return The terminator.
	*/
    unsigned int getTerminator(void); 

    /*! \brief Get the timeout.
		\details Function to get the timeout used for the host communication. 
        \return The timeout.
	*/
    unsigned int getTimeout(void); 

     /*! \brief Check if host port is open.
        \details Function to check if the host port has been open successfully.
        \return true if the host port is open, false otherwise.
    */
    bool isInit(void); //check if is init
    
    /*! \brief Check if host port is open.
        \details Boolean operator to check if the host port has been open successfully.
        \return true if the host port is open, false otherwise.
    */
    operator bool() { return isInit(); }
    
    static constexpr unsigned int HEADER = 0xFF812345; //!< Default header.
    static constexpr unsigned int TERMINATOR = 0xFF8CABDE; //!< Default terminator.
    static constexpr unsigned int TIMEOUT = 1000; //!< Default timeout.

    /*! \brief Print details on the object.
        \details Print operator to show the details on the HostPort object.
        \param os The stram object.
        \param hp The HostPort object.
        \return The stream object.
    */
    friend std::ostream& operator<<(std::ostream& os, HostPortTCP hp) {
        os << "HostPort at:\t0x" << std::hex << (uint64_t) &hp << std::dec << std::endl;
        if (!hp.isInit()) {
            os << "IP:\t" << "Undefined" << std::endl;
            os << "Port:\t\t" << "Undefined" << std::endl;
            os << "Header:\t\t" << "Undefined" << std::endl;
            os << "Terminator:\t" << "Undefined" << std::endl;
            os << "Timeout:\t" << "Undefined" << std::endl;
        } else {
            os << "IP:\t" << hp._ip.c_str() << std::endl;
            os << "Port:\t\t" << hp._port << std::endl;
            os << "Header:\t\t0x" << std::hex << hp._header << std::dec << std::endl;
            os << "Terminator:\t0x" << std::hex << hp._terminator << std::dec << std::endl;
            os << "Timeout:\t" << hp._timeout << std::endl;
        }
        if (hp.isInit()) os << "isInit:\t\t" << "True"  << std::endl;
        else os << "isInit:\t\t" << "False" << std::endl;
        return os;
    }

    /*! \brief Read data for Pythoin.
        \details Wrapper function to read data from Python binding.
        \param obj The Python object, created using numpy.empty(SIZE, dtype=numpy.DATATYPE)
        \return true if success, false otherwise.
    */
    bool readpy(boost::python::object obj);

    /*! \brief Write data for Pythoin.
        \details Wrapper function to write data from Python binding.
        \param obj The Python object, created using numpy.empty(SIZE, dtype=numpy.DATATYPE)
        \return true if success, false otherwise.
    */
    bool writepy(boost::python::object obj);

private:
    //static constexpr unsigned int TX_BUF_SIZE = 1024; //!< Size of the output buffer.
    sockpp::socket_initializer sockInit;
    static constexpr unsigned int MASK = 0xFF; //!< Mask for parsing.
    sockpp::tcp_connector client; //!< Socket object.
    unsigned int _port = 0; //!< Socket port.
    std::string _ip = ""; //!< IP address.
    unsigned int _terminator = 0; //!< Terminator bytes.
    unsigned int _header = 0; //!< Header bytes.
    unsigned int _timeout = 0; //!< Timeout.
    //unsigned char _tx_buf[TX_BUF_SIZE]; //!< Tx buffer.
    bool _isFirstRead = false; //!< True if firt packer read.
    bool init(std::string ipaddr, unsigned short port, unsigned int timeout); //!< Private initialization function
};

#endif