using EmptyFlow.SciterAPI;

namespace GaiaiLogic.HTMLComponents
{
    internal class RadioButton : SciterEventHandler
    {

        private const string Script = "radio-script";

        private const string Title = "radio-title";

        private const string Value = "radio-value";

        private readonly string m_activateScript;

        private bool m_activated = false;

        private nint m_image = nint.Zero;

        private nint m_group = nint.Zero;

        private string m_value = "";

        public RadioButton(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            m_activateScript = Host.GetElementAttribute(m_subscribedElement, Script);

            var title = "";
            if (Host.GetElementHasAttribute(m_subscribedElement, Title)) title = Host.GetElementAttribute(m_subscribedElement, Title);
            m_value = Host.GetElementAttribute(m_subscribedElement, Value);

            var template =
$"""
<div class="flex-row">
    <div style="flow: stack">
        <img src="disabledradio.png" width="16" height="16">
        <svg width="16" height="16" style="display: none;">
            <circle
            cx="8"
            cy="8"
            r="1.1"
            stroke="black"
            stroke-width="2"
            fill="black"
        />
    </div>
    <span class="margin-left-6">{title}</span>
</div>
""";

            Host.SetElementHtml(m_subscribedElement, template, SetElementHtml.ReplaceContent);
            m_image = Host.MakeCssSelector("svg", m_subscribedElement).First();
            m_group = Host.NodeParent(m_subscribedElement);

        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_MOUSE | EventBehaviourGroups.HANDLE_BEHAVIOR_EVENT;

        public void ActivateRadio(bool fireParent = true)
        {
            if (!m_activated)
            {
                if (fireParent)
                {
                    var parentHandler = Host.GetEventHandlerByPointer(m_group) as RadioButtonGroup;
                    if (parentHandler != null) parentHandler.ActivateRadio(m_value);
                }

                Host.SetElementStyleProperty(m_image, "display", "block");
                m_activated = true;
            }
        }

        public void DeactivatedRadio()
        {
            if (m_activated)
            {
                Host.SetElementStyleProperty(m_image, "display", "none");
                m_activated = false;
            }
        }

        public override void MouseEvent(MouseEvents command, SciterPoint elementRelated, SciterPoint ViewRelated, KeyboardStates keyboardStates, DraggingType draggingMode, CursorType cursorType, nint target, nint dragging, bool isOnIcon, uint buttonState)
        {
            if (command == MouseEvents.MOUSE_CLICK) ActivateRadio();
        }

    }
}
