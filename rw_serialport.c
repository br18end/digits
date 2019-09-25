#include <stdio.h> /* Standard input/output definitions */
#include <fcntl.h> /* File Control Definitions */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h> /* UNIX Standard Definitions */
#include <errno.h> /* ERROR Number Definitions */
#include <string.h> /* String function definitions */

void main() {
	// File descriptor
	int fd;
	//Open port
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
	/* ttyS0 is the serial port   */
	/* O_RDWR   - Read/Write access to serial port */
	/* O_NOCTTY - No terminal will control the process */
	/* O_NONBLOCK - The file is opened in nonblocking mode */
	/* Open in blocking mode,read will wait */

	//Check errors
	if (fd == -1)
		printf("Opening port: %s(Code:%d)\n", strerror(errno), errno);
	else 
		printf("Opening port: %s(Code:%d)\n", strerror(errno), errno);

	/* Setting the Attributes of the serial port using termios structure */
	// Create the structure
	struct termios SerialPortSettings;
	// Get the current attributes of the Serial port 
	tcgetattr(fd, &SerialPortSettings);

	/* Setting the Baud rate */
	// Set Read  Speed as 9600
	cfsetispeed(&SerialPortSettings,B9600);
	// Set Write Speed as 9600 
	cfsetospeed(&SerialPortSettings,B9600);

	//cfmakeraw() sets the terminal to something like the "raw" mode of the old Version 7 terminal driver: input is available character by character, echoing is disabled, and all special processing of terminal input and output characters is disabled. 
	cfmakeraw(&SerialPortSettings);
	/* 8N1 Mode */
	// Disables the Parity Enable bit(PARENB),So No Parity
	SerialPortSettings.c_cflag &= ~PARENB;
	// CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit
	SerialPortSettings.c_cflag &= ~CSTOPB;
	// Clears the mask for setting the data size
	SerialPortSettings.c_cflag &= ~CSIZE;
	// Set the data bits = 8
	SerialPortSettings.c_cflag |= CS8;
	// No Hardware flow Control
	SerialPortSettings.c_cflag &= ~CRTSCTS;
	// Enable receiver,Ignore Modem Control lines
	SerialPortSettings.c_cflag |= (CREAD | CLOCAL);
	// Disable XON/XOFF flow control both i/p and o/p
	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
	// Non Cannonical mode
	SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ISIG);  
	// No Output Processing
	SerialPortSettings.c_oflag &= ~OPOST;

	/* Setting Time outs */
	// Read at least 1 characters
	SerialPortSettings.c_cc[VMIN] = 1;
	// Wait indefinetly 
	SerialPortSettings.c_cc[VTIME] = 0;

	/* Set the attributes to the termios structure*/
	if((tcsetattr(fd, TCSANOW, &SerialPortSettings)) == -1) 
		printf("Setting attributes: %s(Code:%d)\n", strerror(errno), errno);
	else
		printf("Setting attributes: %s(Code:%d) \nBaudRate = 9600 \nStopBits = 1 \nParity = none\n", strerror(errno), errno);

	/* Read data from serial port */
	// Discards old data in the rx buffer
	tcflush(fd, TCIFLUSH);
	// Buffer to store the data received
	char read_buffer[256];
	memset(read_buffer, '\0', sizeof(read_buffer));
	// Number of bytes read by the read() system call
	int  bytes_read = 0;

	// Write the data
     bytes_read = write(fd,read_buffer, sizeof(read_buffer));
     
     if(bytes_read == -1)
        printf("Writing: %s(Code:%d)\n", strerror(errno), errno);
     else
        printf("Writing %d bytes: %s(Code:%d)\n", bytes_read,  strerror(errno), errno);

	while(1) {
		// Read the data
		bytes_read = read(fd, read_buffer, sizeof(read_buffer));

		if (bytes_read == -1)
        	printf("Reading: %s(Code:%d)\n", strerror(errno), errno);
		else {
			// Print the number of bytes read
			printf("Reading %d bytes %s(Code:%d)\n", bytes_read, strerror(errno), errno);
	 		/*printing only the received characters*/
			for(int i=0; i<bytes_read; i++)
				printf("%c",read_buffer[i]);
			printf("\n");
		}
	}
	//Close file descriptor
	close(fd);
}
