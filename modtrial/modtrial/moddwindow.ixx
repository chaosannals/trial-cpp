export module modd;

import <map>;
import <string>;
import moddattr;

namespace modn
{
	struct window_state {
		std::map<std::string, moddattrn::attr> attrs;
	};

	export class window {
		window_state* state;
	public:

	};
}