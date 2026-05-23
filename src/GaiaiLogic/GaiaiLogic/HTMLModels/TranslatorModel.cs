using EmptyFlow.SciterAPI;
using GaiaiLogic.Translate;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLModels
{

    internal class TranslatorModel
    {

        private readonly Translator m_translator;

        private readonly SciterAPIHost m_host;

        public TranslatorModel(Translator translator, SciterAPIHost sciterAPIHost)
        {
            m_translator = translator;
            m_host = sciterAPIHost;
        }

        public SciterValue FillTranslations(IEnumerable<SciterValue> parameters)
        {
            if (!parameters.Any()) return m_host.NullValue;

            var firstParameter = parameters.First();
            var translate = m_host.GetValueString(ref firstParameter);

            var translated = m_translator.FillTranslations(translate);

            return m_host.CreateValue(translated);
        }

    }

}
