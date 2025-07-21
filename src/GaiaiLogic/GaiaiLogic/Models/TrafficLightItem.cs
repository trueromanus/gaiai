namespace GaiaiLogic.Models {

    public record TrafficLightItem {

        public string Title { get; init; } = "";

        public IEnumerable<string> AffectedHouses { get; init; } = Enumerable.Empty<string> ();

    }

}