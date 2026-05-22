using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;
using System.Text.RegularExpressions;

namespace GaiaiLogic.Translate
{

    internal class Translator
    {

        private Dictionary<string, string> m_translates = new Dictionary<string, string>();

        public void LoadTranslation(string languageCode)
        {
            if (m_translates.Any()) m_translates.Clear();

            var content = File.ReadAllText($"Translate/Translations-{languageCode}.json");
            var root = JsonNode.Parse(content);
            var rootObject = root?.AsObject();
            if (rootObject == null) return;

            foreach (var item in rootObject)
            {
                m_translates.Add(item.Key, item.Value?.ToString() ?? "");
            }
        }

        public void AddToTranslation(string name, string value)
        {
            m_translates.Add(name, value);
        }

        public string FillTranslations(string template)
        {
            var regex = new Regex(@"\{\{trans_([A-Za-z0-9_]+)\}\}");
            var matches = regex.Matches(template);
            var result = template;
            foreach (Match match in matches)
            {
                var value = match.Groups[1].Value;
                var original = match.Value;
                if (m_translates.ContainsKey(value))
                {
                    result = result.Replace(original, m_translates[value]);
                }
            }

            return result;
        }

    }

}
