/***************************************************************************
 *   Copyright (C) 2005 by Joris Guisson                                   *
 *   joris.guisson@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ***************************************************************************/
#include <qstring.h>
#include <string.h>
#include <util/log.h>
#include <util/bitset.h>
#include <util/functions.h>
#include <torrent/globals.h>
#include "packet.h"
#include "request.h"
#include "chunk.h"
#include "peer.h"

namespace bt
{

	static Uint8* AllocPacket(Uint32 size,Uint8 type)
	{
		Uint8* data = new Uint8[size];
		WriteUint32(data,0,size - 4);
		data[4] = type;
		return data;
	}


	Packet::Packet(Uint8 type) : data(0),size(0),written(0)
	{
		size = 5;
		data = AllocPacket(size,type);
	}
	
	Packet::Packet(Uint16 port) : data(0),size(0),written(0)
	{
		size = 7;
		data = AllocPacket(size,PORT);
		WriteUint16(data,5,port);
		
	}
	
	Packet::Packet(Uint32 chunk,Uint8 type) : data(0),size(0),written(0)
	{
		size = 9;
		data = AllocPacket(size,type);
		WriteUint32(data,5,chunk);
	}
	
	Packet::Packet(const BitSet & bs) : data(0),size(0),written(0)
	{
		size = 5 + bs.getNumBytes();
		data = AllocPacket(size,BITFIELD);
		memcpy(data+5,bs.getData(),bs.getNumBytes());
	}
	
	Packet::Packet(const Request & r,Uint8 type) : data(0),size(0),written(0)
	{
		size = 17;
		data = AllocPacket(size,type);
		WriteUint32(data,5,r.getIndex());
		WriteUint32(data,9,r.getOffset());
		WriteUint32(data,13,r.getLength());
	}
	
	Packet::Packet(Uint32 index,Uint32 begin,Uint32 len,Chunk* ch) : data(0),size(0),written(0)
	{
		size = 13 + len;
		data = AllocPacket(size,PIECE);
		WriteUint32(data,5,index);
		WriteUint32(data,9,begin);
		memcpy(data+13,ch->getData() + begin,len);
	}


	Packet::~Packet()
	{
		delete [] data;
	}
	
	/*
	QString Packet::debugString() const
	{
		if (!data)
			return QString::null;
		
		switch (data[4])
		{
			case CHOKE : return QString("CHOKE %1 %2").arg(hdr_length).arg(data_length);
			case UNCHOKE : return QString("UNCHOKE %1 %2").arg(hdr_length).arg(data_length);
			case INTERESTED : return QString("INTERESTED %1 %2").arg(hdr_length).arg(data_length);
			case NOT_INTERESTED : return QString("NOT_INTERESTED %1 %2").arg(hdr_length).arg(data_length);
			case HAVE : return QString("HAVE %1 %2").arg(hdr_length).arg(data_length);
			case BITFIELD : return QString("BITFIELD %1 %2").arg(hdr_length).arg(data_length);
			case PIECE : return QString("PIECE %1 %2").arg(hdr_length).arg(data_length);
			case REQUEST : return QString("REQUEST %1 %2").arg(hdr_length).arg(data_length);
			case CANCEL : return QString("CANCEL %1 %2").arg(hdr_length).arg(data_length);
			default: return QString("UNKNOWN %1 %2").arg(hdr_length).arg(data_length);
		}
	}
	*/
	bool Packet::isOK() const
	{
		if (!data)
			return false;

		return true;
	}

	bool Packet::send(Peer* peer,Uint32 max_bytes,Uint32 & bytes_sent)
	{
		bool proto = data[4] != PIECE;
		if (written + max_bytes >= size)
		{
			peer->sendData(data + written,size - written,proto);
			written = size;
			bytes_sent = size - written;
			return true;
		}
		else
		{
			peer->sendData(data + written,max_bytes,proto);
			written += max_bytes;
			bytes_sent = max_bytes;
			return false;
		}
	}
}
