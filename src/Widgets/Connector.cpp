#include "Connector.h"
#include "../stdafx.h"


namespace Widgets
{
	void Connector::Draw()
	{
		updateBounds();
		Widget::Draw();
	}
}