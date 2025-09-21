namespace GaiaiLogic.Models {

    internal class HouseFuse {

        public int Width { get; set; }

        public IEnumerable<int> Triggers { get; set; } = Enumerable.Empty<int> ();

    }

}
