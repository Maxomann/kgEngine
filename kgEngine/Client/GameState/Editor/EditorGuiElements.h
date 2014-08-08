#pragma once
#include "../../GUI/GuiElement.h"
#include "../../Network/Messages.h"
#include "BrushSystem.h"

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
		virtual void onClose( tgui::Container& container );

		virtual void onInit( cCore& core, tgui::Container& container );
	};



	CLIENT_API class TileDrawingSubWindow : public NonStaticGuiElement
	{
	public:
		virtual void onInit( cCore& core, tgui::Container& container ) = 0;

		virtual bool hasBrushChanged()=0;

		virtual std::unique_ptr<Brush> createBrush(cCore& core) = 0;

		virtual void onClose( tgui::Container& container ) = 0;
	};



	class TileDrawingWindow : public ExtendableNonStaticGuiElement < TileDrawingWindow, TileDrawingSubWindow >
	{
		tgui::ChildWindow::Ptr m_tileDrawingWindow = nullptr;
		tgui::ComboBox::Ptr m_subWindowSelectionBox = nullptr;

		//since last getBrush() call
		bool m_hasSubWindowChanged = true;

		void m_callback( const tgui::Callback& callback, cCore& core );

		static const std::string NO_BRUSH;

	public:
		virtual void onInit( cCore& core, tgui::Container& container );

		virtual bool hasBrushChanged();

		//returns nullptr if no brush is selected
		std::unique_ptr<Brush> getBrush(cCore& core);

		virtual void onClose( tgui::Container& container );

		static const sf::Vector2i windowSize;
		static const sf::Vector2i selectionBarSize;
	};
}
