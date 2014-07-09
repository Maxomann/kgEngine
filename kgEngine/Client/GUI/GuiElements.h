#pragma once
#include "GuiElement.h"
#include "../Network/Messages.h"
#include "../GameState/Editor/BrushSystem.h"

namespace kg
{
	class ConnectToServerWindow : public NonStaticGuiElement
	{
		tgui::ChildWindow::Ptr m_connectToServerWindow = nullptr;
		tgui::EditBox::Ptr m_ctsIp = nullptr;
		tgui::EditBox::Ptr m_ctsRecievePortOnServer = nullptr;
		tgui::EditBox::Ptr m_ctsRecievePortOnClient = nullptr;
		tgui::Button::Ptr m_ctsSendButton = nullptr;

		void m_callback( const tgui::Callback& callback,
						 cCore& core );

	public:
		virtual void onClose( tgui::Gui& gui );

		virtual void onInit( cCore& core, tgui::Gui& gui );

	};



	CLIENT_API class TileDrawingSubWindow : public NonStaticGuiElement
	{
	public:
		virtual void onInit( cCore& core, tgui::Gui& gui )=0;

		virtual std::shared_ptr<Brush> createBrush() = 0;

		virtual void onClose( tgui::Gui& gui ) = 0;

	};

	class TileDrawingWindow : public ExtendableNonStaticGuiElement<TileDrawingWindow, TileDrawingSubWindow>
	{
		tgui::ChildWindow::Ptr m_tileDrawingWindow = nullptr;
		tgui::ComboBox::Ptr m_subWindowSelectionBox = nullptr;

		void m_callback( const tgui::Callback& callback, cCore& core, tgui::Gui& gui );

		static const std::string NO_BRUSH;

	public:
		virtual void onInit( cCore& core, tgui::Gui& gui );

		//can return nullptr if no brush is selected
		std::shared_ptr<Brush> getBrush();

		virtual void onClose( tgui::Gui& gui );

	};
}
