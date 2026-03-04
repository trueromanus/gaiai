using EmptyFlow.SciterAPI;
using GaiaiLogic.HTMLComponents;

namespace GaiaiLogic
{

    internal static class RegisterSciterBehaviours
    {

        internal static void Register(SciterAPIHost host)
        {
            host.Callbacks.AddAttachBehaviourFactory("actionbutton", (element) => new ActionButton(element, host));
        }

    }

}
