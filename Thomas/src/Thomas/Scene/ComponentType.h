#pragma once

namespace Thomas {

	enum ComponentTypeId
	{
		//Invalid component id
		CT_None = 0,
		CT_Point,
		CT_Colour,
		CT_Triangle,
		CT_Rigidbody,

		//Max
		CT_MaxComponents
	};

}