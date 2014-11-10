#pragma once

#include "Widget.h"

namespace Widgets
{
	class Connector : public Widget
	{
	public:
		void Draw() const override;


		Connector() = default;
		Connector(const Connector&) = default;
		Connector(Connector&& rhs) = default;
		Connector& operator=(const Connector&) = default;
		Connector& operator=(Connector&&) = default;
		virtual ~Connector() = default;
	};
}