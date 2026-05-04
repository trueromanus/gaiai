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

}
