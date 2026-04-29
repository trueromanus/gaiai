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

            host.Callbacks.AddAttachBehaviourFactory(
                "triggershub",
                (element) =>
                {
                    if (GameLibrary.TriggersHub == null) throw new ArgumentNullException();

                    var hubModel = new TriggersHubModel(GameLibrary.TriggersHub, host);
                    var model = new InnerPseudoSomModel<TriggersHubModel>(hubModel, "triggershub", host);
                    return new PseudoSomModelHandler(model, element, host.MainWindow, host);
                }
            );
            host.Callbacks.AddAttachBehaviourFactory(
                "templateloader",
                (element) =>
                {
                    if (GameLibrary.TriggersHub == null) throw new ArgumentNullException();

                    return new InnerPseudoSomModelHandler<TemplateLoaderModel>(new TemplateLoaderModel(host), element, host.MainWindow, host, "model");
                }
            );


        }

    }

}
