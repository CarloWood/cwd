/**
 * \file debug_ostream_operators.h
 * \brief This file contains the declaration of debug serializers.
 *
 * Copyright (C) 2016 Carlo Wood.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CWD_DEBUG_OSTREAM_OPERATORS_H
#define CWD_DEBUG_OSTREAM_OPERATORS_H

#ifdef CWDEBUG

#include <sys/time.h>
#include <iosfwd>                       // std::ostream&
#include <utility>                      // std::pair
#include <map>
#include <boost/shared_ptr.hpp>         // boost::shared_ptr
#include <boost/weak_ptr.hpp>           // boost::weak_ptr
#if CWDEBUG_LOCATION
#include <libcwd/type_info.h>
#else
#include <typeinfo>
#endif
#ifndef NAMESPACE_DEBUG
#include "debug.h"                      // NAMESPACE_DEBUG
#endif

namespace NAMESPACE_DEBUG {

template<typename T>
inline char const* type_name_of()
{
#if CWDEBUG_LOCATION
  return libcwd::type_info_of<T>().demangled_name();
#else
  return typeid(T).name();
#endif
}

} // namespace NAMESPACE_DEBUG

struct timeval;

extern std::ostream& operator<<(std::ostream& os, timeval const& time);                         //!< Print debug info for timeval instance \a time.

#ifdef USE_LIBBOOST
//! Print debug info for boost::shared_ptr&lt;T&gt;.
template<typename T>
std::ostream& operator<<(std::ostream& os, boost::shared_ptr<T> const& data)
{
  os << "(boost::shared_ptr<" << debug::type_name_of<T>() << ">)({";
  if (data.get())
    os << *data;
  else
    os << "<NULL>";
  return os << "})";
}

//! Print debug info for boost::weak_ptr&lt;T&gt;.
template<typename T>
std::ostream& operator<<(std::ostream& os, boost::weak_ptr<T> const& data)
{
  return os << "(boost::weak_ptr<" << debug::type_name_of<T>() << ">)({ " << *boost::shared_ptr<T>(data) << "})";
}
#endif // USE_LIBBOOST

//! Print debug info for std::pair&lt;&gt; instance \a data.
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& data)
{
  return os << "{first:" << data.first << ", second:" << data.second << '}';
}

//! Print a whole map.
template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream& os, std::map<T1, T2, T3> const& data)
{
  os << "{map<" << debug::type_name_of<T1>() <<
      ", " << debug::type_name_of<T2>() <<
      ", " << debug::type_name_of<T3>() <<">:";
  typedef std::map<T1, T2, T3> map_type;
  for (typename map_type::const_iterator iter = data.begin(); iter != data.end(); ++iter)
    os << '{' << *iter << '}';
  return os << '}';
}

#endif // CWDEBUG
#endif // CWD_DEBUG_OSTREAM_OPERATORS_H