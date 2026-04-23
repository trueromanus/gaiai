using EmptyFlow.SciterAPI;
using EmptyFlow.SciterAPI.Client.PseudoSom;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLModels
{

    internal class TriggersHubModel
    {

        private readonly TriggersHub m_hub;

        private readonly SciterAPIHost m_host;

        public TriggersHubModel(TriggersHub hub, SciterAPIHost sciterAPIHost)
        {
            m_hub = hub;
            m_host = sciterAPIHost;
        }

        public SciterValue EnableTrigger(IEnumerable<SciterValue> parameters)
        {
            if (!parameters.Any()) return m_host.NullValue;

            var firstParameter = parameters.First();
            var trigger = m_host.GetValueString(ref firstParameter);
            m_hub.EnableTrigger(trigger);

            return m_host.NullValue;
        }

        public SciterValue DisableTrigger(IEnumerable<SciterValue> parameters)
        {
            if (!parameters.Any()) return m_host.NullValue;

            var firstParameter = parameters.First();
            var trigger = m_host.GetValueString(ref firstParameter);
            m_hub.DisableTrigger(trigger);

            return m_host.NullValue;
        }

    }

    internal class TriggersHubHandler : SciterEventHandler
    {

        private InnerPseudoSomModel<TriggersHubModel> m_model;

        public TriggersHubHandler(nint relatedThing, SciterAPIHost sciterAPIHost) : base(relatedThing, sciterAPIHost)
        {
#pragma warning disable CS8604 // Possible null reference argument.
            var innerModel = new TriggersHubModel(GameLibrary.TriggersHub, sciterAPIHost);
#pragma warning restore CS8604 // Possible null reference argument.
            m_model = new InnerPseudoSomModel<TriggersHubModel>(innerModel, "triggershub", sciterAPIHost);
            PseudoSom.RegisterModel(m_model, sciterAPIHost, Host.MainWindow, relatedThing);
        }

        public override (SciterValue? value, bool handled) ScriptMethodCall(string name, IEnumerable<SciterValue> arguments) => PseudoSom.Handle(m_model, Host, name, arguments);

    }

}
