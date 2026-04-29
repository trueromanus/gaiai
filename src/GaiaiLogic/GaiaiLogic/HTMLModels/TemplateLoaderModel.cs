using EmptyFlow.SciterAPI;
using GaiaiLogic.Loaders;
using System;
using System.Collections.Generic;
using System.Text;

namespace GaiaiLogic.HTMLModels
{
    internal class TemplateLoaderModel
    {

        private readonly SciterAPIHost m_host;

        public TemplateLoaderModel(SciterAPIHost sciterAPIHost)
        {
            m_host = sciterAPIHost;
        }

        public SciterValue GetTemplate(IEnumerable<SciterValue> parameters)
        {
            if (!parameters.Any()) return m_host.NullValue;

            var firstParameter = parameters.First();
            var nameTemplate = m_host.GetValueString(ref firstParameter);
            var content = TemplateLoader.LoadTemplate(nameTemplate);

            if (content == null) return m_host.NullValue;

            return m_host.CreateValue(content);
        }

    }

}
