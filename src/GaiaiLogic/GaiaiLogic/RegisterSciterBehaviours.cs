using EmptyFlow.SciterAPI;
using GaiaiLogic.HTMLComponents;
using GaiaiLogic.HTMLModels;

namespace GaiaiLogic
{

    internal static class RegisterSciterBehaviours
    {

        internal static void Register(SciterAPIHost host)
        {
            host.Callbacks.AddAttachBehaviourFactory("actionbutton", (element) => new ActionButton(element, host));
            host.Callbacks.AddAttachBehaviourFactory("actionarea", (element) => new ActionArea(element, host));
            host.Callbacks.AddAttachBehaviourFactory("radiobutton", (element) => new RadioButton(element, host));
            host.Callbacks.AddAttachBehaviourFactory("radiobuttongroup", (element) => new RadioButtonGroup(element, host));
            host.Callbacks.AddAttachBehaviourFactory("textbutton", (element) => new TextButton(element, host));

            host.Callbacks.AddAttachBehaviourFactory("tasbarwindows", (element) => new TaskBarWindows(element, host));
            host.Callbacks.AddAttachBehaviourFactory("taskbarbutton", (element) => new TaskBarButton(element, host));

            host.Callbacks.AddAttachBehaviourFactory("triggershub", (element) => new TriggersHubHandler(element, host));
        }

    }

}
