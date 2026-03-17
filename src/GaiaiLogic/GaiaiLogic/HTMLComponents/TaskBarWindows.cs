using EmptyFlow.SciterAPI;

namespace GaiaiLogic.HTMLComponents
{

    internal class TaskBarWindows : SciterEventHandler
    {

        private const string IdlePanel = "button-idle-panel";

        private const string PressedPanel = "button-pressed-panel";

        private const string GridPanel = "grid-panel task-bar-window-button-pressed";

        private IDictionary<int, nint> m_taskBarWindows = new Dictionary<int, nint>();

        private string m_activateScript = "";

        public TaskBarWindows(nint relatedThing, SciterAPIHost host) : base(relatedThing, host)
        {
            m_activateScript = Host.GetElementAttribute(m_subscribedElement, "taskbakwindow-script");
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_SCRIPTING_METHOD_CALL | EventBehaviourGroups.HANDLE_METHOD_CALL;

        public override (SciterValue? value, bool handled) ScriptMethodCall(string name, IEnumerable<SciterValue> arguments)
        {
            switch (name)
            {
                case "activateWindow": return (ActivateWindow(arguments), true);
                case "deactivateWindow": return (DeactivateWindow(arguments), true);
                case "createWindow": return (CreateWindow(arguments), true);
                case "closeWindow": return (CloseWindow(arguments), true);
                default: return base.ScriptMethodCall(name, arguments);
            }
        }

        public void ActivateWindow(int windowIndex)
        {
            Host.ExecuteWindowEval(Host.MainWindow, m_activateScript.Replace("{{windowindex}}", windowIndex.ToString()), out _);
        }

        private SciterValue ActivateWindow(IEnumerable<SciterValue> arguments)
        {
            if (!arguments.Any()) return Host.CreateValue(false);

            var firstArgument = arguments.First();
            var windowIndex = Host.GetValueInt32(ref firstArgument);

            if (m_taskBarWindows.ContainsKey(windowIndex))
            {
                var button = m_taskBarWindows[windowIndex];
                var valueOfClass = Host.GetElementAttribute(button, "class");
                if (valueOfClass.Contains(IdlePanel))
                {
                    Host.SetElementAttribute(button, "class", valueOfClass.Replace(IdlePanel, PressedPanel) + " " + GridPanel);
                }

                return Host.CreateValue(true);
            }

            return Host.CreateValue(false);
        }

        private SciterValue DeactivateWindow(IEnumerable<SciterValue> arguments)
        {
            if (!arguments.Any()) return Host.CreateValue(false);

            var firstArgument = arguments.First();
            var windowIndex = Host.GetValueInt32(ref firstArgument);

            if (m_taskBarWindows.ContainsKey(windowIndex))
            {
                var button = m_taskBarWindows[windowIndex];
                var valueOfClass = Host.GetElementAttribute(button, "class");
                if (valueOfClass.Contains(PressedPanel))
                {
                    Host.SetElementAttribute(button, "class", valueOfClass.Replace(PressedPanel, IdlePanel).Replace(GridPanel, ""));
                }

                return Host.CreateValue(true);
            }

            return Host.CreateValue(false);
        }

        private SciterValue CreateWindow(IEnumerable<SciterValue> arguments)
        {
            if (!arguments.Any()) return Host.CreateValue(false);

            var firstArgument = arguments.First();
            var windowIndex = Host.GetValueInt32(ref firstArgument);

            if (m_taskBarWindows.ContainsKey(windowIndex)) return Host.CreateValue(false);

            var element = Host.MakeCssSelector($"[window-index={windowIndex}]", m_subscribedElement).First();
            m_taskBarWindows.Add(windowIndex, element);

            return Host.CreateValue(true);
        }

        private SciterValue CloseWindow(IEnumerable<SciterValue> arguments)
        {
            if (!arguments.Any()) return Host.CreateValue(false);

            var firstArgument = arguments.First();
            var windowIndex = Host.GetValueInt32(ref firstArgument);

            if (m_taskBarWindows.ContainsKey(windowIndex)) m_taskBarWindows.Remove(windowIndex);

            return Host.CreateValue(true);
        }

        public override string GetUnique() => "taskbarwindows";

    }

}
