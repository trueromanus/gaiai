using EmptyFlow.SciterAPI;
using EmptyFlow.SciterAPI.Client.PseudoSom;
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

            host.Callbacks.AddAttachBehaviourFactory("popupmenu", (element) => new PopupMenu(element, host));
            host.Callbacks.AddAttachBehaviourFactory("popupmenuitem", (element) => new ItemPopupMenu(element, host));

            host.Callbacks.AddAttachBehaviourFactory(
                "triggershub",
                (element) =>
                {
                    if (Program.GameHost.TriggersHub == null) throw new ArgumentNullException();

                    var hubModel = new TriggersHubModel(Program.GameHost.TriggersHub, host);
                    var model = new InnerPseudoSomModel<TriggersHubModel>(hubModel, "triggershub", host);
                    return new PseudoSomModelHandler(model, element, host.MainWindow, host);
                }
            );
            host.Callbacks.AddAttachBehaviourFactory(
                "templateloader",
                (element) =>
                {
                    if (Program.GameHost.TriggersHub == null) throw new ArgumentNullException();

                    return new InnerPseudoSomModelHandler<TemplateLoaderModel>(new TemplateLoaderModel(host), element, host.MainWindow, host, "model");
                }
            );
            host.Callbacks.AddAttachBehaviourFactory(
                "translator",
                (element) =>
                {
                    if (Program.GameHost.Translator == null) throw new ArgumentNullException();

                    return new InnerPseudoSomModelHandler<TranslatorModel>(new TranslatorModel(Program.GameHost.Translator, host), element, host.MainWindow, host, "model");
                }
            );
        }

    }

}
