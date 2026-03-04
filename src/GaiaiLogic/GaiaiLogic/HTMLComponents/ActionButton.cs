using EmptyFlow.SciterAPI;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

    internal class ActionButton : SciterEventHandler
    {

        private const string IdleState = "button-idle-panel";

        private const string PressedState = "button-pressed-panel";

        private const string ArgumentAttribute = "iconbutton-arg-";

        private readonly string m_parametersScript = "";

        private readonly bool m_hasParameters = false;

        private string m_script = "";

        private SciterAPIHost m_host;

        public ActionButton(nint element, SciterAPIHost host) : base(element, host)
        {
            m_host = host;

            var names = m_host.GetElementAttributeNames(SubscribedElement)
                .Where(a => a.StartsWith(ArgumentAttribute))
                .ToArray();
            var result = new List<string>(names.Length);
            foreach (var name in names)
            {
                var attribute = name.Replace(ArgumentAttribute, "");
                var value = m_host.GetElementAttribute(SubscribedElement, name);
                result.Add($"\"{attribute}\": {value}");
            }
            m_hasParameters = result.Any();

            if (m_hasParameters)
            {
                var builder = new StringBuilder();
                builder.Append("var parameters = {");
                builder.Append(string.Join(",", result));
                builder.Append("};");
                m_parametersScript = builder.ToString();
            }

            m_script = m_host.GetElementAttribute(SubscribedElement, "iconbutton-script");
        }

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_DOWN)
            {
                var classValue = Host.GetElementAttribute(SubscribedElement, "class");
                Host.SetElementAttribute(SubscribedElement, "class", classValue.Replace(IdleState, PressedState));
                SetReturnState(true);
            }

            if (command is MouseEvents.MOUSE_CLICK or MouseEvents.MOUSE_LEAVE)
            {
                var classValue = Host.GetElementAttribute(SubscribedElement, "class");
                Host.SetElementAttribute(SubscribedElement, "class", classValue.Replace(PressedState, IdleState));

                Host.ExecuteWindowEval(Host.MainWindow, m_hasParameters ? m_parametersScript + m_script : m_script, out _);
                SetReturnState(true);
            }
        }

    }

}
