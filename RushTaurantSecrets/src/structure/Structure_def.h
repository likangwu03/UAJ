#pragma once
#include <cstdint>

namespace _ecs {
	using id_type = uint8_t;

	// Components
	enum _cmp_id : id_type {
		cmp_TRANSFORM,

		// Do not erase pls
		cmp_INVALID
	};
	constexpr id_type cmpNum = cmp_INVALID;
	
	// Groups
	enum _grp_id : id_type {
		grp_GENERAL,

		// Do not erase pls
		grp_INVALID
	};
	constexpr id_type grpNum = grp_INVALID;

	// Handlers
	enum _hdr_id : id_type {

		// Do not erase pls
		hdr_INVALID
	};
	constexpr id_type hdrNum = hdr_INVALID;
}