/* Copyright (C) 2014 InfiniDB, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; version 2 of
   the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA. */

/******************************************************************************
 * $Id$
 *
 *****************************************************************************/

/** @file
 * class BRMShmImpl
 */

#pragma once

#include <unistd.h>
//#define NDEBUG
#include <cassert>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace bi = boost::interprocess;

namespace BRM
{

class BRMShmImplParent
{
  public:
    BRMShmImplParent(unsigned key, off_t size, bool readOnly = false);
    virtual ~BRMShmImplParent();

    inline unsigned key() const
    {
        return fKey;
    }
    inline off_t size() const
    {
        return fSize;
    }
    inline bool isReadOnly() const
    {
        return fReadOnly;
    }

    virtual void setReadOnly() = 0;
    virtual int grow(unsigned newKey, off_t newSize) = 0;
    virtual int clear(unsigned newKey, off_t newSize) = 0;
    virtual void destroy() = 0;

protected:
    unsigned fKey;
    off_t fSize;
    bool fReadOnly;
};


class BRMShmImpl : public BRMShmImplParent
{
public:
    BRMShmImpl(unsigned key, off_t size, bool readOnly = false);
    ~BRMShmImpl() { }

    int grow(unsigned newKey, off_t newSize) override;
    int clear(unsigned newKey, off_t newSize) override;
    void destroy() override;
    void setReadOnly() override;

    void swap(BRMShmImpl& rhs);

    bi::shared_memory_object fShmobj;
    bi::mapped_region fMapreg;

private:
    BRMShmImpl(const BRMShmImpl& rhs);
    BRMShmImpl& operator=(const BRMShmImpl& rhs);
};

class BRMManagedShmImpl : public BRMShmImplParent
{
public:
    BRMManagedShmImpl(unsigned key, off_t size, bool readOnly = false);
    ~BRMManagedShmImpl() { }

    int grow(unsigned newKey, off_t newSize) override;
    int clear(unsigned newKey, off_t newSize) override;
    void destroy() override;
    void setReadOnly() override;

    void swap(BRMManagedShmImpl& rhs);

    bi::managed_shared_memory* fShmSegment;
private:
    BRMManagedShmImpl(const BRMManagedShmImpl& rhs);
    BRMManagedShmImpl& operator=(const BRMManagedShmImpl& rhs);
};

} //namespace
