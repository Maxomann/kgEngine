#include "GuiElement.h"
#include "../Network/Messages.h"

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
		ConnectToServerWindow( cCore& core, tgui::Gui& gui );

		virtual void onClose( tgui::Gui& gui );
	};
}
