using EmptyFlow.SciterAPI;

namespace GaiaiLogic.HTMLComponents
{

    internal class ActionArea : SciterEventHandler
    {

        private const string ActionAreaScript = "actionarea-script";

        private string m_script = "";

        public ActionArea(nint element, SciterAPIHost host) : base(element, host)
        {
            m_script = host.GetElementAttribute(SubscribedElement, ActionAreaScript);
        }

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_CLICK)
            {
                Host.ExecuteWindowEval(Host.MainWindow, m_script, out _);
                SetReturnState(true);
            }
        }

    }

}
