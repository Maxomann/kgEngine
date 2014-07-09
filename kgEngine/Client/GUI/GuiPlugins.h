//_______GUI_PLUGINS_______//

#pragma once
#include "GuiElements.h"

namespace kg
{
	class StandartTileDrawingSubWindow : public TileDrawingSubWindow
	{
	public:
		virtual void onInit( cCore& core, tgui::Gui& gui )
		{

		};

		virtual std::shared_ptr<Brush> createBrush()
		{
			return std::make_shared<StandartBrush>();
		};

		virtual void onClose( tgui::Gui& gui )
		{

		};

		static std::string info()
		{
			return "SingleBrush";
		};

	};

}