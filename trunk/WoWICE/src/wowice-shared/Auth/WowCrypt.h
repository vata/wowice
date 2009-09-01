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

#ifndef _WOWCRYPT_H
#define _WOWCRYPT_H

#include <stdlib.h>
#include "../Common.h"
#include "BigNumber.h"
#include <vector>
#include <openssl/sha.h>
#include <openssl/rc4.h>

class WowCrypt {
public:
	WowCrypt();
	~WowCrypt();

	void Init(uint8 *K);
    WoWICE_INLINE void DecryptRecv(uint8* pData, size_t len) { if( !m_initialized) { return; } RC4(&m_clientDecrypt, (unsigned long)len, pData, pData); }
    WoWICE_INLINE void EncryptSend(uint8* pData, size_t len) { if( !m_initialized) { return; } RC4(&m_serverEncrypt, (unsigned long)len, pData, pData); }
    bool IsInitialized() { return m_initialized; }

private:
    RC4_KEY m_clientDecrypt;
    RC4_KEY m_serverEncrypt;
    bool m_initialized;
};

#endif
