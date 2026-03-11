using EmptyFlow.SciterAPI;

namespace GaiaiLogic.HTMLModels
{
    internal partial class TestModelPseudoSomModel
    {

        public int Property1 { get; set; }

        public string Property2 { get; set; } = "";

        public SciterValue CallMethod(IEnumerable<SciterValue> parameters)
        {
            return new SciterValue();
        }

    }

    

}
