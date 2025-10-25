namespace GaiaiLogic.Models {

    public record TrafficLight {

        public string Title { get; init; } = "";

        public string District { get; init; } = "";

        public int X { get; set; }

        public int Y { get; set; }

        public IEnumerable<string> AffectedHouses { get; init; } = Enumerable.Empty<string> ();

    }

}