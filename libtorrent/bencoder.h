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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef BTBENCODER_H
#define BTBENCODER_H


#include "file.h"


namespace bt
{
	class File;

	/**
	 * @author Joris Guisson
	 * @brief Helper class to b-encode stuff.
	 * 
	 * This class b-encodes data. For more details about b-encoding, see
	 * the BitTorrent protocol docs. The data gets written to a File
	 */
	class BEncoder 
	{
		File* fptr;
	public:
		/**
		 * Constructor
		 */
		BEncoder(File* fptr);
		virtual ~BEncoder();

		/**
		 * Begin a dictionary.Should have a corresponding end call.
		 */
		void beginDict();
		
		/**
		 * Begin a list. Should have a corresponding end call.
		 */
		void beginList();
		
		/**
		 * Write an int
		 * @param val 
		 */
		void write(int val);
		
		/**
		 * Write a string
		 * @param str 
		 */
		void write(const QString & str);
		
		/**
		 * Write a QByteArray
		 * @param data 
		 */
		void write(const QByteArray & data);

		/**
		 * Write a data array
		 * @param data
		 * @param size of data
		 */
		void write(const Uint8* data,Uint32 size);
		
		/**
		 * End a beginDict or beginList call.
		 */
		void end();
	};

}

#endif
