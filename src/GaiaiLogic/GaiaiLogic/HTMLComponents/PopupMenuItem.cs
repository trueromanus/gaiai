using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

    internal class ItemPopupMenu : SciterEventHandler
    {

        private readonly PopupMenu m_menu;

        private readonly int m_menuId;

        public ItemPopupMenu(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            var parent = host.NodeParent(relatedThing);
            m_menu = (host.GetEventHandlerByPointer(parent) as PopupMenu) ?? throw new Exception("Parent for ItemPopupMenu not PopupMenu");
            m_menuId = Convert.ToInt32(host.GetElementAttribute(m_subscribedElement, "menu-id"));
        }

        public int MenuId => m_menuId;

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_MOUSE;

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_CLICK)
            {
                m_menu.ClickOnMenu(this);
            }

            if (command == MouseEvents.MOUSE_ENTER)
            {
                Host.SetElementStyleProperty(m_subscribedElement, "background-color", "#00007F");
                Host.SetElementStyleProperty(m_subscribedElement, "color", "white");

                m_menu.HoverOnMenu(this);
            }

            if (command == MouseEvents.MOUSE_LEAVE)
            {
                Host.SetElementStyleProperty(m_subscribedElement, "background-color", "transparent");
                Host.SetElementStyleProperty(m_subscribedElement, "color", "black");
            }
        }

    }

}
