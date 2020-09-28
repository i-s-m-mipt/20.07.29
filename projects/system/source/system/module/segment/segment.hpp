#ifndef SOLUTION_SYSTEM_MODULE_SEGMENT_HPP
#define SOLUTION_SYSTEM_MODULE_SEGMENT_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#  pragma once
#endif // #ifdef BOOST_HAS_PRAGMA_ONCE

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../../../../shared/source/logger/logger.hpp"

namespace solution
{
	namespace system
	{
		namespace module
		{
			class segment_exception : public std::exception
			{
			public:

				explicit segment_exception(const std::string & message) noexcept :
					std::exception(message.c_str())
				{}

				explicit segment_exception(const char * const message) noexcept :
					std::exception(message)
				{}

				~segment_exception() noexcept = default;
			};

			class Segment
			{
			public:

				using id_t = boost::uuids::uuid;

				using segments_container_t = std::vector < id_t > ;

			public:

				enum class Type
				{
					station,
					railway
				};

			public:

				template < typename Id, typename Name, typename Adjacent_Segments, typename Enable = 
					std::enable_if_t <
						std::is_convertible_v < Id, id_t > &&
						std::is_convertible_v < Name, std::string > &&
						std::is_convertible_v < Adjacent_Segments, segments_container_t > > >
				explicit Segment(
					Id && id, Type type, Name && name, std::size_t length, Adjacent_Segments && adjacent_segments) :
						m_id(std::forward < Id > (id)), m_type(type), m_name(std::forward < Name > (name)), 
						m_length(length), m_adjacent_segments(std::forward < Adjacent_Segments > (adjacent_segments))
				{}

				~Segment() noexcept = default;

			public:

				const auto & id() const noexcept
				{
					return m_id;
				}

			public:

				static boost::uuids::string_generator string_generator;

			private:

				const id_t m_id;
				const Type m_type;
				const std::string m_name;
				const std::size_t m_length; // (m)
				const segments_container_t m_adjacent_segments;

			private:

				id_t m_current_train_id = boost::uuids::nil_generator()();
			};

		} // namespace module

	} // namespace system

} // namespace solution

#endif // #ifndef SOLUTION_SYSTEM_MODULE_SEGMENT_HPP