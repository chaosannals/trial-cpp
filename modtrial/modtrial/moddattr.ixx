export module moddattr;

namespace moddattrn
{
	export enum attr_type : char8_t {
		integer,
		number,
		string,
	};
	export struct attr
	{
		attr_type type;
		union {
			int iv;
			double dv;
			char8_t* sv;
		} value;
	};
}