using EmptyFlow.SciterAPI;

namespace GaiaiLogic.HTMLComponents
{

    internal class TaskBarButton : SciterEventHandler
    {

        private TaskBarWindows? m_windowHandler;

        private int m_windowIndex = -1;

        public TaskBarButton(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            var attribute = Host.GetElementAttribute(m_subscribedElement, "window-index");
            try
            {
                m_windowIndex = Convert.ToInt32(attribute);
            }
            catch
            {
            }
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_MOUSE;

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_CLICK)
            {
                if (m_windowHandler == null) m_windowHandler = Host.GetEventHandlerByUnique("taskbarwindows") as TaskBarWindows;

                if (m_windowHandler != null && m_windowIndex != -1) m_windowHandler.ActivateWindow(m_windowIndex);
            }
        }

    }

}
