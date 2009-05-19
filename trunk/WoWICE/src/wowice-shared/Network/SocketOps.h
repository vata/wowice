/*
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * Multiplatform Async Network Library
 * Copyright (c) 2007 Burlex
 *
 * SocketOps - wrapper for any specific socket operations that may be platform-dependant.
 *
 */


#ifndef SOCKET_OPS_H
#define SOCKET_OPS_H

namespace SocketOps
{
	// Create file descriptor for socket i/o operations.
	SOCKET CreateTCPFileDescriptor();

	// Disable blocking send/recv calls.
	bool Nonblocking(SOCKET fd);

	// Enable blocking send/recv calls.
	bool Blocking(SOCKET fd);

	// Disable nagle buffering algorithm
	bool DisableBuffering(SOCKET fd);

	// Enables nagle buffering algorithm
	bool EnableBuffering(SOCKET fd);

	// Set internal buffer size to socket.
	bool SetRecvBufferSize(SOCKET fd, uint32 size);

	// Set internal buffer size to socket.
	bool SetSendBufferSize(SOCKET fd, uint32 size);

	// Set timeout, in seconds
	bool SetTimeout(SOCKET fd, uint32 timeout);

	// Closes socket completely.
	void CloseSocket(SOCKET fd);

	// Sets SO_REUSEADDR
	void ReuseAddr(SOCKET fd);
};

#endif

