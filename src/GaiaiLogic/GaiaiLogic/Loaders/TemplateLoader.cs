using GaiaiLogic.Models;
using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using System.Text.Json;

namespace GaiaiLogic.Loaders
{
    public static class TemplateLoader
    {

        private static Assembly? m_assembly;

        private static Dictionary<string, string> m_cachedTemplated = new Dictionary<string, string>();

        public static string LoadTemplate(string name)
        {
            if (m_cachedTemplated.ContainsKey(name)) return m_cachedTemplated[name];

            if (m_assembly == null) m_assembly = typeof(TemplateLoader).Assembly;

            var stream = GetResourceStream(name + ".html");
            using var streamReader = new StreamReader(stream);
            var template = streamReader.ReadToEnd();
            m_cachedTemplated.Add(name, template);

            return template;
        }

        private static Stream GetResourceStream(string file)
        {
            var stream = m_assembly!.GetManifestResourceStream(file);
            if (stream == null) throw new Exception($"Can't read file {file} from resource!");

            return stream;
        }

    }

}
