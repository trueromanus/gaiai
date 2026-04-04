using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{
    internal class TextButton : SciterEventHandler
    {

        private const string IdleState = "button-idle-panel";

        private const string PressedState = "button-pressed-panel";

        private bool m_pressed = false;

        private string m_script = "";

        private nint m_buttonRoot = nint.Zero;

        private string m_buttonTemplate =
"""
<div class="button-idle-panel">
	<div style="height: {{height}}px; width: {{width}}px;" class="flex-column">
		<div class="item-center flex-row" style="height: 100%;">
			<div class="text-middle-plus-size item-center">{{title}}</div>
		</div>
	</div>
</div>
""";

        public TextButton(nint element, SciterAPIHost host) : base(element, host)
        {
            m_script = Host.GetElementAttribute(SubscribedElement, "button-script");
            var width = Host.GetElementAttribute(SubscribedElement, "button-width");
            var height = Host.GetElementAttribute(SubscribedElement, "button-height");
            var title = Host.GetElementAttribute(SubscribedElement, "button-title");

            Host.SetElementHtml(
                m_subscribedElement,
                m_buttonTemplate
                    .Replace("{{height}}", height)
                    .Replace("{{width}}", width)
                    .Replace("{{title}}", title),
                SetElementHtml.ReplaceContent
            );
            m_buttonRoot = Host.NodeFirstChild(SubscribedElement);
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_MOUSE;

        private void PressedButton()
        {
            var classValue = Host.GetElementAttribute(m_buttonRoot, "class");
            Host.SetElementAttribute(m_buttonRoot, "class", classValue.Replace(IdleState, PressedState));
            m_pressed = true;
            SetReturnState(true);
        }

        private void UnpressedButton()
        {
            var classValue = Host.GetElementAttribute(m_buttonRoot, "class");
            Host.SetElementAttribute(m_buttonRoot, "class", classValue.Replace(PressedState, IdleState));
            m_pressed = false;
            SetReturnState(true);
        }

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_DOWN)
            {
                PressedButton();
                return;
            }

            if (command == MouseEvents.MOUSE_LEAVE)
            {
                UnpressedButton();
                return;
            }

            if (m_pressed == true && command is MouseEvents.MOUSE_CLICK)
            {
                UnpressedButton();
                Host.ExecuteWindowEval(Host.MainWindow, m_script, out _);
                return;
            }
        }

    }

}
