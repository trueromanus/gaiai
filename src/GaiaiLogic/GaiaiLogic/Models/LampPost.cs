namespace GaiaiLogic.Models {

    internal class LampPost {

        public string District { get; init; } = "";

        public string Title { get; init; } = "";

        public TimeSpan StartTime { get; set; }

        public int MaximumState { get; set; }

        public IEnumerable<string> AffectedHouses { get; init; } = Enumerable.Empty<string> ();

    }

}
