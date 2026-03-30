using EmptyFlow.SciterAPI;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLComponents
{

    internal class RadioButtonGroup : SciterEventHandler
    {

        private const string Value = "radio-value";

        private const string Changed = "radio-group-changed";

        private string m_changedScript = "";

        private string m_initialValue = "";

        private string m_currentValue = "";

        public RadioButtonGroup(nint relatedThing, SciterAPIHost host, SciterEventHandlerMode mode = SciterEventHandlerMode.Element) : base(relatedThing, host, mode)
        {
            m_changedScript = Host.GetElementAttribute(m_subscribedElement, Changed);
            m_initialValue = Host.GetElementAttribute(m_subscribedElement, Value);
            if (!string.IsNullOrEmpty(m_initialValue)) m_currentValue = m_initialValue;
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_BEHAVIOR_EVENT;

        public void ActivateRadio(string value, bool fireParent = true)
        {
            var valueElement = Host.MakeCssSelector($"[radio-value=\"{m_currentValue}\"]", m_subscribedElement).FirstOrDefault();
            if (valueElement != nint.Zero)
            {
                var button = Host.GetEventHandlerByPointer(valueElement) as RadioButton;
                if (button != null) button.DeactivatedRadio();
            }
            Host.ExecuteWindowEval(Host.MainWindow, m_changedScript + value, out var _);
            m_currentValue = value;
        }

        public override void BehaviourEvent(BehaviourEvents command, nint targetElement, nint element, nint reason, SciterValue data, string name)
        {
            if (command == BehaviourEvents.CONTENT_CHANGED)
            {
                var valueElement = Host.MakeCssSelector($"[radio-value=\"{m_initialValue}\"]", m_subscribedElement).FirstOrDefault();
                if (valueElement != nint.Zero)
                {
                    var button = Host.GetEventHandlerByPointer(valueElement) as RadioButton;
                    if (button != null) button.ActivateRadio(fireParent: false);
                }
            }
        }

    }

}
