using GaiaiLogic.Models;

namespace GaiaiLogic.Loaders {

    internal class LoadedStaticItems {

        public IEnumerable<LampPost> LampPosts { get; init; } = Enumerable.Empty<LampPost>();

        public IEnumerable<TrafficLight> TrafficLights { get; init; } = Enumerable.Empty<TrafficLight> ();

        public IEnumerable<House> Houses { get; init; } = Enumerable.Empty<House> ();

    }

}
