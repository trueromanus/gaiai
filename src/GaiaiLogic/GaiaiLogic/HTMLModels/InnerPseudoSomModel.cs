using EmptyFlow.SciterAPI;
using EmptyFlow.SciterAPI.Client.PseudoSom;
using System.Diagnostics.CodeAnalysis;
using System.Reflection;
using System.Runtime.InteropServices.Marshalling;

namespace GaiaiLogic.HTMLModels
{

    internal partial class InnerPseudoSomModel<[DynamicallyAccessedMembers(DynamicallyAccessedMemberTypes.All)] T> : IPseudoSomModel where T : class
    {
        private string m_unique = "";

        private Dictionary<string, PropertyInfo> m_properties = new Dictionary<string, PropertyInfo>();

        private readonly string m_modelName = "";

        private readonly SciterAPIHost m_sciterAPIHost;

        private readonly T m_model;

        public InnerPseudoSomModel(T model, string modelName, SciterAPIHost host)
        {
            m_modelName = modelName;
            m_sciterAPIHost = host;
            m_model = model;
            var modelType = model.GetType();
            var properties = modelType.GetProperties(BindingFlags.Public | BindingFlags.Instance);
            foreach (var property in properties)
            {
                m_properties.Add(property.Name, property);
            }
        }

        public string Unique => m_unique;

        public string GetModelName() => m_modelName;

        public SciterValue CallMethod(string name, IEnumerable<SciterValue> parameters)
        {
            throw new NotImplementedException();
        }

        public HashSet<string> GetMethods()
        {
            return [];
        }

        public HashSet<string> GetProperties() => m_properties.Keys.ToHashSet();

        public SciterValue GetPropetyValue(string name)
        {
            if (m_properties.TryGetValue(name, out var property))
            {
                return m_sciterAPIHost.CreateValue(property.GetValue(m_model));
            }

            return m_sciterAPIHost.NullValue;
        }

        public bool SetPropetyValue(SciterValue value, string name)
        {
            if (m_properties.TryGetValue(name, out var property))
            {
                var type = property.PropertyType;
                switch (type)
                {
                    case Type _ when type == typeof(string):
                        var sciterString = m_sciterAPIHost.GetValueString(ref value);
                        property.SetValue(m_model, sciterString);
                        break;
                    case Type _ when type == typeof(int):
                        var sciterInt = m_sciterAPIHost.GetValueInt32(ref value);
                        property.SetValue(m_model, sciterInt);
                        break;
                    case Type _ when type == typeof(double):
                        var sciterDouble = m_sciterAPIHost.GetValueDouble(ref value);
                        property.SetValue(m_model, sciterDouble);
                        break;
                    case Type _ when type == typeof(decimal):
                        var sciterDecimal = m_sciterAPIHost.GetValueDouble(ref value);
                        property.SetValue(m_model, sciterDecimal);
                        break;
                    case Type _ when type == typeof(float):
                        var sciterFloat = m_sciterAPIHost.GetValueDouble(ref value);
                        property.SetValue(m_model, sciterFloat);
                        break;
                    case Type _ when type == typeof(long):
                        var sciterLong = m_sciterAPIHost.GetValueInt64(ref value);
                        property.SetValue(m_model, sciterLong);
                        break;
                    case Type _ when type == typeof(bool):
                        var sciterBoolean = value.d == 1;
                        property.SetValue(m_model, sciterBoolean);
                        break;
                    default: return false;
                }

                return true;
            }

            return false;
        }

        public void SetUnique(string unique) => m_unique = unique;

    }



}
