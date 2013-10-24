/* 
	Copyright 2013 Mona - mathieu.poux[a]gmail.com
 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License received along this program for more
	details (or else see http://www.gnu.org/licenses/).

	This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/Decoding.h"
#include "Mona/WebSocket/WS.h"

namespace Mona {


class WSUnmasking : public Decoding {
public:
	WSUnmasking(UInt32 id,TaskHandler& taskHandler,Protocol& protocol,Poco::SharedPtr<Poco::Buffer<UInt8> >& pBuffer,const Poco::Net::SocketAddress& address,UInt8 type): _type(type),Decoding(id,taskHandler,protocol,pBuffer,address){}
	virtual ~WSUnmasking(){}

private:
	bool						decode(MemoryReader& packet);
	UInt8					_type;
};

inline bool WSUnmasking::decode(MemoryReader& packet) {
	WS::Unmask(packet);
	packet.reset(3);
	(*packet.current()) = _type;
	return true;
}



} // namespace Mona
