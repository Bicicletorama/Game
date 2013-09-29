//
// AbstractDelegate.h
//
// $Id: //poco/1.4/Foundation/include/Poco/AbstractDelegate.h#1 $
//
// Library: Foundation
// Package: Events
// Module:  AbstractDelegate
//
// Implementation of the AbstractDelegate template.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_AbstractDelegate_INCLUDED
#define Foundation_AbstractDelegate_INCLUDED


#include "Poco/Foundation.h"


namespace Poco {


template <class TArgs> 
class AbstractDelegate
	/// Interface for Delegate and Expire
	/// Very similar to AbstractPriorityDelegate but having two separate files (no inheritance)
	/// allows one to have compile-time checks when registering an observer
	/// instead of run-time checks.
{
public:
	AbstractDelegate(void* pTarget): _pTarget(pTarget)
	{
		poco_assert_dbg (_pTarget != 0);
	}

	AbstractDelegate(const AbstractDelegate& del): _pTarget(del._pTarget)
	{
		poco_assert_dbg (_pTarget != 0);
	}

	virtual ~AbstractDelegate() 
	{
	}

	virtual bool notify(const void* sender, TArgs& arguments) = 0;
		/// Returns false, if the Delegate is no longer valid, thus indicating an expire.

	virtual AbstractDelegate* clone() const = 0;
		/// Returns a deep-copy of the AbstractDelegate

	bool operator < (const AbstractDelegate<TArgs>& other) const
		/// For comparing AbstractDelegates in a collection.
	{
		return _pTarget < other._pTarget;
	}

	void* target() const
	{
		return _pTarget;
	}

protected:
	void* _pTarget;
};


} // namespace Poco


#endif // Foundation_AbstractDelegate_INCLUDED
