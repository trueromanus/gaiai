namespace GaiaiLogic.Models {

    internal record TrafficLight {

        public string District { get; init; } = "";

        public IEnumerable<TrafficLightItem> Items { get; init; } = Enumerable.Empty<TrafficLightItem> ();

    }

}
