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

    /// <summary>
    /// Single pseudo model event handler.
    /// </summary>
    public class PseudoSomModelHandler : SciterEventHandler
    {

        readonly IPseudoSomModel m_model;

        public PseudoSomModelHandler(IPseudoSomModel model, nint relatedThing, nint window, SciterAPIHost sciterAPIHost) : base(relatedThing, sciterAPIHost)
        {
            m_model = model ?? throw new ArgumentNullException(nameof(model));
            PseudoSom.RegisterModel(m_model, sciterAPIHost, window, relatedThing);
        }

        public override EventBehaviourGroups BeforeRegisterEvent() => EventBehaviourGroups.HANDLE_SCRIPTING_METHOD_CALL | EventBehaviourGroups.HANDLE_METHOD_CALL;


        public override (SciterValue? value, bool handled) ScriptMethodCall(string name, IEnumerable<SciterValue> arguments) => PseudoSom.Handle(m_model, Host, name, arguments);

    }

    public class InnerPseudoSomModelHandler<T> : PseudoSomModelHandler where T : class
    {

        public InnerPseudoSomModelHandler(T model, nint relatedThing, nint window, SciterAPIHost sciterAPIHost, string modelName) :
            base(PseudoSomModelFactory.Inner(model, modelName, sciterAPIHost), relatedThing, window, sciterAPIHost)
        {
        }

    }


}
