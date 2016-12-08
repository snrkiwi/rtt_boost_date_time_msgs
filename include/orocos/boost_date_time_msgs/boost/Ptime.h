#ifndef BOOST_DATE_TIME_MSGS_BOOST_SERIALIZATION_PTIME_H
#define BOOST_DATE_TIME_MSGS_BOOST_SERIALIZATION_PTIME_H

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#include <boost_date_time_msgs/Ptime.h>
#include <boost_date_time_typekit/typekit/Types.hpp>

namespace boost
{
namespace serialization
{

template<class Archive, class ContainerAllocator>
void serialize(Archive& a,  ::boost_date_time_msgs::Ptime_<ContainerAllocator>  & m, unsigned int version)
{
    serialize(a, static_cast< ::boost::posix_time::ptime &>(m), version);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_DATE_TIME_MSGS_BOOST_SERIALIZATION_PTIME_H

