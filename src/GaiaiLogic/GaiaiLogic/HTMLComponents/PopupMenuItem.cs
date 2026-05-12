using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

    internal class ItemPopupMenu : SciterEventHandler
    {

        private readonly PopupMenu m_menu;

        public ItemPopupMenu(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            var parent = host.NodeParent(relatedThing);
            m_menu = (host.GetEventHandlerByPointer(parent) as PopupMenu) ?? throw new Exception("Parent for ItemPopupMenu not PopupMenu");
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_MOUSE;

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_CLICK)
            {
                m_menu.ClickOnMenu(this);
            }

            if (command == MouseEvents.MOUSE_ENTER)
            {
                m_menu.HoverOnMenu(this);
            }

            if (command == MouseEvents.MOUSE_LEAVE)
            {

            }
        }

    }

}
